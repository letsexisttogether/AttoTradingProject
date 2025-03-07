#include "ValueParser.hpp"

#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>

ValueParser::OutputBuffer ValueParser::Parse(const InputBuffer& buffer) noexcept
{
    constexpr std::size_t doubleSize = sizeof(double);
    constexpr std::size_t maxDoubleStrSize = 32; 

    OutputBuffer parsedValues{};
    parsedValues.reserve(buffer.size() * maxDoubleStrSize);

    InputBuffer tempBuffer{ m_RemainingData };
    tempBuffer.insert(tempBuffer.end(), buffer.begin(), buffer.end());

    char doubleBuffer[maxDoubleStrSize];

    std::size_t i = 0;
    for (; i < tempBuffer.size(); ++i) 
    {
        const double value = tempBuffer[i];

        const std::int32_t len = std::snprintf(doubleBuffer, maxDoubleStrSize,
            "%.5g\n", value);

        if (len > 0)
        {
            parsedValues.insert(parsedValues.end(), doubleBuffer, doubleBuffer + len);
        }
    }

    m_RemainingData.assign(tempBuffer.begin() + i, tempBuffer.end());

    return parsedValues;
}
