#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>

#include "Parse/Byte/ByteParser.hpp"
#include "Parse/Value/ValueParser.hpp"

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

    std::cout << "agasgag" << std::endl;

    /*
    try
    {
        std::filesystem::copy(inputFilePath, outputFilePath,
            std::filesystem::copy_options::overwrite_existing);
    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error] " << exp.what() << std::endl;

        return EXIT_FAILURE;
    }
    */

    std::cout << "We copied the file" << std::endl;

    std::ifstream inputStream{ inputFilePath };
    std::ofstream outputStream{ outputFilePath };

    const std::size_t fileSize = std::filesystem::file_size(inputFilePath);

    if (!inputStream.is_open() || !outputStream.is_open())
    {
        std::cerr << "[Error] No connecting with the files "
            << inputFilePath << outputFilePath << std::endl;

        return EXIT_FAILURE;
    }

    const std::size_t chunkSize = std::min(30ull * 1024 * 1024, fileSize);

    std::unique_ptr<Parser<char, double>> byteParser
    {
        new ByteParser{}
    };
    std::unique_ptr<Parser<double, char>> valueParser 
    {
        new ValueParser{}
    };

    while(true)
    {
        const std::size_t position = inputStream.tellg();
        // std::cout << "The position: " << position << std::endl;

        ByteParser::InputBuffer rawBuffer(chunkSize);

        inputStream.read(rawBuffer.data(), chunkSize);

        if (inputStream.bad())
        {
            std::cerr << "[Error] The read operation has failed" << std::endl;

            return EXIT_FAILURE;
        }

        const std::size_t bytesRead = inputStream.gcount();
        // std::cout << "gcount(): " << bytesRead << std::endl;

        if (!bytesRead)
        {
            break;
        }

        ByteParser::OutputBuffer valuesAsDouble
        { 
            byteParser->Parse(rawBuffer) 
        };

        std::sort(valuesAsDouble.begin(), valuesAsDouble.end());

        /*
        for (const double value : valuesAsDouble)
        {
            std::cout << value << '\n';
        }
        std::cout << std::endl;
        */

        ValueParser::OutputBuffer valuesAsChar
        { 
            valueParser->Parse(valuesAsDouble) 
        };

        /*
        for (const char symbol : valuesAsChar)
        {
            std::cout << symbol;
        }
        std::cout << std::endl;
        */

        // std::cout << "The writing position: " << outputStream.tellp() << std::endl;

        outputStream.write(valuesAsChar.data(), valuesAsChar.size());

        if (outputStream.bad())
        {
            std::cerr << "[Error] The write operation has failed" << std::endl;

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
