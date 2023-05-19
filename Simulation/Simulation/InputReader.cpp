

#include "InputReader.h"
#include "chacker.h"
Parameters InputReader::get_parameters(std::string const& path)
{
	std::ifstream f;
	f.open(path);
	if (f.good()) {
		return read_input(f);
	}
	else {
		throw std::invalid_argument(path+" file not found");
	}
}

Parameters InputReader::read_input(std::istream& str)
{
	using Section=std::unordered_map<std::string, Line>;
	Parameters parameters;
	bool first_species = true;
	bool header_defined = false;
	HeaderChacker header_ch;
	SpeciesChacker species_ch;
	RegularSpeaciesChacker r_species_ch;
	PlantChacker plants_ch;
	for (;;) {
		 Argument line;
		 readLine(str,line);
		if (line.getName().empty()) break;

		if (line.getName() == "*head") {
			Section section;
			read_section(str,section);
			header_ch.check_header(section,parameters.header.get());
			header_defined = true;
		}
		if (line.getName() == "*plant") {
			Section section;
			read_section(str,section);
		
			parameters.plants.get()->push_back(PlantSpecies());
			PlantSpecies* p=&parameters.plants.get()->back();   
			plants_ch.check_plant(section, p);    // setting and checking parameters of new plant species 
			p->setId((int)parameters.plants.get()->size() );
			
		}
		if (line.getName() == "*species") {
			if (first_species) {
				Section section;
				read_section(str,section);
				parameters.species.get()->push_back(AnimalSpecies());
				AnimalSpecies* a= &parameters.species.get()->back();				
				r_species_ch.check_animal(section,a);
				a->setId((int)parameters.species.get()->size() );
				first_species = false;
			}
			else {
				Section section;
				read_section(str,section);
				parameters.species.get()->push_back(AnimalSpecies());
				AnimalSpecies* a = &parameters.species.get()->back();
				species_ch.check_animal(section, r_species_ch.getRSpecies(),a);
				a->setId((int)parameters.species.get()->size());
			}		
		}
	}
	if (!header_defined){
		throw std::runtime_error("header must be defined");
	}
	int items = 0;
	for (auto&& plant : *parameters.plants.get()) {
		items += plant.getCount();
	}
	for (auto&& s : *parameters.species.get()) {
		items += s.getCount();
	}
	if (parameters.header->getMap_higth() * parameters.header->getMap_width() < items) {
		throw std::runtime_error("To many items on the map");
	}
    return parameters;
}

void InputReader::read_section(std::istream& str, std::unordered_map<std::string, Line>& parameters)
{   
	for (;;) { 
		Argument argument;
		readLine(str,argument);
		if (argument.getName().empty() || argument.getName()[0] == '-') { //"-" means end of the section 
			break;
		}
		else {
			
			parameters.insert({ argument.getName(), Line(argument.getValues(),line_number) });
		}	
	}	
}

void InputReader::readLine(std::istream& str, Argument& argument)
{
	std::vector<std::string> parameters;
	std::string raw_line;
	std::string word;
	std::string first_word_in_line;
	
	while (first_word_in_line.empty()) {
		++line_number;
		getline(str, raw_line);
		if (str.fail()) {
		    argument.setName(first_word_in_line);
		    argument.setValues(parameters);
		    return;
	    }
		throwComment(raw_line);
		std::stringstream stream(raw_line);
		for (;;) {
			stream >> word;
			if (stream.fail() ) 
				break;

			if (first_word_in_line.empty()) {
				first_word_in_line = word;
			}
			else {
				parameters.push_back(word);
			}			
		}
	}
	
	argument.setName(first_word_in_line);
	argument.setValues(parameters);
}

void InputReader::throwComment(std::string& line)
{
	int index = 0;
	for (int i = 0; i < line.size(); ++i) {
		++index;
		if (line[i] == comment_deliminator) {
			line = line.substr(0, index-1);
			break;
		}
			
	}
	
}

