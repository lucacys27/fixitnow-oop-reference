#include "Electrocasnic.h"
#pragma once

class Televizor : public Electrocasnic
{
private:
    double diagonala;

public:
    Televizor(std::string, std::string, int, double, double);
    std::string getTip() const override;
    void afisare() const override;
};
