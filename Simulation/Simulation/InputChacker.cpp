

#include "chacker.h"
const std::vector< std::string>  HeaderChacker::head_param{ "days","map_hight","map_width","calculator","nutritions_divider" };
const std::vector< std::string>  RegularSpeaciesChacker::animal_param{ "name","size","sense","dexterity","reproduction","mutation","count","food","stop_eat" };
const std::vector< std::string>  PlantChacker::plant_param { "name","size","count","nourishment","changer" };

void HeaderChacker::check_header(const std::unordered_map < std::string, Line> & param,Header* header)const 
{
    if (param.size() > head_param.size()) {
        throw std::runtime_error(" to much parameter in head definition ");
    }
    for (const std::string parameter_name:head_param) {
        if (param.find(parameter_name) == param.end()) {
            throw std::runtime_error(parameter_name +" is not set in header declaration");
        }
        else {
            proces_header_params(header, param.at(parameter_name), parameter_name);
        }
    }
  
}

void SpeciesChacker::check_animal(const std::unordered_map < std::string,Line> & param,const  AnimalSpecies&  r_species,AnimalSpecies* species)const
{
    if (param.size() > animal_param.size()) {
        throw std::runtime_error(" to much parameter in species definition ");
    }
    for (const std::string parameter_name : animal_param) {
        if (param.find(parameter_name) == param.end()) {
            set_animal_params(species,parameter_name,r_species);
        }
        else {
            proces_species_params(species, param.at(parameter_name), parameter_name);
        }
    }
    for (const auto& pair : param) {
        if (std::find(animal_param.begin(), animal_param.end(), pair.first) == animal_param.end()) {
            throw std::runtime_error(pair.first + " on line: " +pair.second.getLine() + " is not a parameter");
        }
        
    }
}

void RegularSpeaciesChacker::check_animal(std::unordered_map < std::string, Line> const& param,AnimalSpecies* species)
{

    for (const std::string parameter_name : animal_param) {
        if (param.find(parameter_name) == param.end()) {
            throw std::runtime_error(parameter_name + " is not set in first species declaration");
        }
        else {
            proces_species_params(species, param.at(parameter_name), parameter_name);
        }
    }
    regular_animal = *species;
}

void PlantChacker::check_plant(std::unordered_map < std::string, Line> const& param,PlantSpecies* plant)const
{
    if (param.size()>plant_param.size()) {
        throw std::runtime_error( " to much parameter in plant definition ");
    }
    for (const std::string parameter_name : plant_param) {
        if (param.find(parameter_name) == param.end()) {
             
            throw std::runtime_error(parameter_name + " is not set in plant declaration");
        }
        else {
            proces_plants_params(plant, param.at(parameter_name), parameter_name);
        }
    }
}

void HeaderChacker::proces_header_params(Header* header, const Line& parameter, const std::string & parameter_name)const
{
    const std::vector<std::string>& string_param =parameter.getValues();
    if (parameter_name == "days") {
        check_count(1, parameter, parameter_name);
        header->setDays(std::stoi(string_param.at(0)));
    }
    else if (parameter_name == "map_hight") {
        check_count(1, parameter, parameter_name);
        header->setMap_higth (std::stoi(string_param.at(0)));
    }
    else if (parameter_name == "map_width") {
        check_count(1, parameter,  parameter_name);
        header->setMap_width (std::stoi(string_param.at(0)));
    }
    else if (parameter_name == "nutritions_divider") {
        check_count(1, parameter, parameter_name);
        header->setDivider(std::stof(string_param.at(0)));
    }
    else if (parameter_name == "calculator") {
        check_count(4, parameter, parameter_name);
        header->setCalculator(std::stoi(string_param.at(0)), std::stof(string_param.at(1)), std::stof(string_param.at(2)), std::stof(string_param.at(3)));
    }
    
    else {
        throw std::invalid_argument( parameter_name + " isn`t head parameter");
    }

}

