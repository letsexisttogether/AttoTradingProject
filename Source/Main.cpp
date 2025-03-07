#include <chrono>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <string>

#include "Generate/FileDataGenerator.hpp"
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

    if (argc > 3 && !std::strcmp(argv[3], "-g"))
    {
        FileDataGenerator generator
        { 
            inputFilePath, 
            1 * 1024 * 1024 * 1024,
            20 * 1024 * 1024,
            { -2000000, 2000000 } 
        }; 
        generator.Generate();
    }

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
