#pragma once

#include <ios>
#include <filesystem>

struct FileInfo
{
    std::filesystem::path Path{};
    std::ios::openmode OpenMode{};
};
