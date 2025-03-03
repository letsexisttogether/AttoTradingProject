#include "Sorter.hpp"

Sorter::Sorter(FileDataSource&& dataSource)
    : m_DataSource{ std::move(dataSource) }
{}

void Sorter::Sort() noexcept
{
    Sort(0, m_DataSource.GetCount() - 1);
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
    const double pivot = m_DataSource.GetValue(left);

    Index i = left - 1;

    for (Index j = left; j < right; ++j)
    {
        const double currentValue = m_DataSource.GetValue(j);
        const bool isLess = currentValue < pivot;
        
        if (isLess)
        {
            // std::swap(pivot, currentValue);
        }
    }
    
    const double lastValue = m_DataSource.GetValue(++i);

    // std::swap(lastValue, pivot);

    return i;
}

