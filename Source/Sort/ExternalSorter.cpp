#include "ExternalSorter.hpp"

#include <filesystem>
#include <iostream>
#include <algorithm>
#include <queue>

#include "FileProcess/Read/FileReader.hpp"
#include "FileProcess/Write/FileWriter.hpp"
#include "Parse/Byte/ByteParser.hpp"
#include "Parse/Value/ValueParser.hpp"
#include "Spawn/Input/InputBufferSpawner.hpp"
#include "Spawn/Output/OutputBufferSpawner.hpp"

#include "General/MemoryUsage.hpp"

ExternalSorter::ExternalSorter(const std::filesystem::path& inputPath,
    const std::filesystem::path& outputPath,
    const std::size_t availableMemory) noexcept
    : m_InputPath{ inputPath }, m_OutputPath{ outputPath },
    m_BufferSize{ availableMemory / 2 } // Due to extra buffers use
{
    try
    {
        if (std::filesystem::exists(m_TempDirPath))
        {
            std::filesystem::remove_all(m_TempDirPath);
        }

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
        std::filesystem::remove_all(m_TempDirPath);
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
    const std::string tempFilePath
    { 
        m_TempDirPath.string() + "file" 
    };

    try
    {
        std::cout << "Sorting..." << std::endl;

        std::vector<double> data{};

        FileReader<double> reader
        { 
            { m_InputPath, std::ios::in },
            new ByteParser{}
        }; 

        for (std::size_t i = 1; !reader.IsEOF(); ++i)
        {
            data = reader.Read(m_BufferSize);

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
    using ValueIndex = std::pair<double, std::uint8_t>;

    std::priority_queue<ValueIndex, std::vector<ValueIndex>,
        std::greater<ValueIndex>> queue{};

    const std::size_t inputSize = m_BufferSize * 0.8;
    const std::size_t outputSize = m_BufferSize - inputSize;

    try
    {
        std::cout << "Merging..." << std::endl;

        InputBufferSpawner inputBufferSpawner
        { 
            { m_TempDirPath, std::ios::in },
            inputSize
        };

        std::vector<InputBufferSpawner::InputBuffer> inputBuffers{};
        for (std::uint8_t i = 0; !inputBufferSpawner.IsEnd(); ++i)
        {
            auto inputBuffer = inputBufferSpawner.Spawn();
            inputBuffer.Read();

            queue.push({ inputBuffer.GetValue(), i });
            inputBuffers.push_back(std::move(inputBuffer));
        }

        OutputBufferSpawner outputBufferSpawner
        {
            { m_OutputPath, std::ios::out },
            outputSize
        };

        auto outputBuffer{ outputBufferSpawner.Spawn() };

        while(!queue.empty())
        {
            const auto [value, index] = queue.top();
            queue.pop();

            auto& inputBuffer = inputBuffers[index];

            if (inputBuffer.IsEnd())
            {
                inputBuffer.Read(); 
            }
            if (!inputBuffer.IsEnd())
            {
                queue.push({ inputBuffer.GetValue(), index });
            }

            if (outputBuffer.IsEnd())
            {
                outputBuffer.Write();
            }

            outputBuffer.PutValue(value);
        }
    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error during merging] "
            << exp.what() << std::endl;
    }
}
