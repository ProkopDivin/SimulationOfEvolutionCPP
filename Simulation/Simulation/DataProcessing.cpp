

#include "DataProcessing.h"

void Statistic::record(const Map& map)
{
	beginRecord(map);
	processMap(map);
}

void Statistic::load(const Map& map, int days, const std::string& delimeter)
{  
	d = delimeter;
    records = 1+days;//days +starting point
	for (auto&& p : map.getPlants()) {
		std::vector<PlantsStat> stats;
		stats.reserve(records);   //records ==max length of vector  
		plantsStats.insert({ p.getId(),std::move(stats) });
	}
	for (auto&& s : map.getSpecies()) {
		std::vector<SpeciesStat> stats; 
		stats.reserve(records);
		speciesStats.insert({ s.getId(),std::move(stats) });
	}
	record(map);

}

void Statistic::saveStats(const std::string& fileName) const
{
	std::ofstream file(fileName);
	std::vector<int> keys_plants;
	std::vector<int> keys_species;
	for (auto&& pair : plantsStats) {keys_plants.push_back(pair.first);}
	for (auto&& p : speciesStats) { keys_species.push_back(p.first); }
	if (file.is_open()) {
		file << makeHeadline(keys_plants, keys_species);
		for (int i = 0; i < records; ++i) { //i is number of the day 
			file << i << d;
			//save one day to the file 
			for (auto&& key : keys_plants) {
				file  << plantsStats.at(key)[i].to_string(d);
			}
			for (auto&& key : keys_species) {
				file << speciesStats.at(key)[i].to_string(d);
			}
			file << std::endl;
		}
		std::cout << " results save to : " << fileName << std::endl;
	}
	else {
		std::cout << " unable open file: " << fileName << std::endl;
	}

}

std::string Statistic::makeHeadline(const std::vector<int>& plants, const std::vector<int>& species)const
{
	std::stringstream ss;
	ss << "day,";
	for (auto&& key : plants) { ss << key<< "_plant_count"<<d; }
	for (auto&& key : species) { 
		ss << key<< "_species_size"<<d; 
		ss << key<< "_species_sense"<<d; 
		ss << key<< "_species_dexterity"<<d; 
		ss << key << "_species_count"<<d; 
	}
	ss << std::endl;
	return ss.str();
}

void Statistic::beginRecord(const Map& map)
{
	recorded = true;
	for (auto&& p : map.getPlants()) { plantsStats[p.getId()].push_back(PlantsStat(0)); }
	for (auto&& s : map.getSpecies()) { speciesStats[s.getId()].push_back(SpeciesStat(0, 0, 0, 0)); }
}

void Statistic::processMap(const Map& map)
{
	for (auto&& coor : map.getAnimalCoor()) {
		Item* item = map.getMap()[coor.x][coor.y].get();
		if (item) {
			if (item->getType() == ANIMAL) {
				const Animal* a = dynamic_cast<Animal*>(item);
				speciesStats[a->species->getId()].back().noteAnimal(a->getSize(), a->getSense(), a->getDexterity(), 1);
			}
		}
	}
	for (auto&& plant : map.getPlants()) {

		plantsStats[plant.getId()].back().notePlant(plant.getCount());
	}
}

std::string SpeciesStat::to_string(const std::string& d)const
{
	std::stringstream ss;
	if (count > 0) {
		ss << (size / count) << d << (sense / count) << d << (dexterity / count) << d << count << d;
	}
	else {
		ss << d << d << d << count << d;
	}
	return ss.str();
}

std::string PlantsStat::to_string(const std::string& d)const
{
	return std::to_string(count) + d;
}
