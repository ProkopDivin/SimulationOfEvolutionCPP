#include "InputEntities.h"


void PlantSpecies::print()
{
	std::cout << "Plant parameters:" << std::endl;
	std::cout << "name:" << name << std::endl;
	std::cout << "count:" << count << std::endl;
	std::cout << "size:" << size << std::endl;
	std::cout << "nourishment:" << nourishment << std::endl;
	std::cout << "food changer:" << std::endl;
	std::cout << "	min:" << changer.min << std::endl;
	std::cout << "	max:" << changer.max << std::endl;
	std::cout << "	interval:" << changer.interval << std::endl;
	std::cout << "	times:" << changer.times << std::endl;
	std::cout << std::endl;
}


void AnimalSpecies::print()
{
	std::cout << "Animal parameters:" << std::endl;
	std::cout << "name:" << name << std::endl;
	std::cout << "size:" << size << std::endl;
	std::cout << "sense:" << sense << std::endl;
	std::cout << "dexterity:" << dexterity << std::endl;
	std::cout << "reproduction:" << reproduction << std::endl;
	std::cout << "mutation:" << mutation << std::endl;
	std::cout << "count:" << count << std::endl;
	std::cout << "food_multiplicators:" << std::endl;
	std::cout << "	meat:" << food.meet << std::endl;
	std::cout << "	plant:" << food.plants << std::endl;
	std::cout << std::endl;
}

void Header::print()
{
	std::cout << "header parameters:" << std::endl;
	std::cout << "days:" << days << std::endl;
	std::cout << "map_width:" << map_width << std::endl;
	std::cout << "map_higth:" << map_higth << std::endl;
	std::cout << "calculator " << calculator->to_string() << std::endl;

	
	
	std::cout << std::endl;

}




