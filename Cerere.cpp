#include <iostream>
#include "Cerere.h"

using namespace std;

Cerere::Cerere(int p1, Electrocasnic *p2, Data p3, int p4, int p5)
    : id(p1), electrocasnic(p2), dataDepunere(p3), oraDepunere(p4), complexitate(p5)
{
    this->status = "Neinregistrat";
    this->idTehnicianAsignat = -1;
    int vechime = 2025 - this->electrocasnic->getAn();
    if (vechime == 0)
        vechime = 1;
    this->durataEstimata = vechime * this->complexitate;
    this->durataRamasa = this->durataEstimata;
    this->pretReparatie = this->electrocasnic->getPret() * this->durataEstimata;
}

Cerere::~Cerere()
{
    if (this->electrocasnic != nullptr)
        delete this->electrocasnic;
}

void Cerere::asigneazaTehnician(int idTehnician)
{
    this->idTehnicianAsignat = idTehnician;
    this->status = "In Lucru";
}

void Cerere::decrementeazaTimp()
{
    if (this->durataRamasa > 0)
        this->durataRamasa--;
    if (this->durataRamasa == 0)
        this->status = "Finalizata";
}

bool Cerere::esteFinalizata() const
{
    if (this->durataRamasa == 0)
        return 1;
    else
        return 0;
}

int Cerere::getId() const
{
    return this->id;
}

string Cerere::getStatus() const
{
    return this->status;
}

Electrocasnic *Cerere::getElectrocasnic() const
{
    return this->electrocasnic;
}

int Cerere::getDurataRamasa() const
{
    return this->durataRamasa;
}

int Cerere::getIdTehnician() const
{
    return this->idTehnicianAsignat;
}

int Cerere::getDurataEstimata() const
{
    return this->durataEstimata;
}

double Cerere::getPretReparatie() const
{
    return this->pretReparatie;
}

int Cerere::getOraDepunere() const 
{
    return this->oraDepunere;
}

void Cerere::setStatus(string statusNou) 
{
    this->status = statusNou;
}

void Cerere::afisare() const
{
    cout << "Cerere ID: " << this->id << endl;
    cout << "Data depunere: " << this->dataDepunere.toString() << " Ora: " << this->oraDepunere << endl;
    cout << "Status: " << this->status << endl;
    cout << "Complexitate: " << this->complexitate << "/5" << endl;
    cout << "Durata estimata: " << this->durataEstimata << " unitati (Ramase: " << this->durataRamasa << ")" << endl;
    cout << "Pret Reparatie: " << this->pretReparatie << endl;
    if (this->idTehnicianAsignat != -1)
        cout << "Tehnician Asignat cu ID-ul: " << this->idTehnicianAsignat << endl;
    cout << "Detalii Aparat:" << endl;
    this->electrocasnic->afisare();
}
