#pragma once

#include <string>

#include "Parse/Parser.hpp"

class ByteParser : public Parser<char, double>
{
public:
    ParserUsings(char, double);

public:
    ByteParser() = default;

    ~ByteParser() = default;

    OutputBuffer Parse(const InputBuffer& buffer) noexcept override;

private:
    std::string m_RemainingData{};
};
