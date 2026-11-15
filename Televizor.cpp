#include <iostream>
#include "Televizor.h"

using namespace std;

Televizor::Televizor(string p1, string p2, int p3, double p4, double p5)
    : Electrocasnic(p1, p2, p3, p4), diagonala(p5) {}

string Televizor::getTip() const
{
    return "Televizor";
}

void Televizor::afisare() const
{
    Electrocasnic::afisare();
    cout << "Diagonala: " << this->diagonala << endl;
}
