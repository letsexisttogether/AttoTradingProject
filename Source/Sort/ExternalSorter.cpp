#include "ExternalSorter.hpp"

#include <iostream>
#include <algorithm>

#include "FileProcess/Read/FileReader.hpp"
#include "FileProcess/Write/FileWriter.hpp"
#include "Parse/Byte/ByteParser.hpp"
#include "Parse/Value/ValueParser.hpp"
#include "Spawn/Input/InputBufferSpawner.hpp"
#include "Spawn/Output/OutputBufferSpawner.hpp"

ExternalSorter::ExternalSorter(const std::filesystem::path& inputPath,
    const std::filesystem::path& outputPath,
    const std::size_t availableMemory) noexcept
    : m_InputPath{ inputPath }, m_OutputPath{ outputPath },
    m_AvailableMemory{ availableMemory }
{
    try
    {
        std::filesystem::create_directory(m_TempDirPath);
    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error during dir creation] "
            << exp.what() << std::endl;
    }
}

ExternalSorter::~ExternalSorter()
{
    try
    {
        // std::filesystem::remove_all(m_TempDirPath);
    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error during dir deletion] " 
            << exp.what() << std::endl;
    }
}

void ExternalSorter::Sort() noexcept
{
    SortChunks();
    MergeChunks();
}

void ExternalSorter::SortChunks() noexcept
{
    // 1 for read, 1 for write 
    const std::size_t bufferSize = m_AvailableMemory / 2;

    const std::string tempFilePath
    { 
        m_TempDirPath.string() + "file" 
    };

    try
    {
        std::cout << "We sort" << std::endl;

        std::vector<double> data{};

        FileReader<double> reader
        { 
            { m_InputPath, std::ios::in },
            new ByteParser{}
        }; 

        for (std::size_t i = 1; !reader.IsEOF(); ++i)
        {
            data = reader.Read(bufferSize);

            std::sort(data.begin(), data.end());

            FileWriter<double> writer
            {
                { tempFilePath + std::to_string(i), std::ios::out },
                new ValueParser{}
            };

            writer.Write(data);
        }

    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error during sorting] "
            << exp.what() << std::endl;
    }
}

void ExternalSorter::MergeChunks() noexcept
{
    try
    {
        std::cout << "We merge" << std::endl;

        InputBufferSpawner inputBufferSpawner
        { 
            { m_TempDirPath, std::ios::in },
            5 * 1024 * 1024
        };

        std::cout << "We try to spawn" << std::endl;
        std::vector<InputBufferSpawner::InputBuffer> inputBuffers{};
        while(!inputBufferSpawner.IsEnd())
        {
            inputBuffers.push_back(inputBufferSpawner.Spawn());
        }
        std::cout << "We spawned" << std::endl;

        OutputBufferSpawner outputBufferSpawner
        {
            { m_OutputPath, std::ios::out },
            10 * 1024 * 1024 
        };

        InputBuffer<double>& inputBuffer = inputBuffers.at(0);
        OutputBuffer<double> outputBuffer{ outputBufferSpawner.Spawn() };

        while(!inputBuffer.IsEnd() || !inputBuffer.IsEOF())
        {
            inputBuffer.Read();

            while(!inputBuffer.IsEnd())
            {
                if (outputBuffer.IsEnd())
                {
                    outputBuffer.Write();
                }

                const double value = inputBuffer.GetValue();

                outputBuffer.PutValue(value);
            }
        }
    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error during merging] "
            << exp.what() << std::endl;
    }

    std::cout << "We merged" << std::endl;
}
