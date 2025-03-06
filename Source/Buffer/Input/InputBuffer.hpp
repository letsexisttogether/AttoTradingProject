#pragma once

#include "FileProcess/Read/FileReader.hpp"

template <typename _Type>
class InputBuffer
{
public:
    using FileReader = FileReader<_Type>;

public:
    InputBuffer(FileReader&& fileReader, const std::size_t readSize)
        noexcept;

    _Type GetNext() noexcept;

    void Refill() noexcept;

    bool IsEOF() const noexcept;
    bool IsEnd() const noexcept;

private:
    using Data = typename FileReader::OutputData;

private:
    FileReader&& m_FileReader;

    std::size_t m_ReadSize;

    Data m_Data{};
    std::size_t m_Iterator{};
};


template <typename _Type>
InputBuffer<_Type>::InputBuffer(FileReader&& fileReader, 
    const std::size_t readSize) noexcept
    : m_FileReader{ std::move(fileReader) }, m_ReadSize{ readSize}
{}

template <typename _Type>
_Type InputBuffer<_Type>::GetNext() noexcept
{
    return m_Data[m_Iterator++];
}

template <typename _Type>
void InputBuffer<_Type>::Refill() noexcept
{
    m_Data = m_FileReader.Read(m_ReadSize);
    m_Iterator = {};
}

template <typename _Type>
bool InputBuffer<_Type>::IsEOF() const noexcept
{
    return m_FileReader.IsEOF();
}

template <typename _Type>
bool InputBuffer<_Type>::IsEnd() const noexcept
{
    return m_Iterator >= m_Data.size();
}
