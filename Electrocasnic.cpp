#include <iostream>
#include "Electrocasnic.h"

using namespace std;

Electrocasnic::Electrocasnic(string p1, string p2, int p3, double p4)
    : marca(p1), model(p2), anFabricatie(p3), pretCatalog(p4) {}

double Electrocasnic::getPret() const
{
    return this->pretCatalog;
}

int Electrocasnic::getAn() const
{
    return this->anFabricatie;
}

string Electrocasnic::getMarca() const
{
    return this->marca;
}

string Electrocasnic::getModel() const
{
    return this->model;
}

void Electrocasnic::afisare() const
{
    cout << "Tip: " << this->getTip() << endl; 
    cout << "Marca: " << this->marca << endl;
    cout << "Model: " << this->model << endl;
    cout << "An fabricatie: " << this->anFabricatie << endl;
    cout << "Pret catalog: " << this->pretCatalog << endl;
}
