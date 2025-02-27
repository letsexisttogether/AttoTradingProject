#include <iostream>

#include "Parse/Byte/ByteParser.hpp"
#include "Parse/Value/ValueParser.hpp"
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
    const std::size_t chunkSize = 100000;

    FileTransformer toByteTransformer
    { 
        { inputFilePath, std::ios_base::in },
        { tempFilePath, std::ios_base::binary },
        chunkSize, new ByteParser{} 
    };
    toByteTransformer.Standartize();
    toByteTransformer.~FileTransformer();
    

    FileTransformer fromByteTransformer
    { 
        { tempFilePath, std::ios::binary },
        { outputFilePath, std::ios::out },
        chunkSize, new ValueParser{} 
    };
    fromByteTransformer.Standartize();

    return EXIT_SUCCESS;
}
