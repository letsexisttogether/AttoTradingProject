#pragma once

#include <vector>

#include "Parse/Parser.hpp"

class ValueParser : public Parser
{
public:
    ValueParser() = default;

    ~ValueParser() = default;

    Buffer Parse(const Buffer& buffer) noexcept;

private:
    std::vector<char> m_RemainingData{};
};
