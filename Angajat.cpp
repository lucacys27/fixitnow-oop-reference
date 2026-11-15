#include <iostream>
#include "Angajat.h"

using namespace std;

Angajat::Angajat(int p1, string p2, string p3, string p4, Data p5, string p6)
    : id(p1), nume(p2), prenume(p3), cnp(p4), dataAngajarii(p5), orasDomiciliu(p6) {}

int Angajat::getId() const
{
    return this->id;
}

string Angajat::getNume() const
{
    return this->nume;
}

string Angajat::getCnp() const
{
    return this->cnp;
}

int Angajat::getVechime() const
{
    return 2025 - this->dataAngajarii.getAn();
}

string Angajat::getOras() const
{
    return this->orasDomiciliu;
}

string Angajat::getPrenume() const
{
    return this->prenume;
}

void Angajat::setNume(string numeComplet)
{
    size_t pozitieSpatiu = numeComplet.find(' ');
    if (pozitieSpatiu != string::npos) 
    {
        this->nume = numeComplet.substr(0, pozitieSpatiu);
        this->prenume = numeComplet.substr(pozitieSpatiu + 1);
    }
    else 
    {
        this->nume = numeComplet;
        this->prenume = "";
    }
}

Data Angajat::getDataAngajarii() const
{
    return this->dataAngajarii;
}

void Angajat::afisare() const
{
    cout << "ID: " << this->id << endl;
    cout << "Nume: " << this->nume << " " << this->prenume << endl;
    cout << "CNP: " << this->cnp << endl;
    cout << "Data Angajarii: " << this->dataAngajarii.toString() << endl;
    cout << "Domiciliu: " << this->orasDomiciliu << endl;
}
