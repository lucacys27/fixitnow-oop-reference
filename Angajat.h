#include <iostream>
#include <string>
#include "Data.h"
#pragma once

class Angajat
{
protected:
    const int id;
    std::string nume;
    std::string prenume;
    std::string cnp;
    Data dataAngajarii;
    std::string orasDomiciliu;

public:
    Angajat(int, std::string, std::string, std::string, Data, std::string);
    virtual ~Angajat() = default;
    virtual double calculeazaSalariu() const = 0;
    virtual void afisare() const;
    int getId() const;
    std::string getNume() const;
    std::string getPrenume() const;
    std::string getCnp() const;
    int getVechime() const;
    std::string getOras() const;
    Data getDataAngajarii() const;
    void setNume(std::string);
};
