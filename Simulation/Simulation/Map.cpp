#include "Map.h"

void MapPrinter::printMap(const Enviroment& map,const std::string & day, std::ostream& file)
{
	int cell_width = 3;
	size_t row_width = cell_width * map.at(0).size() + 1;
	file <<"day: "<<day<< std::endl;
	printRowSeparator(file, row_width);
	for (auto&& line : map) {
		printRowSeparator(file, row_width);
		for (auto&& item : line) {
			file << "|";
			if (!item.get()) file << "  ";
			//print animal 
			else if (item.get()->getType() == ANIMAL) {
				file<< dynamic_cast<Animal*>(item.get())->species->getName();				
			}
			//print food
			else if (item.get()->getType() == FOOD) {
				file << dynamic_cast<Food*>(item.get())->plant->getName();
			}
		}
		file <<"|" << std::endl;
	}
	printRowSeparator(file, row_width);
}

void MapPrinter::printRowSeparator(std::ostream& file, size_t length)
{
	for (int i = 0; i < length; ++i) {
		file << "-" ;
	}
	file << std::endl;
}



void Map::findAnimals()
{
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[0].size(); ++j) {
			auto item = map[i][j].get();
			if (item) { //if iteme not noll true
				if (map[i][j]->getType() == ANIMAL && map[i][j] != NULL) {   
					animalsCoordinates.insert(Coordinates(i, j));
				}
			}
		}
	}
}

void Map::moveAnimals()
{
	for (int i = 0; i < Animal::rounds; ++i) {
		std::unordered_set<Coordinates, Coordinates::HashFunction> actualCoordinates;
		for (auto&& from : animalsCoordinates) {
			if (takenFields.count(from) == 0 && map[from.x][from.y] != nullptr) {//don`t move with animals which ate anither animal and with empty fields
				Animal* a = dynamic_cast<Animal*>(map[from.x][from.y].get());
				Coordinates to = a->MakeStep(*this, from, i, random);
				if (from.x!= to.x || from.y !=to.y  ) {//animal cant eat itself
				    //to find out max food animal can eat
					float max_food = a->species->getStop_eat() * a->species->getReproduction() * calculator->hunger(a->getSize(), a->getSense(), a->getDexterity());
				    a->Eat(move(map[to.x][to.y]), max_food);
			    }
				takenFields.insert(to); //fields where are already moved animals 				
				map[to.x][to.y] = move(map[from.x][from.y]);  
				actualCoordinates.insert(to);
			}
		}
		animalsCoordinates = move(actualCoordinates);
		takenFields.clear();		
	}
}

void Map::changeFoodCount(int date)
{
	for (auto&& f : plants) {
		Food_changer changer = f.getFood_changer();
		if ( date % changer.interval == 0) { //its time to channge max amount of food 
			int x = (int)(changer.times * f.getCount());
			x = std::min(changer.max, x);   //make sure it is under lower bound
			x = std::max(changer.min, x);   //make sure it is under upper bound
			f.setCount(x);
			
		}
	}
}

void Map::Day(int date)
{
 	moveAnimals();
	std::unordered_set<Coordinates,Coordinates::HashFunction> new_generation;
	for(auto && c : animalsCoordinates) {

		Animal* a = dynamic_cast<Animal*>(map[c.x][c.y].get());
		float hunger = calculator->hunger(a->getSize(), a->getSense(), a->getDexterity());   
		a->eaten -= hunger;
		
		if (a->eaten < 0) //animal didn`t eat enought
		{
			map[c.x][c.y].reset();
		}
		else {
			a->eaten += hunger;
			if (a->eaten > a->species->getReproduction() * hunger) {//animal can reproduce
				Animal new_animal = a->makeAnimal(random);
				Coordinates new_coor = place_item(new_animal); // new animal is born

				if (new_coor.x > -1) {//animal can be placed on the map 
					new_generation.insert(new_coor);
					a->eaten -= hunger * a->species->getReproduction();
				} 
				else {
					a->eaten -= hunger;
				}
			}
		    new_generation.insert(c); //animal survive
			a->eaten = a->eaten / divider;
		} 		
	}
	animalsCoordinates = move(new_generation);
	changeFoodCount(date);
	putFood();  //put fod on the map
}

