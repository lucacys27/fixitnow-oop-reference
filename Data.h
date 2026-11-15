#include <iostream>
#include <string>
#pragma once

class Data
{
private:
    int zi;
    int luna;
    int an;

public:
    Data() = default;
    Data(int, int, int);
    int getZi() const;
    int getLuna() const;
    int getAn() const;
    std::string toString() const;
    bool operator==(const Data &) const;
    bool eDataValida() const;
};
