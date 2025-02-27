#include "FileTransformer.hpp"

#include <iostream>
#include <filesystem>

FileTransformer::FileTransformer(FileInfo&& inputInfo, FileInfo&& outputInfo,
    const Size chunkSize, Parser* const parser)
    : m_InputInfo{ std::move(inputInfo) }, m_OutputInfo{ std::move(outputInfo) },
    m_InputStream{ m_InputInfo.Path, m_InputInfo.OpenMode },
    m_OutputStream{ m_OutputInfo.Path, m_OutputInfo.OpenMode },
    m_ChunkSize{ chunkSize }, m_Parser{ parser }
{
    if (const std::filesystem::path& path = m_InputInfo.Path;
        !std::filesystem::exists(path))
    {
        std::cerr << "[Error] A file with the provided path \"" 
            << path << "\" does not exist" << std::endl;
    }
    else 
    {
        const Size inputFileSize = std::filesystem::file_size(path);
        m_ChunkSize = std::min(inputFileSize, m_ChunkSize);

        std::cout << "The chunk's size is " << m_ChunkSize
            << " bytes" << std::endl;
    }
}

void FileTransformer::Standartize() noexcept
{
    Parser::Buffer buffer(m_ChunkSize);

    while(m_InputStream.read(buffer.data(), buffer.size())
        || m_InputStream.gcount() > 0)
    {
        Parser::Buffer parsedValues{ m_Parser->Parse(buffer) };

        m_OutputStream.write(parsedValues.data(), parsedValues.size());
    }
}
