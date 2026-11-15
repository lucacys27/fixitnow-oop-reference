#include <iostream>
#include "Data.h"

using namespace std;

Data::Data(int p1, int p2, int p3) : zi(p1), luna(p2), an(p3) {}

int Data::getZi() const
{
    return this->zi;
}

int Data::getLuna() const
{
    return this->luna;
}

int Data::getAn() const
{
    return this->an;
}

string Data::toString() const
{
    return to_string(this->zi) + "." + to_string(this->luna) + "." + to_string(this->an);
}

bool Data::operator==(const Data &p) const
{
    if (p.zi == this->zi && p.luna == this->luna && p.an == this->an)
        return 1;
    else
        return 0;
}

bool Data::eDataValida() const
{
    if (this->an < 1900 || this->an > 2050) return false; 
    if (this->luna < 1 || this->luna > 12) return false;
    if (this->zi < 1) return false;
    switch (this->luna)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (this->zi > 31) return false;
            break;

        case 4: case 6: case 9: case 11:
            if (this->zi > 30) return false;
            break;

        case 2:
        {
            bool eBisect = (this->an % 4 == 0 && this->an % 100 != 0) || (this->an % 400 == 0);
            int zileMax = eBisect ? 29 : 28;
            if (this->zi > zileMax) return false;
            break;
        }
        
        default:
            return false;
    }

    return true;
}
