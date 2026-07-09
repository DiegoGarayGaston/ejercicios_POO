#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
struct Estadistica
{
    int anio;
    int litros = 0;
    int monto = 0;
};
class vino
{
protected:
    int nro;
    int cant_de_litros;
    int anio_de_produccion;
    int anios_espera;
    int precio_litro;

public:
    vino(int n, int litros, int anio, int espera, int precio)
    {
        nro = n;
        cant_de_litros = litros;
        anio_de_produccion = anio;
        anios_espera = espera;
        precio_litro = precio;
    }

    int anio_venta()
    {
        return anio_de_produccion + anios_espera;
    }

    int monto()
    {
        return cant_de_litros * precio_litro;
    }

    int get_litros()
    {
        return cant_de_litros;
    }

    int get_anio_produccion()
    {
        return anio_de_produccion;
    }

    string get_info()
    {
        return to_string(nro) + "//" +
               to_string(anio_de_produccion) + ".." +
               to_string(cant_de_litros);
    }

    virtual ~vino() = default;
};
class mesa : public vino
{
public:
    mesa(int n, int litros, int anio)
        : vino(n, litros, anio, 1, 120)
    {
    }
};
class premium : public vino
{
public:
    premium(int n, int litros, int anio)
        : vino(n, litros, anio, 2, 200)
    {
    }
};
class especial : public vino
{
public:
    especial(int n, int litros, int anio)
        : vino(n, litros, anio, 3, 320)
    {
    }
};
struct Estadistica
{
    int anio;
    int litros = 0;
    int monto = 0;
};



class vitinicola
{
private:
    vector<vino*> vinos;

    // Estadísticas por año de venta
    vector<Estadistica> generar_estadisticas()
    {
        vector<Estadistica> estadisticas;

        for (auto v : vinos)
        {
            auto it = find_if(
                estadisticas.begin(),
                estadisticas.end(),
                [v](const Estadistica& e)
                {
                    return e.anio == v->anio_venta();
                });

            if (it == estadisticas.end())
            {
                Estadistica e;
                e.anio = v->anio_venta();
                e.litros = v->get_litros();
                e.monto = v->monto();

                estadisticas.push_back(e);
            }
            else
            {
                it->litros += v->get_litros();
                it->monto += v->monto();
            }
        }

        return estadisticas;
    }

public:
    void venta_por_año(int año)
    {
        for(auto it : vinos)
        {
            if(año < it->anio_venta())
            {
                cout << it->get_info() << endl;
            }
        }
    }

    void cargar_binario(const char* nombre)
    {
        ifstream arch(nombre, ios::binary);

        if (!arch)
            return;

        int nro;
        char tipo;
        int litros;
        int anio;

        while (arch.read((char*)&nro, sizeof(int)))
        {
            arch.read((char*)&tipo, sizeof(char));
            arch.read((char*)&litros, sizeof(int));
            arch.read((char*)&anio, sizeof(int));

            switch(tipo)
            {
            case 'M':
                vinos.push_back(new mesa(nro, litros, anio));
                break;
            case 'P':
                vinos.push_back(new premium(nro, litros, anio));
                break;
            case 'E':
                vinos.push_back(new especial(nro, litros, anio));
                break;
            }
        }

        arch.close();
    }

    void txt_anios(int año)
    {
        ofstream arch("salida.txt");

        for(int i = 2020; i <= 2023; i++)
        {
            for(auto it : vinos)
            {
                if(i == it->anio_venta())
                {
                    arch << it->get_info() << endl;
                }
            }
        }

        arch.close();
    }

    // 1) Los 5 años que se produjeron más litros
    void top5_produccion()
    {
        vector<Estadistica> produccion;

        for(auto v : vinos)
        {
            auto it = find_if(
                produccion.begin(),
                produccion.end(),
                [v](const Estadistica& e)
                {
                    return e.anio == v->get_anio_produccion();
                });

            if(it == produccion.end())
            {
                Estadistica e;
                e.anio = v->get_anio_produccion();
                e.litros = v->get_litros();

                produccion.push_back(e);
            }
            else
            {
                it->litros += v->get_litros();
            }
        }

        sort(
            produccion.begin(),
            produccion.end(),
            [](const Estadistica& a, const Estadistica& b)
            {
                return a.litros > b.litros;
            });

        cout << "Top 5 años con mayor producción\n";

        for(size_t i = 0; i < 5 && i < produccion.size(); i++)
        {
            cout << produccion[i].anio
                 << " -> "
                 << produccion[i].litros
                 << " litros\n";
        }
    }

    // 2) Año que se podrá vender más vino
    void año_mas_venta()
    {
        auto estadisticas = generar_estadisticas();

        auto it = max_element(
            estadisticas.begin(),
            estadisticas.end(),
            [](const Estadistica& a, const Estadistica& b)
            {
                return a.litros < b.litros;
            });

        if(it != estadisticas.end())
        {
            cout << "Año con más litros vendidos: "
                 << it->anio
                 << " (" << it->litros << " litros)\n";
        }
    }

    // 3) Año con mayor monto de venta
    void año_mayor_monto()
    {
        auto estadisticas = generar_estadisticas();

        auto it = max_element(
            estadisticas.begin(),
            estadisticas.end(),
            [](const Estadistica& a, const Estadistica& b)
            {
                return a.monto < b.monto;
            });

        if(it != estadisticas.end())
        {
            cout << "Año con mayor monto: "
                 << it->anio
                 << " ($" << it->monto << ")\n";
        }
    }

    ~vitinicola()
    {
        for(auto v : vinos)
            delete v;
    }
};


int main()
{
    return 0;
}
