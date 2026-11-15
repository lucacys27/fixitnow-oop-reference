#include <iostream>
#include "Supervizor.h"

using namespace std;

Supervizor::Supervizor(int p1, string p2, string p3, string p4, Data p5, string p6) 
    : Angajat(p1, p2, p3, p4, p5, p6) {}

double Supervizor::calculeazaSalariu() const
{
    double salariu = 4000;
    salariu += (4000 * 0.20);
    int bonusuri = this->getVechime() / 3;
    salariu += (4000 * 0.05 * bonusuri);
    if (this->orasDomiciliu != "Bucuresti")
        salariu = salariu + 400;
    return salariu;
}

void Supervizor::afisare() const
{
    Angajat::afisare();
    cout << "Functie: Supervizor" << endl;
    cout << "Salariu curent: " << this->calculeazaSalariu() << endl;
}
