#include <iostream>

using namespace std;

class viaje{
public:
    virtual double get_precio()=0;
    virtual int get_horas(){return horas;};
    viaje(int horas){this->horas=horas;};
protected:
    int horas;
};

class colectivo:public viaje
{
public:
    double get_precio()
    {
        return kilometros*8;
    }
int get_horas()
    {return horas;}
    colectivo(int horas,int kilometros):viaje(horas){this->kilometros=kilometros;};

private:
    int kilometros;
};

class avion:public viaje
{
public:
double get_precio()
    {
    return (costo_ida+costo_vuelta)*1.2;
    }

    avion(int horas,double costo_ida,double costo_vuelta):viaje(horas+2){this->costo_ida=costo_ida;this->costo_vuelta=costo_vuelta;};
private:
    double costo_ida;
    double costo_vuelta;
};

class combinado:public viaje
{
private:
    avion v1;
    colectivo c1;
public:
    double get_precio()
    {
        return v1.get_precio()+c1.get_precio();
    }
    combinado(avion v, colectivo c)
        : viaje(v.get_horas() + c.get_horas()),
        v1(v),
        c1(c)
    {
    }
};

int main()
{
    colectivo c(6, 500);          // 6 horas, 500 km
    avion a(3, 20000, 18000);     // 3 horas de vuelo (+2 del aeropuerto)

    combinado viaje(a, c);

    cout << "=== Colectivo ===" << endl;
    cout << "Horas: " << c.get_horas() << endl;
    cout << "Precio: $" << c.get_precio() << endl;

    cout << "\n=== Avion ===" << endl;
    cout << "Horas: " << a.get_horas() << endl;
    cout << "Precio: $" << a.get_precio() << endl;

    cout << "\n=== Combinado ===" << endl;
    cout << "Horas: " << viaje.get_horas() << endl;
    cout << "Precio: $" << viaje.get_precio() << endl;

    return 0;
}
