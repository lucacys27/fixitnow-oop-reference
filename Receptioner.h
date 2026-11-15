#include "Angajat.h"
#include <vector>
#pragma once

class Receptioner : public Angajat
{
private:
    std::vector<int> idCereriInregistrate;

public:
    Receptioner(int, std::string, std::string, std::string, Data, std::string);
    void adaugaCerere(int idCerere);
    double calculeazaSalariu() const override;
    void afisare() const override;
};
