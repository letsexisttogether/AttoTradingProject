#include "ValueParser.hpp"

#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>

ValueParser::Buffer ValueParser::Parse(const Buffer& buffer) noexcept
{
    Buffer parsedValues;
    parsedValues.reserve(buffer.size());  

    Buffer tempBuffer{ m_RemainingData };
    tempBuffer.insert(tempBuffer.end(), buffer.begin(), buffer.end());

    constexpr std::size_t doubleSize = sizeof(double);
    constexpr std::size_t maxDoubleStrSize = 32; 

    char doubleBuffer[maxDoubleStrSize];

    std::size_t i = 0;
    while (i + doubleSize <= tempBuffer.size()) 
    {
        double value{};
        std::memcpy(&value, tempBuffer.data() + i, doubleSize);
        i += doubleSize;

        const std::int32_t len = std::snprintf(doubleBuffer,
            maxDoubleStrSize, "%.5g\n", value);

        if (len > 0)
        {
            parsedValues.insert(parsedValues.end(), doubleBuffer, doubleBuffer + len);
        }
    }

    m_RemainingData.assign(tempBuffer.begin() + i, tempBuffer.end());

    return parsedValues;
}
