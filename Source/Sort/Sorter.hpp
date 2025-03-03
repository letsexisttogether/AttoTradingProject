#pragma once

#include "Data/FileDataSource.hpp"

class Sorter
{
public:
    Sorter() = delete;
    Sorter(const Sorter&) = delete;
    Sorter(const Sorter&&) = delete;

    Sorter(FileDataSource&& dataSource);

    ~Sorter() = default;

    void Sort() noexcept;

private:
    using Index = FileDataSource::Size;

private:
    void Sort(const Index left, const Index right) noexcept;
    Index Partition(const Index left, const Index right) noexcept;

private:
    FileDataSource m_DataSource;
};

