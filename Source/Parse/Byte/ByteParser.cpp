#include "ByteParser.hpp"

#include <iostream>

ByteParser::OutputBuffer ByteParser::Parse(const InputBuffer& buffer) noexcept
{
    OutputBuffer parsedValues{};
    
    std::string doubleAsStr{ m_RemainingData }; 

    for (std::size_t i = 0; i < buffer.size(); ++i)
    {
        const char symbol = buffer[i];

        if (symbol != '\n')
        {
            doubleAsStr += symbol;

            continue;
        }

        try
        {
            const double value = std::stod(doubleAsStr);

            parsedValues.push_back(value);
        }
        catch (const std::exception& exp)
        {
            std::cerr << "[Error] The provided value \"" << doubleAsStr
                << "\" is not double precision: " << exp.what() << std::endl;

            m_RemainingData.clear();

            break;
        }

        doubleAsStr.clear();
    }

    m_RemainingData = doubleAsStr;

    return parsedValues;
}