void Map::load(Parameters parameters)
{
	plants = *parameters.plants.get();

	species = *std::move(parameters.species.get());
	Header* header = parameters.header.get();
	width = header->getMap_width();
	hight = header->getMap_higth();
	calculator = header->getCalculator();
	divider = header->getDivider();
	resize_map(); //givw map it`s final size
	fill_map();
	findAnimals();
}

void MapLoading::resize_map()
{
	for (int i = 0; i < width; ++i) {
		std::vector<std::unique_ptr<Item>> colum(hight);
		colum.shrink_to_fit();
		map.push_back(move(colum));
	}
	map.shrink_to_fit();
}

void MapLoading::fill_map()
{
	putAnimals();
	putFood();
}

void MapLoading::putAnimals()
{
	int index = 0;
	for (auto&& sp : species) {
		for (int i = 0; i < sp.getCount(); ++i) {
			Animal a(sp.getSize(), sp.getSense(), sp.getDexterity(),&sp);
			place_item(a);
		}
		index++;
	}
}

void MapLoading::putFood()
{
	int index = 0;
	for (auto&& f : plants) {
		for (int i = f.getActual_count() ; i < f.getCount(); ++i) {
			Food food(&f);
			Coordinates c=place_item(food);	
			
		}
		f.setActual_count(f.getCount());
	}
}



Coordinates MapLoading::RandomCoordinates()
{
	int x = random.roll(width);
	int y = random.roll(hight);
	for (int i = 0; i < tryes; ++i) { //try random pozition 5 times 
		if (map[x][y].get() == nullptr) return Coordinates(x, y);
		x = random.roll(width);
		y = random.roll(hight);
	}
	long startIndex = x * width + y;
	long places = width * hight;
	for (long i = startIndex; i < places + startIndex; ++i) {  //random pozitions didn`t work find first possible pozition
		if (map[x][y].get() == nullptr) return Coordinates(x, y);
		int index = i % places;
		x = (index / hight);
		y = (index % hight);
	}
	if (map[x][y].get() == nullptr) return Coordinates(x, y);
	else {
		return Coordinates(-1, -1);
	}
}

bool Map::IsEmpty(Coordinates c) const
{
	if (width > c.x && c.x > -1 && hight > c.y && c.y > -1) {//is inside the map
		if (map[c.x][c.y] == nullptr) return true;
	}
	return false;
}
																									

 




/**/
Animal::Animal(const Animal& animal)
{
	size = animal.size;
	sense = animal.sense;
	dexterity = animal.dexterity;
	species = animal.species;
	
}
void Animal::Eat(std::unique_ptr<Item> item,float max_food)
{
	{
		if (!item.get()) { ///for now on item can not be null 
			return ;
		}
		else {
			//eate another animal 
			if (item->getType() == ANIMAL && item!=NULL) {  //NULL -- to dont get warning 
				Animal* a = dynamic_cast<Animal*>(item.get());
				eaten += a->size * species->getFood().meet;						    
			}
			//eate food 
			else {

				Food* f = dynamic_cast<Food*>(item.get());
				eaten += f->plant->getNourishment() * species->getFood().plants;
				f->plant->decreaseActual_count();
				
			}
			eaten = std::min(max_food,eaten);
		}
	}
}
/**/
Animal Animal::makeAnimal( Generator& random)
{	
	int roll = random.roll(8);	
	//               size +    1/-1           * size *        float
	float new_size = size + mutations[roll][0]* size * species->getMutation();
	float new_sense = sense + mutations[roll][1]* sense * species->getMutation();
	float new_dexterity = dexterity + mutations[roll][2]*dexterity * species->getMutation();
	return  Animal(new_size, new_sense, new_dexterity, species);
}

