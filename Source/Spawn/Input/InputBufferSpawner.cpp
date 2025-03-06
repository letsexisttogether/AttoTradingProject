#include "InputBufferSpawner.hpp"

InputBufferSpawner::InputBufferSpawner(const FileInfo fileInfo,
    const std::size_t chunkSize) noexcept(false)
    : m_FileInfo{ fileInfo }, m_ChunkSize{ chunkSize },
    m_FileStream{ m_FileInfo.Path, m_FileInfo.OpenMode }
{
    if (!m_FileStream.is_open())
    {
        throw std::exception{ "There's not access to the file" };
    }

    m_FileSize = std::filesystem::file_size(m_FileInfo.Path);
    m_ChunkSize = std::min(m_ChunkSize, m_FileSize);
}
