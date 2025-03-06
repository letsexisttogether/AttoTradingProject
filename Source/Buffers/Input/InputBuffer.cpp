#include "InputBuffer.hpp"

InputBuffer::InputBuffer(std::ifstream& fileStream,
    const std::size_t startPosition, const std::size_t maxPosition,
    const std::size_t chunkSize) noexcept(false)
    : m_FileStream{ fileStream }, m_Position{ startPosition },
    m_MaxPosition{ maxPosition }, m_ChunkSize{ chunkSize }
{
    if (m_Position + m_ChunkSize >= m_MaxPosition)
    {
        m_FileStream.close();

        throw std::exception{ "It's impossible to read file even once" };
    }
}

std::size_t InputBuffer::Read() noexcept(false)
{
    ByteParser::InputBuffer rawBuffer(m_ChunkSize);

    m_FileStream.read(rawBuffer.data(), m_ChunkSize);

    if (m_FileStream.bad())
    {
        throw std::exception{ "The read operation has failed" };
    }

    m_Data = m_Parser->Parse(rawBuffer);

    const std::size_t readCount = m_FileStream.gcount();
    
    m_Position += readCount;

    return m_FileStream.gcount();
}

InputBuffer::Data& InputBuffer::GetData() noexcept
{
    return m_Data;
}

const InputBuffer::Data& InputBuffer::GetData() const noexcept
{
    return m_Data;
}
