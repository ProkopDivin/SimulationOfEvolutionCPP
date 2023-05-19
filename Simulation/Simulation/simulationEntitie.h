#pragma once
#include <iostream>
#include <memory>
#include <random>
#include <vector>


#ifndef SIMENTITIES_H_
#define SIMENTITIES_H_
/// <summary>
/// random nuber generator 
/// </summary>
struct Generator {
	 
public:
	Generator() : rng(rd()) {
		rng.seed(42);
	}

	int roll(const int max) {
		dice = std::uniform_int_distribution<>(0, max - 1);
		return dice(rng);
	}
private:
	std::random_device rd;
	typedef std::mt19937 MyRng;
	MyRng rng;
	std::uniform_int_distribution<int> dice;
};
/// <summary>
/// coordinates in the map 
/// </summary>
struct Coordinates {
public:
	int x;
	int y;
	Coordinates() : x(-0), y(0) {}
	Coordinates(int x, int y) : x(x), y(y) {}

	int Distance()const
	{
		return x + y;
	}
	int Distance(Coordinates p)const;
	int Length()const;
	Coordinates Direction(Coordinates c);
	friend bool operator==(const Coordinates a, const Coordinates b) { return a.x == b.x && a.y == b.y; }

	
	struct HashFunction
	{
		size_t operator()(const Coordinates coor) const;
	};
};
/// <summary>
/// -iterator 
/// -iterate over coordinates where animal is looking for food source
/// -this coordinates can be return one by one 
/// -return all cordinates further then min and closses than max
/// -assume that animal is in coordinates [0,0]
/// </summary>

struct SearchingCoordinates {
	/// <summary>
	
	/// </summary>
	/// <param name="min">minimal distance </param>
	/// <param name="max">maximal distance </param>
	SearchingCoordinates(int min, int max) :
		min(min),
		max(max),
		//indexes
		i(min),
		j(-1)  //	with frst call "next" became 0;
	{}
private:
	void next_in_one_direction() {
		if (j <= i && std::abs(i-j)+j<max) {
			//cordinates in distance i
			j += 1;
		}
		else if (i < max) {
			//increase distance
			i += 1;
			j = 0; //start new loop
			//generate frst cordinates
		}
		else {
			valid = false;
		}
	}
public:
	bool next() {
		direction = direction % 4;//four direction
		if (direction == 0) {	next_in_one_direction();}
		int x = i - j;
		int y = j;
		if (!valid) { return false; }
		if (direction == 0) {
			item = Coordinates(x, y);
			direction += 1;
		}
		else if (direction == 1) {
			item = Coordinates(-x, -y);
			direction += 1;
		}
		else if (direction == 2) {
			if (x == 0 || y == 0) {//dont want to iterate repeate coordinates 			
				direction = 0;
				return next();
          	}
			else {
				item = Coordinates(x, -y);
				direction += 1;
			}
		}
		else if (direction == 3) {
			item = Coordinates(-x, y);	
			direction += 1;
		}
		
		return true;
		
	}
	bool valid = true;
	Coordinates get() const{
		return item;
	}
private:
	//coordinates where animal will move
	Coordinates item;
	int direction = 0;
	int i;
	int j;
	int min;
	int max;
};
#endif