Coordinates Animal::MakeStep(const Map& map, Coordinates coor, int turn,Generator& random)
{
	int step;
	int wholeDexterity = (int)dexterity;
	if (turn == rounds - 1)step = (wholeDexterity / rounds) + (wholeDexterity % rounds);
	else step = (wholeDexterity / rounds); 
	Coordinates somethingToEat = SearchAround(map, coor, step);
	float hunger = map.getCalculator()->hunger(size, sense, dexterity);

	if (somethingToEat.x == -1 || eaten > species->getStop_eat() * species->getReproduction() * hunger) { //nothing found for eating or animal has eaten enought
		return RandomEmptyBox(map, coor, step,random);
	}
	else {
		if (somethingToEat.Distance(coor) > step) {//cant reach the food
			return GoCloser(map, coor, coor.Direction(somethingToEat), step); 
		}
		else {
			//m.Eat(*this, move(m.map[somethingToEat.x][somethingToEat.y]), somethingToEat); //if something to eat is animal.. eatem <-his coordinates
			return somethingToEat;
		}
	}
}

float Animal::calc_meal( Item* item )const {
	float Meal;
	//calculatin the meal value 
	if (item->getType() == FOOD) { 
		Food* food = dynamic_cast<Food*>(item);
		if (food->plant->getSize() > size)
		{
			Meal = -1; //cant reach the food 
		}
		else {
			Meal = species->getFood().plants * food->plant->getNourishment();
		}
	}
	else {
		Animal* animal = dynamic_cast<Animal*>(item);
		if (animal->species->getId() == species->getId()|| animal->getSize()>size) { //dont allowed canibalism || cant be eate becaouse of size 
			Meal = -1;
		}
		else {
			Meal = species->getFood().meet * animal->getSize();
			
		}
	}
	return Meal;
}
Coordinates Animal::SearchAround(const Map& m, Coordinates coor, int step)const
{
	Coordinates SomethingToEat;
	int isense = (int)sense;
	float maxMeal = 0;
	bool reacheble = true;
	SearchingCoordinates searcher(1, isense);
	while (searcher.next()) {	
		Coordinates relative_move = searcher.get();
		Coordinates c = Coordinates(relative_move.x + coor.x, relative_move.y + coor.y);
		if (m.getWidth() > c.x && c.x > -1 && m.getHight() > c.y && c.y > -1)//c is in the map
		{ 
			Item* item = m.getMap()[c.x][c.y].get();
			if (item != nullptr) {//is not empty 				
				float Meal= calc_meal(item); 
				
				//decide if the meal is worth it 
				if (Meal  > maxMeal) { 
					if (reacheble) {
						maxMeal = Meal; SomethingToEat.x = c.x; SomethingToEat.y = c.y;
					}
					else if(maxMeal==0) {
						maxMeal = Meal; SomethingToEat.x = c.x; SomethingToEat.y = c.y;
					}
				}
				if (relative_move.Length() > step) {
					if (reacheble && maxMeal > 0) return  SomethingToEat;  //to prefare reachable food
					reacheble = false;
				}			
			}
		}
	}
	if (maxMeal > 0)return SomethingToEat;
	else return Coordinates(-1, -1); //didn`t find good move
}

Coordinates Animal::RandomEmptyBox(const Map& m, Coordinates coor, int step,Generator& random)
{
	for (int i = step; i > 0; --i) { // lengt of jump
		int roll = random.roll(i);
		for (int j = 0; j <= i; ++j) {
			int x = (i - roll);
			int y = (roll);
			int randomIndex = random.roll(4);
			for (int i = randomIndex; i < 4 + randomIndex; ++i) {
				int index = i % 4;
				Coordinates c(x * relativeMoves[index][0] + coor.x, y * relativeMoves[index][1] + coor.y);
				if (m.IsEmpty(c)) {
					return c;
				}
			}
			roll = (roll + 1) % (i + 1);
		}
	}
	return coor; //nowhere to move
}


Coordinates Animal::GoCloser(const Map& m, Coordinates coor, Coordinates direction, int step)
{
	int mx = 1; //direction in x axis
	int my = 1; //...........  y axis
	if (direction.x < 0)mx = -1;
	if (direction.y < 0)my = -1;
	for (int i = step; i > 0; --i)
	{
		for (int j = 0; j <= i; ++j)
		{
			if (i - j <= abs(direction.x) && j <= abs(direction.y)) {
				Coordinates c((i - j) * mx + coor.x, j * my + coor.y);
				if (m.IsEmpty(c))return c;
			}
		}
	}
	return Coordinates(coor); //cant go closer so it will stay on the same spot 
}

