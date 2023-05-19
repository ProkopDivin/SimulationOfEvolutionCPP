#include <string>
#include <iostream>
#include <sstream> 
#include "Simulation.h"
#include <chrono>




using namespace std::chrono;


int main(int argc, char** argv)
{
    if (argc < 3) {
        std::cout << "ERROR: argument missing, 2 arguments needed";
        return 0;
    }

    const std::string path_to_input = argv[1]; //"tests/simpleTest.txt";
    const std::string output = argv[2];       // "results";
    Simulation simulation;
    auto start = high_resolution_clock::now();
    simulation.load(path_to_input,output);
    if (simulation.ready) {
        simulation.start();
        simulation.save();
        }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time taken by function: "
        << duration.count() << " microseconds" << std::endl;
    /**/
}
