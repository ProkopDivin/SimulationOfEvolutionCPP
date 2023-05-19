#pragma once
#include <iostream>

#include "Map.h"
#include "DataProcessing.h"
#include "InputReader.h"
#ifndef SIMULATION_H_
#define SIMULATION_H_

class Simulation {
public:
	Simulation();
	/// <summary>
	/// perepare simulation 
	/// </summary>
	/// <param name="inputfile"> name of file with input </param>
	void load(const std::string& inputfile, const std::string& outputfile);
	/// <summary>
	/// start the simulation 
	/// </summary>
	void start();
	/// <summary>
	/// save record of the simulation
	/// </summary>
	/// <param name="outputfile"> name of file where the record shloud be stored </param>
	void save()const;
	bool ready = false;
private:
	
	std::string output = "";
	/// <summary>
	/// to see if the parameters where loaded correct
	/// </summary>
	/// <param name="params">paramers</param>
	void print_params(const Parameters* params)const;
	int days;
	/// <summary>
	/// simulation data 
	/// </summary>
	Map map; 
	/// <summary>
	/// -record of the simulation.
	/// -data which will be stored after simulation ended.
	/// -it is nullptr because dont know size of the map and items on the map yet 
	/// </summary>
	Statistic stats;
	

};
#endif