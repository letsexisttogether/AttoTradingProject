#pragma once

#include "Parse/Parser.hpp"

class ValueParser : public Parser<double, char>
{
public:
    ParserUsings(double, char);

public:
    ValueParser() = default;

    ~ValueParser() = default;

    OutputBuffer Parse(const InputBuffer& buffer) noexcept override;

private:
    InputBuffer m_RemainingData{};
};
