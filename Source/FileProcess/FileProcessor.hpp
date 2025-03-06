#pragma once

#include <cstddef>

#include "General/FileInfo.hpp"

template <class _FileStream>
class FileProcessor
{
public:
    FileProcessor() = delete;
    FileProcessor(const FileProcessor&) = delete;
    FileProcessor(FileProcessor&&) = default;

    FileProcessor(const FileInfo fileInfo) noexcept(false);

    virtual ~FileProcessor() = default;

    virtual std::size_t GetPointer() noexcept = 0;
    virtual void PlacePointer(const std::size_t position) noexcept = 0;

    bool IsOpen() const noexcept;
    bool IsEOF() const noexcept;

protected:
    FileInfo m_FileInfo; 
    _FileStream m_FileStream;
};
