#include "ValueParser.hpp"

#include <iostream>
#include <cstring>
#include <sstream>

ValueParser::Buffer ValueParser::Parse(const Buffer& buffer) noexcept
{
    Buffer parsedValues;
    parsedValues.reserve(buffer.size());  

    Buffer tempBuffer{ m_RemainingData };
    tempBuffer.insert(tempBuffer.end(), buffer.begin(), buffer.end());

    std::size_t i = 0;
    constexpr std::size_t doubleSize = sizeof(double);

    while (i + doubleSize <= tempBuffer.size()) 
    {
        double value{};
        std::memcpy(&value, tempBuffer.data() + i, doubleSize); 
        i += doubleSize;

        std::ostringstream oss;
        oss << value << '\n';

        std::string valueStr = oss.str();
        parsedValues.insert(parsedValues.end(), valueStr.begin(), valueStr.end());
    }

    m_RemainingData.assign(tempBuffer.begin() + i, tempBuffer.end());

    return parsedValues;
}
