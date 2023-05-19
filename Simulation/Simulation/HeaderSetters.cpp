#include "InputEntities.h"


void Header::setDays(int x)
{
    if (x > 0) {
        days = x;
    }
    else {
        throw std::invalid_argument("Error: days in header must be grater or equal  1");
    }
}

void Header::setDivider(float x)
{
    if (x > 0) {
        divider = x;
    }
    else {
        throw std::invalid_argument("Error: nutrition_divider in header must be grater or equal  1");
    }
}

void Header::setMap_width(int x)
{
    if (x > 0&& x<10001) {
        map_width = x;
    }
    else {
        throw std::invalid_argument("Error: map_width in header must be in interval [1-10000]");
    }
}

void Header::setMap_higth(int x)
{
    if (x > 0&& x<10001) {
        map_higth = x;
    }
    else {
        throw std::invalid_argument("Error: map_higth in header must be in interval [1-10000]");
    }
}


void Header::setCalculator(int x, float size, float sense, float dexterity)
{
    if (x >= 0 && size>0 && sense>0 && dexterity>0) {
        
        
        switch (x) {
        case 0:
            calculator =std::make_shared<Calculator>(Calculator(size, sense, dexterity) );
            break;
        case 1:
            calculator = std::make_shared<PlusCalculator> (PlusCalculator(size, sense, dexterity));
            break;
        case 2:
            calculator = std::make_shared<KineticCalculator>(KineticCalculator(size, sense, dexterity));
            break;
        case 3:
            calculator = std::make_shared< Calculator2>(Calculator2(size, sense, dexterity));
            break;
        default:
            throw std::invalid_argument("Error:calculator must be integer smaller integer, not enought calculators");

        }
    }
    else {
        throw std::invalid_argument("Error:calculator must be non negative integer");
    }
}
//auto calc2 = dynamic_cast<PlusCalculator>(calculator);