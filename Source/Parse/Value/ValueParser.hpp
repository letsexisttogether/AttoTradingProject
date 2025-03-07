#pragma once

#include <string>

#include "Parse/Parser.hpp"

class ValueParser : public Parser<double, char>
{
public:
    ParserUsings(double, char);

public:
    ValueParser() = default;
    ValueParser(const ValueParser&) = default;
    ValueParser(ValueParser&&) = default;

    ValueParser(const std::string& format) noexcept;

    ~ValueParser() = default;

    OutputBuffer Parse(const InputBuffer& buffer) noexcept override;

    ValueParser& operator = (const ValueParser&) = delete;
    ValueParser& operator = (ValueParser&&) = delete;

private:
    InputBuffer m_RemainingData{};

    std::string m_OutputFormat{ "%.7g\n" };
};
