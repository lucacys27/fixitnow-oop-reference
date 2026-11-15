#include <iostream>
#include <string>
#include <cctype> //Biblioteca pt isdigit!
#include "ValidatorCNP.h"

using namespace std;

bool ValidatorCNP::eCNPValid(string cnp)
{
    if (cnp.length() != 13)
        return 0;

    for (char c : cnp)
        if (!isdigit(c))
            return 0;

    int cheie[] = {2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9};
    long suma = 0;
    for (int i = 0; i < 12; i++)
    {
        int cifraCnp = cnp[i] - '0';
        suma += (cifraCnp * cheie[i]);
    }

    int rest = suma % 11;
    int cifraControlCalculata;

    if (rest == 10)
        cifraControlCalculata = 1;
    else
        cifraControlCalculata = rest;

    int cifraControlReala = cnp[12] - '0';

    if (cifraControlCalculata == cifraControlReala)
        return 1;
    else
        return 0;
}
