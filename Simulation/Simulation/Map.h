#pragma once
#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <unordered_set>
#include <array>

#include "InputEntities.h"
#include "simulationEntitie.h"

#ifndef MAP_H_
#define MAP_H_
/// <summary>
/// for function get type Item
/// </summary>
 enum MapTypes
{
	ITEM = 0,
	FOOD = 1,
	ANIMAL = 2,
};

/// <summary>
/// represent thing on the map 
/// </summary>
class Item {
public:
	virtual MapTypes getType() const{ return ITEM; }
protected:

};
/// <summary>
/// the data structure where the simulation takes place
/// </summary>
using Enviroment = std::vector < std::vector<std::unique_ptr<Item>>>;


/// <summary>
/// an instance of this class represents one plant that can be eaten 
/// </summary>
class Food :public Item {
public:
	Food( PlantSpecies* p) { plant = p; }
	MapTypes getType() const override { return FOOD; }
	PlantSpecies* plant;
};

/// <summary>
/// for printing the map 
/// </summary>
class MapPrinter {
public:
	static void printMap(const Enviroment& map, const std::string& day, std::ostream& file);
private:
	// make horizontal line ---------
	static void printRowSeparator(std::ostream& file, size_t length);
};
/// <summary>
/// functions for loding the map and setting the simulation
/// </summary>
class MapLoading {
public:

protected:
	size_t tryes = 5; //5 random tryes befor dsearching for the first empty pozitions
	Generator random; 

	void resize_map(); //give the map its final size 
	void fill_map();  //fill the map with animals and food
	void putAnimals();
	void putFood();

	Coordinates RandomCoordinates();//give random coordinates to empty place
	template <typename T>
	Coordinates place_item(const T&  item) //place item on the map can be animal, food...
	{
		Coordinates coor = RandomCoordinates();
		if (coor.x > -1 && coor.y > -1) {
			std::unique_ptr<T> pointer = std::make_unique<T>(item);
			map[coor.x][coor.y] = move(pointer);
		}
		return coor;		
	}

	int width = 0;
	int hight = 0;
	/// <summary>
	/// diferrent kind of food on the map 
	/// </summary>
	std::vector<PlantSpecies> plants; 
	/// <summary>
	/// different kind of animals in the map 
	/// </summary>
	std::vector<AnimalSpecies> species;

	Enviroment map; //main datastructure

	std::shared_ptr< Calculator> calculator = nullptr;//to calculate hunger
};


/// <summary>
/// can simulate one day of the simulation 
/// </summary>

class Map:public MapLoading {
public:
	const Enviroment& getMap()const { return map; }
	void Day(int date);
	int getWidth()const { return width; }
	int getHight()const { return hight; }
	const std::shared_ptr<Calculator> getCalculator() const { return calculator; }
	void load(Parameters parameters);
	bool IsEmpty(Coordinates)const;

	const std::vector<AnimalSpecies>& getSpecies() const { return species; }
	const std::vector<PlantSpecies >& getPlants() const { return plants; }
	const std::unordered_set<Coordinates, Coordinates::HashFunction>& getAnimalCoor() const { return animalsCoordinates; }

protected:

	void findAnimals();//modify animals coordinates
	void moveAnimals();
	void changeFoodCount(int date);

	std::unordered_set<Coordinates, Coordinates::HashFunction> animalsCoordinates; //coordinates of living  animals
	std::unordered_set<Coordinates, Coordinates::HashFunction> takenFields; //to know who moved
	
	float divider=1;
};
/// <summary>
/// represent animal on the map 
/// </summary>
class Animal : public Item {
public:
	
	float getSize()const;
	float getSense()const;
	float getDexterity()const;
	
	Animal(const Animal& animal);
	Animal(float siz, float sense,  float dexterity,  AnimalSpecies* s) : sense(sense), dexterity(dexterity) { size = siz; species = s; }
	MapTypes getType() const  override  { return ANIMAL; }
	Animal makeAnimal( Generator& random);
    /// <summary>
    /// update eaten 
    /// </summary>
    /// <param name="item"> possible foood source </param>
    /// <param name="max_food"> how much can he eat</param>
    void Eat(std::unique_ptr<Item> item,float max_food);

	static const int rounds = 3; //into this number of steps will be animal moving divided 

	float eaten = 0;
	AnimalSpecies* species; //pointer to is own kind (and informations)


	/// <summary>
	/// return coordinates of place where the animal will move. 
	/// in this coordinates myst be the movement possibe in case this place doesnt exist return actual coordinates 
	/// </summary>
	/// <param name="map"> data for the simulation to se animals around  </param>
	/// <param name="coor"> here it is standing </param>
	/// <param name="turn"> in this round of movement it is </param>
	/// <param name="random"> to introduce chance </param>
	/// <returns></returns>
	Coordinates MakeStep(const Map& map, Coordinates coor, int turn, Generator& random);
	const static int moves = 4; //down, up, right , left 
	const static int moves_dimension = 2; // [x,y] coordinates
	const static int number_of_mutations = 8;//2^3 number of combination of mutations
	const static int number_of_mutating_parameters = 3;//size ,sense ,dexterity
private:
 
    static const constexpr std::array<std::array<int, moves_dimension>, moves> relativeMoves = {{{1, 0},//posible moves of the animal with lenght of 1
																										  {-1,0},
																										  {0,-1},
																										  {0,1}} };  /**/
	/// <summary>
/// it says if mutating parameter will increase or decrease 
/// {1,1,-1} means size and sense will be increased and dexterity will be decreased
/// </summary>

    static const constexpr std::array<std::array<int, number_of_mutating_parameters>, number_of_mutations>  mutations = {{{1, 1, 1},//combinatios of how the stats can change
	                                                                                                                     { 1,-1,1 },
	                                                                                                                     { 1,1,-1 },
	                                                                                                                     { 1,-1,-1},
	                                                                                                                     { -1,1,1 },
	                                                                                                                     { -1,1,-1 },
	                                                                                                                     { -1,-1,1 },
	                                                                                                                  {-1,-1,-1}}};  /**/  
	/// <summary>
	/// -return coordinates, where animal wants to go.
	/// 
	/// </summary>
	/// <param name="m">the enviromenet</param>
	/// <param name="coor"> here is animal</param>
	/// <param name="step"> this much steps can animal do</param>
	/// <returns></returns>
	Coordinates SearchAround(const Map& m, Coordinates coor, int step)const;
	//calculate how many nutrition will animal get 
	float calc_meal( Item* food )const;

	Coordinates RandomEmptyBox(const Map& m, Coordinates coor, int step,Generator& random); //get random empty box which is reacheble
	Coordinates GoCloser(const Map& m, Coordinates coor, Coordinates direction, int step); //in case animal see food source but canot reach it 
protected:


	float size;
	float dexterity;
	float sense;
	//size is already in item so it is inherited 

};
#endif
