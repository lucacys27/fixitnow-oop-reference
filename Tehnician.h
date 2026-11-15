#include "Angajat.h"
#include <vector>
#pragma once

class Tehnician : public Angajat
{
private:
    std::vector<std::string> competente;
    double valoareReparatii;
    int totalOreMuncite;

public:
    Tehnician(int, std::string, std::string, std::string, Data, std::string);
    void adaugaCompetenta(std::string);
    void adaugaReparatie(double);
    bool areCompetenta(std::string) const;
    double calculeazaSalariu() const override;
    void afisare() const override;
    void resetareBonus();
    void adaugaOreMuncite(int);
    int getTotalOreMuncite() const;
};
