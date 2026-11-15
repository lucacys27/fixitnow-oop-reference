#include "Angajat.h"
#pragma once

class Supervizor : public Angajat
{
public:
    Supervizor(int, std::string, std::string, std::string, Data, std::string);
    double calculeazaSalariu() const override;
    void afisare() const override;
};
