#include <iostream>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <algorithm>
#include <string>

#include "Buffer/Input/InputBuffer.hpp"
#include "Buffer/Output/OutputBuffer.hpp"
#include "FileProcess/Read/FileReader.hpp"
#include "FileProcess/Write/FileWriter.hpp"
#include "Parse/Byte/ByteParser.hpp"
#include "Parse/Value/ValueParser.hpp"
#include "Spawn/Input/InputBufferSpawner.hpp"
#include "Spawn/Output/OutputBufferSpawner.hpp"

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

    const std::string tempDirPath
    {
        "temp/"
    };
    const std::string tempFilePath
    {
        tempDirPath + "file"
    };

    std::filesystem::create_directory("temp");

    // 90 Mb for all the buffers at max

    const std::size_t inputFileSize = std::filesystem::file_size(inputFilePath);
    const std::size_t inputReadSize = std::min(45ull * 1024 * 1024, inputFileSize);

    std::size_t valuesCount{};

    try
    {
        std::vector<double> data{};

        FileReader<double> reader
        { 
            { inputFilePath, std::ios::in },
            new ByteParser{}
        }; 

        for (std::size_t i = 1; !reader.IsEOF(); ++i)
        {
            data = reader.Read(inputReadSize);
            valuesCount += data.size();

            std::sort(data.begin(), data.end());

            FileWriter<double> writer
            {
                { tempFilePath + std::to_string(i), std::ios::out },
                new ValueParser{}
            };

            writer.Write(data);
        }

        std::cout << "We finished sorting" << std::endl;
    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error] " << exp.what() << std::endl;
    }

    try
    {
        InputBufferSpawner inputBufferSpawner
        { 
            { tempDirPath, std::ios::in },
            5 * 1024 * 1024
        };

        std::vector<InputBufferSpawner::InputBuffer> inputBuffers{};
        while(!inputBufferSpawner.IsEnd())
        {
            inputBuffers.push_back(inputBufferSpawner.Spawn());
        }

        OutputBufferSpawner outputBufferSpawner
        {
            { outputFilePath, std::ios::out },
            10 * 1024 * 1024 
        };
        
        /*
        FileReader<double> reader
        {
            { tempFilePath + std::to_string(1), std::ios::in },
            new ByteParser{}
        };
        const std::size_t readSize = 5 * 1024 * 1024;

        InputBuffer<double> inputBuffer{ std::move(reader), readSize };

        FileWriter<double> writer
        {
            { outputFilePath, std::ios::out },
            new ValueParser{}
        };
        const std::size_t predWriteSize = 10 * 1024 * 1024 / sizeof(double);
        const std::size_t writeSize = std::min(predWriteSize, valuesCount);

        OutputBuffer<double> outputBuffer{ std::move(writer), writeSize };
        */

        InputBuffer<double>& inputBuffer = inputBuffers.at(0);
        OutputBuffer<double> outputBuffer{ outputBufferSpawner.Spawn() };

        std::cout << "We started merging" << std::endl;

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
        std::cout << std::endl;
    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error] " << exp.what() << std::endl;
    }

    // std::filesystem::remove_all(tempDirPath);

    /*
    std::priority_queue<double> queue{};

    // 3 buffers x 20 mb for input; 1 buffer is for size / 3
    // 1 buffer x 20 mb  for output;

    
    // InputBuffer(startPosition, maxPosition, inputReadSize)
    // 
    // max_position = file_size / 3
    // currentPosition
    // inputReadSize
    //   
    // GetData()
    // Read()
    // GetNext()

    // OutputBuffer

    // currentPosition
    // inputReadSize

    // Write
    // PutData
    // IsFull()
    //  return currentPosition * sizeof(double) == inputReadSize
    //

    std::vector<InputBuffer> m_InputBuffers{};
    OutputBuffer m_OutputBuffer{};

    for (std::size_t i = 0; i < m_InputBuffers.size(); ++i)
    {
        buffer.Read();

        m_OrderedValues.insert({ buffer.GetNextValue(), i });
    }

    while(!m_OrderedValues.empty())
    {
        const auto [value, bufferID] = m_OrderedValues.top();
        m_OrderedValues.pop();

        if (auto& inputBuffer = m_InputBuffers[bufferID];
            inputBuffer.IsLastElement())
        {
            inputBuffer.Read();
        }
        else
        {
            m_OrderedValues.insert({ m_InputBuffer.GetNextValue(), bufferID });
        }

        m_OutputBuffer.Put(value);

        if (m_OutputBuffer.IsFull())
        {
            m_OutputBuffer.Write();
        }
    }
    */

    std::cout << "Happy end" << std::endl;
        
    return EXIT_SUCCESS;
}
