#include <iostream>
#include "MasinaSpalat.h"

using namespace std;

MasinaSpalat::MasinaSpalat(string p1, string p2, int p3, double p4, double p5)
    : Electrocasnic(p1, p2, p3, p4), capacitate(p5) {}

string MasinaSpalat::getTip() const
{
    return "MasinaSpalat";
}

void MasinaSpalat::afisare() const
{
    Electrocasnic::afisare();
    cout << "Capacitate: " << this->capacitate << endl;
}
