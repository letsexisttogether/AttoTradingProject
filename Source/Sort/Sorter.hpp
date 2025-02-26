#pragma once

#include "../FileDataSource/FileDataSource.hpp"

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
    using Index = FileDataSource::Index;

private:
    void Sort(const Index left, const Index right) noexcept;
    Index Partition(const Index left, const Index right) noexcept;

    void Swap(const Index left, const Index right) noexcept;

private:
    FileDataSource m_DataSource;
};

