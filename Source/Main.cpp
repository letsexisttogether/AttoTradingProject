#include <iostream>

#include "Standartize/FileStandartizer.hpp"
#include "FileDataSource/FileDataSource.hpp"
#include "Sort/Sorter.hpp"

static void PrintValue(FileDataSource& dataSource,
    const FileDataSource::Index lineNumber) noexcept;

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
    FileStandartizer::Size width = standartize.Standartize(8);

    FileDataSource dataSource{ outputFilePath, width };

    /*
    PrintValue(dataSource, 1);
    dataSource.WriteValueAt(517.308, 1);
    PrintValue(dataSource, 1);
    */

    Sorter sorter{ std::move(dataSource) };
    sorter.Sort();

    return EXIT_SUCCESS;
}

void PrintValue(FileDataSource& dataSource,
    const FileDataSource::Index lineNumber) noexcept
{
    const double value = dataSource.ReadValueAt(lineNumber);
    std::cout << "The value at line: " << lineNumber << ": "
        << value << std::endl;
}
