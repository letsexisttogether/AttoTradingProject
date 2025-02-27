#pragma once

#include "Parse/Parser.hpp"

class ByteParser : public Parser
{
public:
    ByteParser() = default;

    ~ByteParser() = default;

    Buffer Parse(const Buffer& buffer) noexcept;

private:
    std::string m_RemainingData{}; 
};
