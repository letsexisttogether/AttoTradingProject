#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <vector>

#include "Parse/Parser.hpp"
#include "FileInfo.hpp"

class FileTransformer
{
public:
    using Size = std::size_t;

public:
    FileTransformer() = default;
    FileTransformer(const FileTransformer&) = delete;
    FileTransformer(FileTransformer&&) = delete;

    FileTransformer(FileInfo&& inputInfo, FileInfo&& outputInfo,
        const Size chunkSize, Parser* const parser);

    ~FileTransformer() = default;

    void Standartize() noexcept;

private:
    FileInfo m_InputInfo;
    FileInfo m_OutputInfo;

    std::ifstream m_InputStream;
    std::ofstream m_OutputStream;

    Size m_ChunkSize;

    std::unique_ptr<Parser> m_Parser;
};
