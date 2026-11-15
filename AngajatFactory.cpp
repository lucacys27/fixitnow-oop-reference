#include <iostream>
#include <sstream> //Asta e pentru spargerea textului cu spatiere virgulara CSV, very nice!
#include <vector>
#include <algorithm>
#include "AngajatFactory.h"
#include "Tehnician.h"
#include "Receptioner.h"
#include "Supervizor.h"

using namespace std;

Angajat *AngajatFactory::creeazaAngajat(string line)
{
    stringstream ss(line);
    string segment;
    vector<string> date;

    while (getline(ss, segment, ','))
    {
        segment.erase(remove(segment.begin(), segment.end(), ' '), segment.end());
        segment.erase(remove(segment.begin(), segment.end(), '\r'), segment.end());
        segment.erase(remove(segment.begin(), segment.end(), '\n'), segment.end());
        date.push_back(segment);
    }

    if (date.size() < 9)
        return nullptr;

    try
    {
        string tip = date[0];
        int id = stoi(date[1]);
        string nume = date[2];
        string prenume = date[3];
        string cnp = date[4];
        int zi = stoi(date[5]);
        int luna = stoi(date[6]);
        int an = stoi(date[7]);
        Data dataAngajarii(zi, luna, an);
        string oras = date[8];

        if (tip == "Receptioner")
            return new Receptioner(id, nume, prenume, cnp, dataAngajarii, oras);
        else if (tip == "Supervizor")
            return new Supervizor(id, nume, prenume, cnp, dataAngajarii, oras);
        else if (tip == "Tehnician")
            return new Tehnician(id, nume, prenume, cnp, dataAngajarii, oras);
    }
    catch (...)
    {
        return nullptr;
    }
    return nullptr;
}
