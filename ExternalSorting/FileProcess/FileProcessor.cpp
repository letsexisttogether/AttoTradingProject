#include "FileProcessor.hpp"

#include <fstream>

template <class _FileStream>
FileProcessor<_FileStream>::FileProcessor(const FileInfo& fileInfo)
    noexcept(false)
    : m_FileInfo{ fileInfo },
    m_FileStream{ m_FileInfo.Path, m_FileInfo.OpenMode }
{
    if (!IsOpen())
    {
        throw std::exception{ "Cannot open the specified file" };
    }
}

template <class _FileStream>
FileInfo FileProcessor<_FileStream>::GetFileInfo() const noexcept
{
    return m_FileInfo;
}

template <class _FileStream>
bool FileProcessor<_FileStream>::IsOpen() const noexcept
{
    return m_FileStream.is_open();
}

template <class _FileStream>
bool FileProcessor<_FileStream>::IsEOF() const noexcept
{
    return m_FileStream.eof();
}

template class FileProcessor<std::ifstream>;
template class FileProcessor<std::ofstream>;
