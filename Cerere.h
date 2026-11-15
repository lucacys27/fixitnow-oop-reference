#include <iostream>
#include <string>
#include "Data.h"
#include "Electrocasnic.h"
#pragma once

class Cerere
{
private:
    const int id;
    Electrocasnic *electrocasnic;
    Data dataDepunere;
    int oraDepunere;
    int complexitate;
    int durataEstimata;
    int durataRamasa;
    double pretReparatie;
    std::string status; // Asta poate sa fie: "In Asteptare", "In Lucru", "Finalizata"!
    int idTehnicianAsignat;

public:
    Cerere(int, Electrocasnic *, Data, int, int);
    ~Cerere();
    void asigneazaTehnician(int idTehnician);
    void decrementeazaTimp();
    bool esteFinalizata() const;
    int getId() const;
    std::string getStatus() const;
    Electrocasnic *getElectrocasnic() const;
    int getDurataRamasa() const;
    int getDurataEstimata() const;
    int getIdTehnician() const;
    void afisare() const;
    double getPretReparatie() const;
    int getOraDepunere() const;
    void setStatus(std::string);
};
