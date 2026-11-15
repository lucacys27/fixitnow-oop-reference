#include <iostream>
#include "Tehnician.h"

using namespace std;

Tehnician::Tehnician(int p1, string p2, string p3, string p4, Data p5, string p6)
    : Angajat(p1, p2, p3, p4, p5, p6), valoareReparatii(0.0), totalOreMuncite(0) {}

void Tehnician::adaugaCompetenta(string competenta)
{
    this->competente.push_back(competenta);
}

void Tehnician::adaugaReparatie(double valoare)
{
    this->valoareReparatii += valoare;
}

bool Tehnician::areCompetenta(string tip) const
{
    for (const string &c : this->competente)
    {
        if (c == tip)
            return 1;
    }
    return 0;
}

void Tehnician::resetareBonus()
{
    this->valoareReparatii = 0;
}

double Tehnician::calculeazaSalariu() const
{
    double salariu = 4000;
    int bonusuri = this->getVechime() / 3;
    salariu += (4000 * 0.05 * bonusuri);
    if (this->orasDomiciliu != "Bucuresti")
        salariu = salariu + 400;
    salariu += (this->valoareReparatii * 0.02);
    return salariu;
}

void Tehnician::adaugaOreMuncite(int ore)
{
    this->totalOreMuncite += ore;
}

int Tehnician::getTotalOreMuncite() const
{
    return this->totalOreMuncite;
}

void Tehnician::afisare() const
{
    Angajat::afisare();
    cout << "Functie: Tehnician" << endl;
    cout << "Competente: ";
    for (const string &c : this->competente)
        cout << c << ", ";
    cout << endl;
    cout << "Valoare reparatii luna asta: " << this->valoareReparatii << endl;
    cout << "Salariu curent: " << this->calculeazaSalariu() << endl;
}
