#pragma once
#include <iostream>
#include <cmath>
#include <sstream>

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

/// <summary>
/// -classes for computing the hunger
/// -each class have differen function to calculate hunger
/// 
/// </summary>
class Calculator {
public:
	Calculator():rsense(-1),rsize(-1),rdexterity(-1){}
	Calculator(float size, float sense, float dexterity) { rsize = size; rsense = sense; rdexterity = dexterity; }

	virtual float hunger(float size, float sense, float dexterity)const {
		float si = size / rsize;
		float se = sense / rsense;
		float de = dexterity / rdexterity;
		return (float)(pow(si, 3) * pow(de, 2) + se );
	}
	std::string to_string() const{
		std::stringstream ss;

		ss << "id:" << getId() << ",rsize:" << rsize << " ,rsense:" << rsense << " ,rdexterity:" << rdexterity;
		return ss.str();
	}
protected:
	virtual int getId()const { return 0; }
	float rsize;
	float rsense;
	float rdexterity;
};
class PlusCalculator : public Calculator {
public:
	PlusCalculator(float size, float sense, float dexterity) { rsize = size; rsense = sense; rdexterity = dexterity; }

    float hunger(float size, float sense, float dexterity) const override{
		float si = size / rsize;
		float se = sense / rsense;
		float de = dexterity / rdexterity;
		return ((float)(si + de + se ));
	}
protected:
	
	 int getId() const{ return 1; }
};
class KineticCalculator : public Calculator {
public:

	KineticCalculator(float size, float sense, float dexterity) { rsize = size; rsense = sense; rdexterity = dexterity; }
	float hunger(float size, float sense, float dexterity) const override {
		float si = size / rsize;
		float se = sense / rsense;
		float de = dexterity / rdexterity;
		float hunger = ((float)(pow(si, 3) * pow(de, 2) + pow(se, 2)));
		return hunger;

	}
	
protected:
	int getId()const override{ return 2; }
};

class Calculator2 : public Calculator {
public:
	Calculator2(float size, float sense, float dexterity) { rsize = size; rsense = sense; rdexterity = dexterity; }

	float hunger(float size, float sense, float dexterity)const override{
		float si = size / rsize;
		float se = sense / rsense;
		float de = dexterity / rdexterity;
		return ((float)(pow(si, 2) * pow(de, 2) + (se) ));
	}
	
protected:
	int getId() const { return 3; }
};


#endif