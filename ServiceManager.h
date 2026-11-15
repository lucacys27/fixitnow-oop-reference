#include <iostream>
#include <vector>
#include <map>
#include "Angajat.h"
#include "Electrocasnic.h"
#include "Cerere.h"
#pragma once

class ServiceManager
{
private:
    std::vector<Angajat *> angajati;
    std::vector<Electrocasnic *> electrocasniceSuportate;
    std::vector<Cerere *> cereri;
    static ServiceManager *instance;
    std::map<std::string, int> cereriRefuzate;
    ServiceManager();

public:
    static ServiceManager *getInstance();
    void adaugaAngajat(Angajat *);
    void adaugaElectrocasnic(Electrocasnic *);
    void adaugaCerere(Cerere *);
    bool stergeAngajat(int);
    void modificaNumeAngajat(int, std::string);

    void incarcaAngajati(std::string);
    void incarcaElectrocasnice(std::string);
    void incarcaCereri(std::string);

    Angajat *getAngajatDupaId(int idCautat);
    int getNrCereriActivePentruTehnician(int);
    int gasesteCelMaiBunTehnician(Cerere *c);
    void runSimulare();

    void afiseazaAngajatDupaCNP(std::string) const;
    void stergeElectrocasnic(std::string, std::string);
    void afiseazaCereriRefuzatePeEcran() const;
    void adaugaElectrocasnicSuportat(Electrocasnic *);

    void genereazaRapoarteCSV();
    void afiseazaTotiAngajatii() const;
    void afiseazaElectrocasnice() const;
    void afiseazaToateCererile() const;
    ~ServiceManager();
};
