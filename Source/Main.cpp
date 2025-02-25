#include <iostream>

#include "Standartize/FileStandartizer.hpp"

std::int32_t main(std::int32_t argc, char** argv)
{
    std::cout << "Hello, AttoTrading" << std::endl;

    const std::string inputFilePath 
    {
        ((argc > 1) ? (argv[1]) : ("Input.txt"))
    };
    const std::string outputFilePath
    {
        ((argc > 2) ? (argv[2]) : ("Output.txt"))
    };

    FileStandartizer standartize{ inputFilePath, outputFilePath };
    standartize.Standartize();

    return EXIT_SUCCESS;
}
