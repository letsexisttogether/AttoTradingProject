#include <iostream>
#include <cstdlib>
#include <string>

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

    ExternalSorter sorter
    {
        inputFilePath, outputFilePath,
        90 * 1024 * 1024
    };

    sorter.Sort();
    
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
