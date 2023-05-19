

#include "Simulation.h"



Simulation::Simulation():days(0)
{
	
}
void Simulation::load(const std::string& inputfile, const std::string& outputfile)
{
	
	InputReader reader;
	output = outputfile;
	try {
		Parameters parameters = reader.get_parameters(inputfile);
		print_params(&parameters);
		days = parameters.header.get()->getDays();
		map.load(std::move(parameters));
		ready = true;

	}
	catch (const std::runtime_error& e ) {
		std::cout <<"Error:"<< e.what() << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Error:" << e.what() << std::endl;
	}
	

}

void Simulation::start() {
	//new place to store the statistics, it was nullptr before 
	
	
	stats.load(map, days, ",");
	std::ofstream file(output+"_log.txt");
	if (file.is_open()) {
		MapPrinter::printMap(map.getMap(), "0", file); //"0" because it is 0.th day 
		
		for (int i = 1; i <= days; ++i) {
			map.Day(i);
			stats.record(map);
			MapPrinter::printMap(map.getMap(), std::to_string(i), file);
			file << std::endl;
		}
		
	}
	else {
		std::cout<<"cant save log, the file:"<< output <<" can not be open.";
	}
}

void Simulation::save()const 
{
	if (stats.recorded) {
		stats.saveStats(output+".csv");
	}
	else {
		std::cout << "no data for saving" << std::endl;
	}
}
/// <summary>
/// this function print loaded parameters to chack if everything was loaded correctly 
/// </summary>
/// <param name="params"></param>

void Simulation::print_params(const Parameters* params)const
{
	params->header.get()->print();
	for (auto&& a : *params->species.get()) {
		a.print();
	}
	for (auto&& p : *params->plants.get()) {
		p.print();
	}
}
