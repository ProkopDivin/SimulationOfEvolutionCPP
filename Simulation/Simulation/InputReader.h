#pragma once
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#include <fstream>

#include "InputEntities.h"
#include "chacker.h"


#ifndef READER_H_
#define READER_H_
/// <summary>
/// - class for reading the input file 
/// </summary>
class InputReader{
public:
	/// <summary>
	///  - read the input file and return parameters
	/// - parameters have the right type and value, and non of them missing   
	/// </summary>
	/// <param name="path"> path to imput file </param>
	/// <returns>  checked parameters  </returns>
	Parameters get_parameters(std::string const& path);
	
private:
	const static char comment_deliminator = '#';
	int line_number = 0; //number of current line 
	// do the actual reading of the file 
	Parameters read_input(std::istream& str);
	//read one section, from word word *head,*plant... to a line with "----------"
	void read_section(std::istream& str, std::unordered_map<std::string, Line>& section);

	void readLine(std::istream& str, Argument& argument);
	void throwComment(std::string& line);
};
#endif