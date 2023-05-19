#include "InputEntities.h"

void PlantSpecies::setId(int x)
{
	if (x > -1) {
		id = x;
	}
	else {
		throw std::invalid_argument(" id of plants must be greater or equal to 0");
	}
}

void PlantSpecies::setActual_count(int x)
{
	actual_count = x;
}

void PlantSpecies::setName(std::string x)
{
	if (x.size() == 2) {
		name = x;
	}
	else {
		throw std::invalid_argument(" length of the name must be 2 characters ");
	}
}

void PlantSpecies::setCount(int x)
{
	if (x>=0) {
		count = x;
	}
	else {
		throw std::invalid_argument(" count of plants must be greater or equal to 0");
	}
}

void PlantSpecies::setSize(float x)
{
	if (x >= 0) {
		size = x;
	}
	else {
		throw std::invalid_argument(" size of plants must be non negative");
	}
}

void PlantSpecies::setNourishment(float x)
{
	if (x > 0) {
		nourishment = x;
	}
	else {
		throw std::invalid_argument(" nourishment  of plants must be greater than 0");
	}
}

void PlantSpecies::setChanger(int interval, float times, int max, int min)
{
	if (interval > 0 && times>0 && max>=min && min >=0) {
		changer = Food_changer(interval, times, max, min);
	}
	else {
		throw std::invalid_argument(" plans changer doesn`t support these parameters");
	}
}


