#pragma once
#include<unordered_map>
#include<string>
#include<sstream>
#include "Map.h"
/// <summary>
/// -this code is for processing statistics
/// -save how many annimals and food where on the map each day 
/// - for every kind of animal it also save sum of size,sense and dexterity (to calculate average values)
/// </summary>

/// <summary>
/// represents statistic for one kind of animal
/// </summary>
struct SpeciesStat {
public:

	SpeciesStat(float size, float sense, float dexterity, int count):size(size),sense(sense),dexterity(dexterity),count(count) {}
	void noteAnimal(float si, float se, float de, int co) {
		size += si;
		sense += se;
		dexterity += de;
		count += co;
	}
	std::string to_string(const std::string& delimeter) const ;
private:
	float size;
	float sense;
	float dexterity;
	int count;
};

/// <summary>
/// represets one kind of food
/// </summary>
struct PlantsStat {
public:
	PlantsStat(int count):count(count){} 
	void notePlant(int co) {
		count = co;
	}
	std::string to_string(const std::string& delimeter) const;
private:
	int count;
};

/// <summary>
/// main class for saving  statistics
/// </summary>
class Statistic {
public:
	void load(const Map& map,int  days, const std::string& delimetr); //string will be small 
	
	/// <summary>
	/// -call after function: beginRecord()
	/// - make statistic for one day
	/// </summary>
	/// <param name="map"> represent whole enviroment of this simulation</param>
	void record(const Map& map);
	void saveStats(const std::string& fileName) const;
	bool recorded = false;
private:
	
	std::string d;
	/// <summary>
	/// make first line in csv file 
	/// </summary>
	/// <param name="plants"> vectotr of id of plants(plant=one kind of food)</param>
	/// <param name="species"> vector of id  of species (specie= one kind of animal)</param>
	/// <returns>firs line in csv file </returns>
	std::string makeHeadline(const std::vector<int>& plants,const std::vector<int>& species) const;
	int records=0;
	/// <summary>
	/// begin record for new day
	/// </summary>
	/// <param name="map"></param>
	void beginRecord(const Map& map);
	/// <summary>
	/// go through the map and counting things on the map 
	/// </summary>
	/// <param name="map"></param>
	void processMap(const Map& map);
	/// <summary>
	/// here are all statistics for animals saved
	/// </summary>
	std::unordered_map<int, std::vector<SpeciesStat>> speciesStats;
	/// <summary>
	/// here are all statistic for food saved
	/// </summary>
	std::unordered_map<int, std::vector<PlantsStat>> plantsStats;

};