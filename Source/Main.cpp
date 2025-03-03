#include <iostream>

#include "Data/FileDataSource.hpp"
#include "Parse/Byte/ByteParser.hpp"
#include "Parse/Value/ValueParser.hpp"
#include "Sort/Sorter.hpp"
#include "Transform/FileTransformer.hpp"

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

    const std::string tempFilePath{ "temp.bin" };
    const std::size_t chunkSize = 25 * 1024 * 1024;

    FileTransformer toByteTransformer
    { 
        { inputFilePath, std::ios_base::in },
        { tempFilePath, std::ios_base::binary },
        chunkSize, new ByteParser{} 
    };
    toByteTransformer.Standartize();
    toByteTransformer.~FileTransformer();
    
    FileDataSource dataSource
    {
        { tempFilePath, std::ios::binary },
        chunkSize 
    };

    Sorter sorter{ std::move(dataSource) };
    sorter.Sort();

    const double value = dataSource.GetValue(100000);
    std::cout << value << std::endl;

    FileTransformer fromByteTransformer
    { 
        { tempFilePath, std::ios::binary },
        { outputFilePath, std::ios::out },
        chunkSize, new ValueParser{} 
    };
    fromByteTransformer.Standartize();

    return EXIT_SUCCESS;
}
