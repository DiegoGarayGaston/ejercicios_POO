#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
struct PermisoBin
{
    int id;
    char nombre[100];
};
struct CargoBin
{
    int id;
    char nombre[100];
};
struct UsuarioBin
{
    int codigo;
    char nombre[200];
    int idCargo;
};
struct CargoPermisoBin
{
    int idCargo;
    int idPermiso;
};
class Permiso
{
private:
    int id;
    string nombre;

public:
    Permiso(int id=0,string nombre="")
    {
        this->id=id;
        this->nombre=nombre;
    }

    int getId() const
    {
        return id;
    }

    string getNombre() const
    {
        return nombre;
    }
};

class Cargo
{
protected:
    int id;
    string nombre;
    vector<Permiso*> permisos;

public:
    Cargo(int id=0,string nombre="")
    {
        this->id=id;
        this->nombre=nombre;
    }

    virtual vector<Permiso*> getPermisos() const
    {
        return permisos;
    }

    void agregarPermiso(Permiso *p)
    {
        permisos.push_back(p);
    }

    string getNombre() const
    {
        return nombre;
    }

    int cantidadPermisos() const
    {
        return permisos.size();
    }
};

class Usuario
{
private:
    int codigo;
    char nombre[200];
    Cargo *cargo;

public:
    Usuario(int codigo=0,const char *nom="",Cargo *cargo=nullptr)
    {
        this->codigo=codigo;
        strcpy(nombre,nom);
        this->cargo=cargo;
    }

    int getCodigo() const
    {
        return codigo;
    }

    Cargo* getCargo() const
    {
        return cargo;
    }

    string getNombre() const
    {
        return nombre;
    }
};
bool tienePermiso(vector<Usuario*> usuarios,
                  int codigoUsuario,
                  string permiso)
{
    for(auto usuario : usuarios)
    {
        if(usuario->getCodigo()==codigoUsuario)
        {
            vector<Permiso*> permisos=
                usuario->getCargo()->getPermisos();

            for(auto p : permisos)
            {
                if(p->getNombre()==permiso)
                    return true;
            }

            return false;
        }
    }

    return false;
}
vector<Cargo*> cargosConMasPermisos(vector<Cargo*> cargos)
{
    int mayor=0;

    for(auto c:cargos)
        mayor=max(mayor,c->cantidadPermisos());

    vector<Cargo*> resultado;

    copy_if(cargos.begin(),cargos.end(),
            back_inserter(resultado),
            [mayor](Cargo *c)
            {
                return c->cantidadPermisos()==mayor;
            });

    return resultado;
}
vector<string> permisosRepetidos(vector<Cargo*> cargos)
{
    map<string,int> contador;

    for(auto cargo:cargos)
    {
        set<string> usados;

        for(auto permiso:cargo->getPermisos())
            usados.insert(permiso->getNombre());

        for(auto nombre:usados)
            contador[nombre]++;
    }

    vector<string> resultado;

    for(auto dato:contador)
    {
        if(dato.second>1)
            resultado.push_back(dato.first);
    }

    return resultado;
}
vector<Usuario*> usuariosConMasPermisos(vector<Usuario*> usuarios)
{
    int mayor=0;

    for(auto u:usuarios)
    {
        mayor=max(mayor,
                    u->getCargo()->cantidadPermisos());
    }

    vector<Usuario*> resultado;

    copy_if(usuarios.begin(),usuarios.end(),
            back_inserter(resultado),
            [mayor](Usuario *u)
            {
                return u->getCargo()->cantidadPermisos()==mayor;
            });

    return resultado;
}