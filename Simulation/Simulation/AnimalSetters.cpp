#include "InputEntities.h"




void AnimalSpecies::setId(int x)
{
    if (x >= 0) {
        id = x;
    }
    else {
        throw std::invalid_argument(" id of animal must be positive or 0 ");
    }

}

void AnimalSpecies::setName(std::string x)
{
    if (x.size() == 2) {
        name = x;
    }
    else {
        throw std::invalid_argument(" name of animal must have length 2");
    }

}

void AnimalSpecies::setSize(float x)
{
    if (x > 0) {
        size = x;
    }
    else {
        throw std::invalid_argument(" size of animal must be positive ");
    }

}

void AnimalSpecies::setSense(float x)
{
    if (x >= 1) {
        sense = x;
    }
    else {
        throw std::invalid_argument(" sense of animal must be grater or equal  1");
    }
}

void AnimalSpecies::setDexterity(float x)
{
    if (x >= 0) {
        dexterity = x;
    }
    else {
        throw std::invalid_argument(" dexterity of animal must be grater or equal  0");
    }
}



void AnimalSpecies::setReproduction(float x)
{
    if (x >= 1) {
        reproduction = x;
    }
    else {
        throw std::invalid_argument(" reproduction of animal must be grater or equal  1");
    }
}

void AnimalSpecies::setMutation(float x)
{
    if (x >= 0 && x < 1) {
        mutation = x;
    }
    else {
        throw std::invalid_argument(" mutation of animal must be grater or equal  0 and less than 1");
    }
}

void AnimalSpecies::setCount(int x)
{
    if (x >= 0) {
        count = x;
    }
    else {
        throw std::invalid_argument(" count of animal must be grater or equal  0");
    }
}

void AnimalSpecies::setFood(float x, float y)
{
    if (x >= 0 && y >= 0) {
        food = Nutrions_Multiplicators(x, y);
    }
    else {
        throw std::invalid_argument(" nutrions multiplicators of animal must be grater or equal  0");
    }
}

void AnimalSpecies::setStop_eat(float x)
{
    if (x >= 1) {
        stop_eat = x;
    }
    else {
        throw std::invalid_argument("  stop_eat of animal must be grater or equal  1");
    }
}
