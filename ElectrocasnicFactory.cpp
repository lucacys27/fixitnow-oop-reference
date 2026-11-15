#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "ElectrocasnicFactory.h"
#include "Frigider.h"
#include "Televizor.h"
#include "MasinaSpalat.h"

using namespace std;

Electrocasnic *ElectrocasnicFactory::creeazaElectrocasnic(string line)
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

    if (date.size() < 5)
        return nullptr;

    try
    {
        string tip = date[0];
        string marca = date[1];
        string model = date[2];
        int an = stoi(date[3]);
        double pret = stod(date[4]);

        if (tip == "Frigider")
        {
            bool areCongelator;
            if (stoi(date[5]) == 1)
                areCongelator = 1;
            else
                areCongelator = 0;
            return new Frigider(marca, model, an, pret, areCongelator);
        }
        else if (tip == "Televizor")
        {
            double diagonala = stod(date[5]);
            return new Televizor(marca, model, an, pret, diagonala);
        }
        else if (tip == "MasinaSpalat")
        {
            double capacitate = stod(date[5]);
            return new MasinaSpalat(marca, model, an, pret, capacitate);
        }
    }
    catch (...)
    {
        return nullptr;
    }
    return nullptr;
}
