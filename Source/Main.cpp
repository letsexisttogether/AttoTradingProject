#include <iostream>
#include <filesystem>
#include <algorithm>

#include "FileProcess/Read/FileReader.hpp"
#include "FileProcess/Write/FileWriter.hpp"
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

    // 90 Mb for all the buffers at max

    const std::size_t fileSize = std::filesystem::file_size(inputFilePath);
    const std::size_t chunkSize = std::min(45ull * 1024 * 1024, fileSize);

    try
    {
        std::vector<double> data{};

        FileReader<double> reader
        { 
            { inputFilePath, std::ios::in },
            new ByteParser{}
        }; 

        FileWriter<double> writer
        {
            { outputFilePath, std::ios::out },
            new ValueParser{}
        };

        while(!reader.IsEOF())
        {
            data = reader.Read(chunkSize);

            /*
            for (const auto value : data)
            {
                std::cout << value << '\n';
            }
            std::cout << std::endl;
            */

            writer.Write(data);
        }

        std::cout << "The end" << std::endl;
    }
    catch(std::exception& exp)
    {
        std::cerr << "[Error] " << exp.what() << std::endl;
    }


        /*
        std::priority_queue<double> queue{};

        // 3 buffers x 20 mb for input; 1 buffer is for size / 3
        // 1 buffer x 20 mb  for output;

        
        // InputBuffer(startPosition, maxPosition, chunkSize)
        // 
        // max_position = file_size / 3
        // currentPosition
        // chunkSize
        //   
        // GetData()
        // Read()
        // GetNext()

        // OutputBuffer

        // currentPosition
        // chunkSize

        // Write
        // PutData
        // IsFull()
        //  return currentPosition * sizeof(double) == chunkSize
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
        
    return EXIT_SUCCESS;
}
