#pragma once

#include "Parse/Byte/ByteParser.hpp"
#include "Parse/Parser.hpp"
#include <memory>
#include <vector>
#include <fstream>

class InputBuffer
{
public:
    using Data = std::vector<double>;

public:
    InputBuffer() = delete;

    InputBuffer(const InputBuffer&) = delete; 
    InputBuffer(InputBuffer&&) = default; 

    InputBuffer(std::ifstream& fileStream, const std::size_t startPosition,
        const std::size_t chunkSize, const std::size_t maxPosition)
        noexcept(false);

    ~InputBuffer() = default;

    std::size_t Read() noexcept(false);

    Data& GetData() noexcept;
    const Data& GetData() const noexcept;

    InputBuffer& operator = (const InputBuffer&) = delete;
    InputBuffer& operator = (InputBuffer&&) = delete;

private:
    std::ifstream& m_FileStream;

    std::size_t m_MaxPosition;
    std::size_t m_ChunkSize;
    std::size_t m_Position{};

    Data m_Data{}; 

    std::unique_ptr<Parser<char, double>> m_Parser
    {
        std::make_unique<ByteParser>() 
    };
};
