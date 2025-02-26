#include "Sorter.hpp"

Sorter::Sorter(FileDataSource&& dataSource)
    : m_DataSource{ std::move(dataSource) }
{}

void Sorter::Sort() noexcept
{
    Sort(0, m_DataSource.Count() - 1);
}

void Sorter::Sort(const Index left, const Index right) noexcept
{
    if (left >= right)
    {
        return;
    }

    const Index pivot = Partition(left, right);

    if (pivot > 0)
    {
        Sort(left, pivot - 1);
    }

    Sort(pivot + 1, right);
}

Sorter::Index Sorter::Partition(const Index left, const Index right)
    noexcept
{
    const double pivot = m_DataSource.ReadValueAt(right);

    Index i = left - 1;

    for (Index j = left; j < right; ++j)
    {
        const bool isLess = m_DataSource.ReadValueAt(j) < pivot;
        
        if (isLess)
        {
            Swap(++i, j);
        }
    }

    Swap(++i, right);

    return i;
}

void Sorter::Swap(const Index left, const Index right) noexcept
{
    const double temp = m_DataSource.ReadValueAt(left);
    m_DataSource.WriteValueAt(m_DataSource.ReadValueAt(right), left); 
    m_DataSource.WriteValueAt(temp, right);
}
