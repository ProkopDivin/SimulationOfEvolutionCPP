#pragma once

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <array>

#include "InputEntities.h"

#ifndef CHACKER_H_
#define CHACKER_H_


/// <summary>
/// for finctions get type 
/// </summary>
enum Entyties
{
	HEADER = 0,
	SPECIE = 1,
	PLANT = 2
};
/// <summary>
/// class for chacking the parameters
/// </summary>

class Chacker{
protected:
	virtual void check_count(int expected_count, const Line& parameters, const std::string& name) const = 0;
};
/// <summary>
/// check parameters in header and convert them from string to their expected type.
/// </summary>
class HeaderChacker:Chacker {
public:
	/*!
	* \brief check the header part of input file
	*/
    void check_header(std::unordered_map < std::string, Line> const& parameters,Header* header)const;
	//the folowing is protected just to have easy way to create new type of plant
	static const size_t parameters = 5;
protected:
	static  const std::vector<std::string>  head_param; //names of parameters in head defunition
	//check if there is right number of values, when seting property
	void check_count(int expected_count, const Line& parameters, const std::string& name)const override ;
private:
	
	void proces_header_params(Header* header, const Line& parameter, const std::string& parameter_name)const;
};
/// <summary>
/// check parameters for the first animal and convert them from string to their expected type.
/// this animal is used as a regular animal, which means that if in another animal something missing than value from this animal is used. 
/// </summary>
class RegularSpeaciesChacker :Chacker {
public:
	void check_animal(std::unordered_map < std::string, Line> const& parameters, AnimalSpecies* animal);
	//return regular species, stats of regular species are used insted of mising parameters in species definition
	const AnimalSpecies& getRSpecies() const ;
private:
	AnimalSpecies regular_animal;
protected:	
	void check_count(int expected_count, const Line& parameters, const std::string& name)const override;
	static const std::vector<std::string>  animal_param;
	void proces_species_params(AnimalSpecies* header, const Line& parameter, const std::string& parameter_name)const;
};
/// <summary>
/// chack species parameters and fill the missing parameter 
/// </summary>
class SpeciesChacker :RegularSpeaciesChacker {
public:
	void check_animal(const std::unordered_map < std::string, Line> & parameters, const AnimalSpecies& r_species,AnimalSpecies* animal)const;

private:
	void set_animal_params(AnimalSpecies* animal, const std::string& name,const AnimalSpecies& regular_animal)const;
};
/// <summary>
/// check the plant parameters and convert them from string to their expected type.
/// </summary>
class PlantChacker :Chacker {
public:
	void check_plant(const std::unordered_map<std::string, Line>& parameters, PlantSpecies* plants)const;
	//the folowing is protected just to heve easy way to create new type of plant
protected:
	static const std::vector< std::string> plant_param;
	void check_count(int expected_count, const Line& parameters, const std::string& name)const override;
private:
	void proces_plants_params(PlantSpecies* header, const Line& parameter, const std::string& parameter_name)const;
};

#endif