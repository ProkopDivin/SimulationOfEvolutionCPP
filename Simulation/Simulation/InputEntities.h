#pragma once

#include "Calculator.h"
#include <iostream>
#include <functional>
#include "simulationEntitie.h"
#include <memory>

#ifndef INPUTENTITIES_H_
#define INPUTENTITIES_H_






/// <summary>
/// for animal species.
/// </summary>
struct Nutrions_Multiplicators {
public:
	Nutrions_Multiplicators() :plants(-1), meet(-1) {}
	Nutrions_Multiplicators( float meet, float plants):plants(plants),meet(meet){}
	//to ilustrate the efficiency with which an animal obtains nutrients from plants
	float plants;
	//to ilustrate the efficiency with which an animal obtains nutrients from plants another animals
	float meet;

};
/// <summary>
/// for changing the maximum amount of food on the map.
/// at the end of the day, the food is replenished up to a certain number.
/// max...maximum value of that number 
/// min...minimum value of that number 
/// times... how many times does the amount change
/// interval... number of days after which change occure
/// </summary>
struct Food_changer {
public:
	Food_changer():interval(-1),times(-1),max(-1),min(-1){}
	Food_changer(int interval,float times, int max,int min):interval(interval),times(times),max(max),min(min){}
	int interval = -1;
	float times = 1;
	int max = 0;
	int min = 0;
};



/// <summary>
/// class for loading parameters in header section of input 
/// </summary>
class Header {
public:
	Header(const Header& h) {
		days = h.days;
		map_width = h.map_width;
		map_higth = h.map_higth;
		divider = h.divider;
		calculator =h.calculator;
	}
	Header():days(-1),map_width(-1),map_higth(-1),divider(-1){}
	
	void print();
	//getters
	int getDays() const { return days; }
	int getMap_width() const { return map_width; }
	int getMap_higth() const { return map_higth; }
	float getDivider() const { return divider; }
	
	std::shared_ptr<Calculator> getCalculator() { return calculator; }
	
	//setters

	void setDays(int x);
	void setDivider(float x);
	void setMap_width(int x);
	void setMap_higth(int x);
	void setCalculator(int x, float size, float sense, float dexterity);

private:
	float divider;
	int days;
	int map_width;
	int map_higth;
	
	std::shared_ptr<Calculator> calculator=nullptr;
};
/// <summary>
/// class for loading parameters in *animal section of input
/// </summary>
class AnimalSpecies {
public:
	AnimalSpecies( ) :name(""), size(-1), sense(-1), dexterity(-1), reproduction(-1), mutation(-1), count(-1),stop_eat(-1),id(-1) {}
	//getters 
	std::string getName() const { return name; }
	int getId()const {return id; }
	float getSize() const { return size; }
	float getSense()const { return sense; }
	float getDexterity()const { return dexterity; }
	float getReproduction()const { return reproduction; }
	float getMutation()const { return mutation; }
	int getCount()const { return count; }
	float getStop_eat() const {return stop_eat;}
	Nutrions_Multiplicators getFood()const { return food; }
	//setters
	void setId(int x);
	void setName(std::string x);
	void setSize(float x);
	void setSense(float x); 
	void setDexterity(float x); 
	void setReproduction(float x); 
	void setMutation(float x); 
	void setCount(int x);
	void setFood(float x, float y);
	void setStop_eat(float x);
	
	void decreaseCount() { count--; }
	void print();
	
private:
	int id;
	std::string name;
	float stop_eat;
	float size;
	float sense;
	float dexterity;
	float reproduction;
	float mutation;
	int count;
	Nutrions_Multiplicators food;
	

};
/// <summary>
/// class for loading *food section of input folder 
/// </summary>
class PlantSpecies {
public:
	void print();
	PlantSpecies() :name(""), count(-1), size(-1), nourishment(-1), actual_count(0), id(-1) {}
	//getters
	std::string  getName() const { return name; }
	int  getCount() const { return count; }
	float getSize() const { return size; }
	float  getNourishment() const { return nourishment; }
	int getActual_count()const { return actual_count; }
	int getId() const{ return id; }

	Food_changer getFood_changer() const { return changer; }
	//setters
	void decreaseActual_count() { --actual_count; }
	void increaseActual_count() { ++actual_count; }
	void setId(int x);
	void setActual_count(int x);
	void setName(std::string x);
	void setCount(int x);
	void setSize(float x);
	void setNourishment(float x);
	void setChanger(int interval, float times, int max, int min);

private:
	int id;
	int actual_count;
	std::string name;
	int count;
	float size;
	float nourishment;
	Food_changer changer;
	
};



/// <summary>
/// struct to pass readed parameters
/// </summary>
struct Parameters {

	Parameters() {
		header = std::make_unique<Header>(Header());
		species = std::make_unique<std::vector<AnimalSpecies>>(std::vector<AnimalSpecies>());
		plants = std::make_unique < std::vector<PlantSpecies>>(std::vector<PlantSpecies>());
	}

	std::unique_ptr<Header> header;
	std::unique_ptr<std::vector<AnimalSpecies>> species;
	std::unique_ptr<std::vector<PlantSpecies>> plants;
};

class Argument {
public:
	const std::string& getName() const{
		return name;
	}
	const std::vector<std::string>& getValues() const{
		return values;
	}
	
	void setName(const std::string& name) {
		this->name = name;
	}
	void setName(std::string&& name) {
		this->name = std::move(name);
	}
	void setValues(const std::vector<std::string>& values){
		this->values = values;
	}
	void setValues( std::vector<std::string>&& values) {
		this->values = std::move(values);
	}
private:
    std::string name;
    std::vector<std::string> values;
	
};
class Line {
public:
    std::string getLine() const {
		return std::to_string(line_number);
	}
	const std::vector<std::string>& getValues() const {
		return values;
	}

	 Line (std::vector<std::string>&& values, int line) {
		this->values = std::move(values);
		this->line_number = line;
	}
	 Line(const std::vector<std::string>& values, int line) {
		 this->values = values;
		 this->line_number = line;
	 }
	void setLine(int number) {
		this->line_number = number;
	}
	void setValues(const std::vector<std::string>& values) {
		this->values = values;
	}
	void setValues( std::vector<std::string>&& values) {
		this->values = std::move(values);
	}

private:
	int line_number;
	std::vector<std::string> values;
};


#endif