#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

#define USAGE "usage: bits NUM_TO_REPRESENT"

int main(int argc, char ** argv)
{
    std::string prog_name, number_string;
    int number;

    if(argc < 2)
    {
        std::cout << USAGE << std::endl;
        std::exit(EXIT_FAILURE);
    }
    else
    {
        prog_name = std::string(argv[0]);
        number_string = std::string(argv[1]);
        number = std::stoi(number_string);

        if(number <= 0)
        {
            std::cout << "Input must be a positive nonzero number. \n";
            std::cout << USAGE << std::endl;
            std::exit(EXIT_FAILURE);
        }
        else
        {
            std::cout <<  std::floor(std::log2(number)) << std::endl;
        }
        
    }

    return 0;
}