void RegularSpeaciesChacker::proces_species_params(AnimalSpecies* animal, const Line& parameters, const std::string& parameter_name)const
{
    const std::vector<std::string>& string_param = parameters.getValues();
    if (parameter_name == "name") {
        check_count(1, parameters, parameter_name);
        animal->setName(string_param.at(0));
    }
    else if (parameter_name == "size") {
        check_count(1, parameters, parameter_name);
        animal->setSize(std::stof(string_param.at(0)));
    }
    else if (parameter_name == "sense") {
        check_count(1, parameters, parameter_name);
        animal->setSense(std::stof(string_param.at(0)));
    }
    else if (parameter_name == "dexterity") {
        check_count(1, parameters, parameter_name);
        animal->setDexterity(std::stof(string_param.at(0)));
    }
    else if (parameter_name == "reproduction") {
        check_count(1, parameters, parameter_name);
        animal->setReproduction(std::stof(string_param.at(0)));
    }
    else if (parameter_name == "mutation") {
        check_count(1, parameters, parameter_name);
        animal->setMutation(std::stof(string_param.at(0)));

    }
    else if (parameter_name == "count") {
        check_count(1, parameters, parameter_name);
        animal->setCount(std::stoi(string_param.at(0)));

    }
    else if (parameter_name == "food") {
        check_count(2, parameters, parameter_name);
        float meet = std::stof(string_param.at(0));
        float food = std::stof(string_param.at(1));
        animal->setFood(meet, food);

    }

    else if (parameter_name == "stop_eat") {
        check_count(1, parameters, parameter_name);
        animal->setStop_eat(std::stof(string_param.at(0)));
    }
    else {
        throw std::invalid_argument(parameter_name + " isn`t species parameter");
    }
}

void PlantChacker::proces_plants_params(PlantSpecies* plant, const Line& parameter, const std::string& parameter_name)const
{
    const std::vector<std::string>& string_param = parameter.getValues();
    if (parameter_name == "size") {
        check_count(1, parameter, parameter_name);
        plant->setSize(std::stof(string_param.at(0)));
    }
    else if (parameter_name == "name") {
        check_count(1, parameter, parameter_name);
        plant->setName(string_param.at(0));
    }
    else if (parameter_name == "count") {
        check_count(1, parameter, parameter_name);
        plant->setCount(std::stoi(string_param.at(0)));
    }
    else if (parameter_name == "nourishment") {
        check_count(1, parameter, parameter_name);
        plant->setNourishment(std::stof(string_param.at(0)));

    }
    else if (parameter_name == "changer") {
        check_count(4, parameter, parameter_name);
        int interval= std::stoi(string_param.at(0));
        float times= std::stof(string_param.at(1));
        int max= std::stoi(string_param.at(2));
        int min= std::stoi(string_param.at(3));
        plant->setChanger(interval,times,max,min);
    }
    else {
        throw std::invalid_argument( parameter_name + " isn`t plants parameter");
    }
}

void SpeciesChacker::set_animal_params(AnimalSpecies* animal,const std::string& parameter_name, const AnimalSpecies& regular_animal)const
{
    if (parameter_name == "size") {
        animal->setSize(regular_animal.getSize());
    }
    else if (parameter_name == "sense") {
        animal->setSense(regular_animal.getSize());
    }
    else if (parameter_name == "dexterity") {
        animal->setDexterity(regular_animal.getSize());
    }
    else if (parameter_name == "reproduction") {
        animal->setReproduction(regular_animal.getReproduction());
    }
    else if (parameter_name == "mutation") {
        animal->setMutation(regular_animal.getMutation());
    }
    else if (parameter_name == "count") {
        animal->setCount(regular_animal.getCount());
    }
    else if (parameter_name == "food") {
        animal->setFood(regular_animal.getFood().meet, regular_animal.getFood().plants);
    }
    else if (parameter_name == "name") {
        animal->setName(regular_animal.getName());
    }
    else if (parameter_name == "stop_eat") {
        animal->setStop_eat(regular_animal.getStop_eat());
    }
    

}
void HeaderChacker::check_count(int expected_count, const Line& parameters, const std::string& name)const {
    if (parameters.getValues().size() != (unsigned)expected_count)
        throw std::invalid_argument("*head \"" + name + "\" wrong number of arguments at line " + parameters.getLine());
}
void RegularSpeaciesChacker::check_count(int expected_count, const Line& parameters, const std::string& name) const{
    if (parameters.getValues().size() != (unsigned)expected_count)
        throw std::invalid_argument("*food \"" + name + "\" wrong number of arguments at line " + parameters.getLine());

}
void PlantChacker::check_count(int expected_count, const Line& parameters, const std::string& name)const  {
    if (parameters.getValues().size() != (unsigned)expected_count)
        throw std::invalid_argument("*species \"" + name + "\" wrong number of arguments at line " + parameters.getLine());

}


 const AnimalSpecies& RegularSpeaciesChacker::getRSpecies()const  
{
    return  regular_animal;
}