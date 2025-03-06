#pragma once

#include <iostream>

#include "FileProcess/Write/FileWriter.hpp"

template <typename _Type>
class OutputBuffer
{
public:
    using FileWriter = FileWriter<_Type>;

public:
    OutputBuffer() = delete;
    OutputBuffer(const OutputBuffer&) = delete;
    OutputBuffer(OutputBuffer&&) = default;

    OutputBuffer(FileWriter&& fileReader, const std::size_t bufferSize)
        noexcept;

    ~OutputBuffer();

    void PutValue(const _Type value) noexcept(false);

    void Write() noexcept(false);

    bool IsEOF() const noexcept;
    bool IsEnd() const noexcept;

    OutputBuffer& operator = (const OutputBuffer&) = delete;
    OutputBuffer& operator = (OutputBuffer&&) = delete;

private:
    using Data = typename FileWriter::InputData;

private:
    FileWriter m_FileWriter;

    Data m_Data{};
    std::size_t m_Iterator{};
};

template <typename _Type>
OutputBuffer<_Type>::OutputBuffer(FileWriter&& fileWriter,
    const std::size_t bufferSize) noexcept
    : m_FileWriter{ std::move(fileWriter) }
{
    m_Data.resize(bufferSize);
}

template <typename _Type>
OutputBuffer<_Type>::~OutputBuffer() 
{
    m_Data.erase(m_Data.begin() + m_Iterator, m_Data.end());

    try
    {
        Write();
    }
    catch(...)
    {}
}

template <typename _Type>
void OutputBuffer<_Type>::PutValue(const _Type value) noexcept(false)
{
    m_Data.at(m_Iterator++) = value;
}

template <typename _Type>
void OutputBuffer<_Type>::Write() noexcept(false)
{
    m_FileWriter.Write(m_Data);
    m_Iterator = {};
}

template <typename _Type>
bool OutputBuffer<_Type>::IsEOF() const noexcept
{
    return m_FileWriter.IsEOF();
}

template <typename _Type>
bool OutputBuffer<_Type>::IsEnd() const noexcept
{
    return m_Iterator >= m_Data.size();
}
