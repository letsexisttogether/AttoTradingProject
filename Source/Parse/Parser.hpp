#pragma once

#include <string>
#include <vector>

class Parser
{
public:
    using Buffer = std::vector<char>;

public:
    Parser() = default;

    virtual ~Parser() = default;

    virtual Buffer Parse(const Buffer& buffer) noexcept = 0;
};

