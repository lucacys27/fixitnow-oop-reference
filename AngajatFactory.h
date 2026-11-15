#include <iostream>
#include <string>
#include "Angajat.h"
#pragma once

class AngajatFactory
{
public:
    static Angajat* creeazaAngajat(std::string);
};
