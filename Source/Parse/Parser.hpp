#pragma once

#include <vector>

template <typename _InputType, typename _OutputType>
class Parser
{
public:
    using InputBuffer = std::vector<_InputType>;
    using OutputBuffer = std::vector<_OutputType>;

public:
    Parser() = default;

    virtual ~Parser() = default;

    virtual OutputBuffer Parse(const InputBuffer& inputBuffer) noexcept = 0;
};


#define ParserUsings(InputType, OutputType) \
    using Base = Parser<InputType, OutputType>; \
    using InputBuffer = typename Base::InputBuffer; \
    using OutputBuffer = typename Base::OutputBuffer;
