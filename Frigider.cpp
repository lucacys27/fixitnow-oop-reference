#include <iostream>
#include "Frigider.h"

using namespace std;

Frigider::Frigider(string p1, string p2, int p3, double p4, bool p5)
    : Electrocasnic(p1, p2, p3, p4), areCongelator(p5) {}

string Frigider::getTip() const
{
    return "Frigider";
}

void Frigider::afisare() const
{
    Electrocasnic::afisare();
    if (this->areCongelator == 1)
        cout << "Congelator: Da" << endl;
    else
        cout << "Congelator: Nu" << endl;
}
