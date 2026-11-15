#include "Electrocasnic.h"
#pragma once

class Frigider : public Electrocasnic
{
private:
    bool areCongelator;

public:
    Frigider(std::string, std::string, int, double, bool);
    std::string getTip() const override;
    void afisare() const override;
};
