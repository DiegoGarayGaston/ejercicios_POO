#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class pregunta; // Declaración adelantada

class elementoEncuesta
{
protected:
    int id;
    string texto;
public:
    elementoEncuesta(int id = 0, string texto = "") : id(id), texto(texto) {}

    virtual ~elementoEncuesta() = default;

    int get_id() const { return id; }
    string get_texto() const { return texto; }
    void set_texto(string texto) { this->texto = texto; }

    // Métodos virtuales puros para serialización
    virtual void guardarBinario(ofstream& archivo) const = 0;
    virtual void cargarBinario(ifstream& archivo) = 0;
    virtual void mostrar() const = 0;
};

class respuesta : public elementoEncuesta
{
private:
    pregunta* preguntaAnidada;  // 0 o 1 pregunta

public:
    respuesta(int id = 0, string texto = "", pregunta* p = nullptr)
        : elementoEncuesta(id, texto), preguntaAnidada(p) {}

    // Getters y setters
    pregunta* get_pregunta() const { return preguntaAnidada; }

    void set_pregunta(pregunta* p) { preguntaAnidada = p; }

    bool tiene_pregunta_anidada() const { return preguntaAnidada != nullptr; }

    // Ejecuta la respuesta y si hay pregunta anidada, la ejecuta
    void ejecutar_respuesta();

    // Métodos virtuales
    void guardarBinario(ofstream& archivo) const override;
    void cargarBinario(ifstream& archivo) override;
    void mostrar() const override { cout << "  - " << get_texto() << endl; }
};

class pregunta : public elementoEncuesta
{
private:
    vector<respuesta> respuestas;

public:
    pregunta(int id = 0, string texto = "")
        : elementoEncuesta(id, texto) {}

    // Gestión de respuestas
    void agregar_respuesta(const respuesta& r) { respuestas.push_back(r); }

    const vector<respuesta>& get_respuestas() const { return respuestas; }

    int cantidad_respuestas() const { return respuestas.size(); }

    // Ejecutar la pregunta
    void ejecutar_pregunta()
    {
        cout << "\n>>> " << get_texto() << endl;

        for (size_t i = 0; i < respuestas.size(); i++) {
            cout << i << ") " << respuestas[i].get_texto() << endl;
        }

        int opcion;
        cout << "Selecciona (0-" << (respuestas.size() - 1) << "): ";
        cin >> opcion;

        if (opcion >= 0 && opcion < (int)respuestas.size()) {
            respuestas[opcion].ejecutar_respuesta();
        } else {
            cout << "Opción inválida\n";
        }
    }

    // Mostrar todas las respuestas posibles (estructura recursiva)
    void mostrar_estructura() const
    {
        cout << get_texto() << endl;
        for (const auto& r : respuestas) {
            r.mostrar();
            if (r.tiene_pregunta_anidada()) {
                cout << "    Si selecciona esta opción:\n";
                r.get_pregunta()->mostrar_estructura();
            }
        }
    }

    // Métodos virtuales
    void guardarBinario(ofstream& archivo) const override;
    void cargarBinario(ifstream& archivo) override;
    void mostrar() const override { cout << get_texto() << endl; }
};

// Implementación de respuesta::ejecutar_respuesta()
void respuesta::ejecutar_respuesta()
{
    cout << "Seleccionó: " << get_texto() << endl;

    // Si hay una pregunta anidada, ejecutarla
    if (tiene_pregunta_anidada()) {
        preguntaAnidada->ejecutar_pregunta();
    } else {
        cout << "[Fin de esta rama]\n";
    }
}

// Implementaciones de serialización (placeholders)
void respuesta::guardarBinario(ofstream& archivo) const
{
    archivo.write(reinterpret_cast<char*>(const_cast<int*>(&id)), sizeof(int));
    size_t len = texto.length();
    archivo.write(reinterpret_cast<char*>(&len), sizeof(size_t));
    archivo.write(texto.c_str(), len);
    bool tiene = (preguntaAnidada != nullptr);
    archivo.write(reinterpret_cast<char*>(&tiene), sizeof(bool));
}

void respuesta::cargarBinario(ifstream& archivo)
{
    archivo.read(reinterpret_cast<char*>(&id), sizeof(int));
    size_t len;
    archivo.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    texto.resize(len);
    archivo.read(&texto[0], len);
    bool tiene;
    archivo.read(reinterpret_cast<char*>(&tiene), sizeof(bool));
}

void pregunta::guardarBinario(ofstream& archivo) const
{
    archivo.write(reinterpret_cast<char*>(const_cast<int*>(&id)), sizeof(int));
    size_t len = texto.length();
    archivo.write(reinterpret_cast<char*>(&len), sizeof(size_t));
    archivo.write(texto.c_str(), len);

    size_t numResp = respuestas.size();
    archivo.write(reinterpret_cast<char*>(&numResp), sizeof(size_t));
}

void pregunta::cargarBinario(ifstream& archivo)
{
    archivo.read(reinterpret_cast<char*>(&id), sizeof(int));
    size_t len;
    archivo.read(reinterpret_cast<char*>(&len), sizeof(size_t));
    texto.resize(len);
    archivo.read(&texto[0], len);

    size_t numResp;
    archivo.read(reinterpret_cast<char*>(&numResp), sizeof(size_t));
}

// ===================== MAIN =====================
int main()
{
    // Crear preguntas
    pregunta p1(1, "¿Tiene teléfono móvil?");
    pregunta p2(2, "¿Es de última generación?");
    pregunta p3(3, "¿Usa redes sociales?");

    // Preguntas para la rama del "Sí" de p2
    pregunta p4(4, "¿Tiene 5G?");

    // Preguntas para la rama del "Sí" de p1
    pregunta p5(5, "¿Cuántas horas diarias lo usa?");

    // Respuestas para p1 (¿Tiene teléfono móvil?)
    respuesta r1_si(1, "Sí", &p2);      // Sí -> va a p2
    respuesta r1_no(2, "No", nullptr);  // No -> fin

    p1.agregar_respuesta(r1_si);
    p1.agregar_respuesta(r1_no);

    // Respuestas para p2 (¿Es de última generación?)
    respuesta r2_si(3, "Sí", &p4);      // Sí -> va a p4
    respuesta r2_no(4, "No", &p5);      // No -> va a p5

    p2.agregar_respuesta(r2_si);
    p2.agregar_respuesta(r2_no);

    // Respuestas para p4 (¿Tiene 5G?)
    respuesta r4_si(5, "Sí", nullptr);  // Fin
    respuesta r4_no(6, "No", nullptr);  // Fin

    p4.agregar_respuesta(r4_si);
    p4.agregar_respuesta(r4_no);

    // Respuestas para p5 (¿Cuántas horas diarias lo usa?)
    respuesta r5_si(7, "Sí", nullptr);  // Fin
    respuesta r5_no(8, "No", nullptr);  // Fin

    p5.agregar_respuesta(r5_si);
    p5.agregar_respuesta(r5_no);

    cout << "=== ESTRUCTURA DE LA ENCUESTA ===\n";
    p1.mostrar_estructura();

    cout << "\n=== RESPONDER ENCUESTA ===\n";
    p1.ejecutar_pregunta();

    return 0;
}