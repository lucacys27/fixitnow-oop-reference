#include "Electrocasnic.h"
#pragma once

class MasinaSpalat : public Electrocasnic
{
private:
    double capacitate;

public:
    MasinaSpalat(std::string, std::string, int, double, double);
    std::string getTip() const override;
    void afisare() const override;
};
