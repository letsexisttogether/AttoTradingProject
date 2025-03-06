#include <iostream>
#include <cstdlib>
#include <string>

#include "Sort/ExternalSorter.hpp"

std::int32_t main(std::int32_t argc, char** argv)
{
    const std::string inputFilePath 
    {
        ((argc > 1) ? (argv[1]) : ("Input.txt"))
    };
    const std::string outputFilePath
    {
        ((argc > 2) ? (argv[2]) : ("Output.txt"))
    };

    ExternalSorter sorter
    {
        inputFilePath, outputFilePath,
        80 * 1024 * 1024
    };

    sorter.Sort();
        
    return EXIT_SUCCESS;
}
