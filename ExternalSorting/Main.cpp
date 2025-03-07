#include <chrono>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <string>

#include "Sort/ExternalSorter.hpp"

std::int32_t main(std::int32_t argc, char** argv)
{
    const std::string inputFilePath 
    {
        ((argc > 1) ? (argv[1]) : (""))
    };
    const std::string outputFilePath
    {
        ((argc > 2) ? (argv[2]) : ("Output.txt"))
    };

    const auto start = std::chrono::high_resolution_clock::now();

    ExternalSorter sorter
    {
        inputFilePath, outputFilePath,
        80 * 1024 * 1024
    };

    sorter.Sort();

    const auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Estimated external sorting time: " << duration.count() 
        << " seconds" << std::endl;
        
    return EXIT_SUCCESS;
}
