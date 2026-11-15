#include <iostream>
#include <string>
#include "Electrocasnic.h"
#pragma once

class ElectrocasnicFactory
{
public:
    static Electrocasnic *creeazaElectrocasnic(std::string);
};
