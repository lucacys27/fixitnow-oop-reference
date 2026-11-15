#include <iostream>
#include "Receptioner.h"

using namespace std;

Receptioner::Receptioner(int p1, string p2, string p3, string p4, Data p5, string p6)
    : Angajat(p1, p2, p3, p4, p5, p6) {}

void Receptioner::adaugaCerere(int idCerere)
{
    this->idCereriInregistrate.push_back(idCerere);
}

double Receptioner::calculeazaSalariu() const
{
    double salariu = 4000;
    int aniVechime = this->getVechime();
    int bonusuri = aniVechime / 3;
    salariu += (4000 * 0.05 * bonusuri);
    if (this->orasDomiciliu != "Bucuresti")
        salariu = salariu + 400;
    return salariu;
}

void Receptioner::afisare() const
{
    Angajat::afisare();
    cout << "Functie: Receptioner" << endl;
    cout << "Cereri inregistrate: " << this->idCereriInregistrate.size() << endl;
    cout << "Salariu curent: " << this->calculeazaSalariu() << endl;
}
