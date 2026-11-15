#include <iostream>
#include <string>
#pragma once

class Electrocasnic
{
protected:
    std::string marca;
    std::string model;
    int anFabricatie;
    double pretCatalog;

public:
    Electrocasnic(std::string, std::string, int, double);
    virtual ~Electrocasnic() = default;
    virtual std::string getTip() const = 0;
    virtual void afisare() const;
    double getPret() const;
    int getAn() const;
    std::string getMarca() const;
    std::string getModel() const;
};
