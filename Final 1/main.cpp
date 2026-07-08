#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


class paquete
{
private:
    vector<paquete*> paquetes;
    int version;
    string codigo;
    string nombre;

public:
    int cantidad_dependencias()
    {
        return paquetes.size();
    }
    paquete(int version, const char* codigo, const char* nombre)
    {
        this->version = version;
        this->codigo = codigo;
        this->nombre = nombre;
    }


    string get_codigo()
    {
        return codigo;
    }


    string get_nombre()
    {
        return nombre;
    }


    vector<paquete*>& get_dependencias()
    {
        return paquetes;
    }


    void agregar_paquete(paquete* p)
    {
        paquetes.push_back(p);
    }


    string mostrar_dependencias(string espacios)
    {
        string salida;

        salida += espacios + nombre + "\n";

        for(auto dependencia : paquetes)
        {
            salida += dependencia->mostrar_dependencias(espacios + " ");
        }

        return salida;
    }


    friend ostream& operator<<(ostream& os, paquete& p)
    {
        os << p.mostrar_dependencias("");

        return os;
    }
};



class gestora
{
private:

    vector<paquete*> paquetes;


public:


    void agregar_paquete(paquete* p)
    {
        paquetes.push_back(p);
    }



    paquete* buscar_paquete(const string& codigo)
    {
        auto encontrado = find_if(
            paquetes.begin(),
            paquetes.end(),
            [&](paquete* p)
            {
                return p->get_codigo() == codigo;
            }
            );


        if(encontrado != paquetes.end())
            return *encontrado;


        return nullptr;
    }



    vector<paquete*> obtener_dependencias()
    {
        sort(
            paquetes.begin(),
            paquetes.end(),
            [](paquete* p1, paquete* p2)
            {
                return p1->cantidad_dependencias() > p2->cantidad_dependencias();
            }
            );

        return paquetes;
    }

    vector<paquete*> cinco_mayores_dependencias()
    {
        auto resultado = obtener_dependencias();
        if(resultado.size() > 5)
        {
            resultado.resize(5);
        }


        return resultado;
    }
    void sin_dependencias()
    {
        auto resultado = obtener_dependencias();

        cout << "Sin dependencias:\n";

        for(auto p : resultado)
        {
            if(p->cantidad_dependencias() == 0)
                cout << p->get_nombre() << endl;
        }
    }
};



int main()
{
    paquete app(1, "001", "MiApp");
    paquete qt(6, "002", "Qt");
    paquete cmake(3, "003", "CMake");
    paquete gcc(14, "004", "GCC");
    paquete glibc(2, "005", "glibc");
    paquete openssl(3, "006", "OpenSSL");
    paquete zlib(1, "007", "zlib");
    paquete curl(8, "008", "libcurl");
    paquete sqlite(3, "009", "SQLite");
    paquete python(3, "010", "Python");
    paquete pip(24, "011", "pip");
    paquete numpy(2, "012", "NumPy");
    paquete pandas(2, "013", "Pandas");
    paquete git(2, "014", "Git");
    paquete llvm(18, "015", "LLVM");
    paquete clang(18, "016", "Clang");
    paquete openjdk(21, "017", "OpenJDK");
    paquete maven(3, "018", "Maven");
    paquete gradle(8, "019", "Gradle");
    paquete nodejs(22, "020", "NodeJS");
    paquete npm(10, "021", "npm");
    paquete react(19, "022", "React");
    paquete vite(7, "023", "Vite");
    paquete typescript(5, "024", "TypeScript");


    // Dependencias

    app.agregar_paquete(&qt);
    app.agregar_paquete(&git);
    app.agregar_paquete(&python);
    app.agregar_paquete(&nodejs);


    qt.agregar_paquete(&cmake);
    qt.agregar_paquete(&gcc);
    qt.agregar_paquete(&openssl);
    qt.agregar_paquete(&zlib);


    gcc.agregar_paquete(&glibc);


    cmake.agregar_paquete(&gcc);


    git.agregar_paquete(&curl);
    git.agregar_paquete(&openssl);
    git.agregar_paquete(&zlib);


    curl.agregar_paquete(&openssl);
    curl.agregar_paquete(&zlib);


    python.agregar_paquete(&pip);
    python.agregar_paquete(&openssl);
    python.agregar_paquete(&zlib);
    python.agregar_paquete(&sqlite);


    pip.agregar_paquete(&numpy);
    pip.agregar_paquete(&pandas);


    llvm.agregar_paquete(&zlib);


    clang.agregar_paquete(&llvm);


    openjdk.agregar_paquete(&glibc);


    maven.agregar_paquete(&openjdk);


    gradle.agregar_paquete(&openjdk);


    nodejs.agregar_paquete(&npm);



    // Vector plano

    gestora g1;

    g1.agregar_paquete(&app);
    g1.agregar_paquete(&qt);
    g1.agregar_paquete(&cmake);
    g1.agregar_paquete(&gcc);
    g1.agregar_paquete(&glibc);
    g1.agregar_paquete(&openssl);
    g1.agregar_paquete(&zlib);
    g1.agregar_paquete(&curl);
    g1.agregar_paquete(&sqlite);
    g1.agregar_paquete(&python);
    g1.agregar_paquete(&pip);
    g1.agregar_paquete(&numpy);
    g1.agregar_paquete(&pandas);
    g1.agregar_paquete(&git);
    g1.agregar_paquete(&llvm);
    g1.agregar_paquete(&clang);
    g1.agregar_paquete(&openjdk);
    g1.agregar_paquete(&maven);
    g1.agregar_paquete(&gradle);
    g1.agregar_paquete(&nodejs);
    g1.agregar_paquete(&npm);
    g1.agregar_paquete(&react);
    g1.agregar_paquete(&vite);
    g1.agregar_paquete(&typescript);


    paquete* resultado = g1.buscar_paquete("001");


    if(resultado)
    {
        cout << "Encontrado:\n";
        cout << *resultado;
    }
    else
    {
        cout << "No encontrado";
    }
    cout << "\nCantidad de dependencias:\n";
    auto resultado1 = g1.obtener_dependencias();
    for(auto dato : resultado1)
    {
        cout<< dato->get_codigo() << "-> "<< dato->cantidad_dependencias() <<endl;
    }
    cout << "\n\n5 paquetes con mayor cantidad de dependencias:\n";
    auto mayores = g1.cinco_mayores_dependencias();
    for(auto dato : mayores)
    {
       cout<< dato->get_codigo() << "-> "<< dato->cantidad_dependencias() <<endl;
    }
    cout << "\n\nPaquetes sin dependencias:\n";
    g1.sin_dependencias();
    return 0;
}
