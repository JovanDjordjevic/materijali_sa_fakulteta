#include "the_set.hpp"

the_set::the_set(const std::set<int>& s)
    : m_set(s)
{
}

the_set::the_set()
{}

void the_set::add(int val)
{
    m_set.insert(val);
}

void the_set::init(int start, int end)
{
    m_set.clear();
    for (int v = start; v <= end; v++)
        m_set.insert(v);
}

std::ostream& operator<<(std::ostream& out, const the_set& s)
{
    // Radi lepseg formatiranja cemo koristiti standardnu for petlju,
    // ali generalno bi trebalo izbegavati to i koristiti iteratore.
    
    out << '{';
    
    unsigned i = 0;
    for (const auto& e: s.m_set) {
        if (i == s.m_set.size() - 1) {
            out << e;
        } else {
            out << e << ", ";
        }
        i++;
    }
    out << '}';

    return out;
}

the_set* the_set::union_op(const the_set& s) const
{
    std::set<int> result;

    // std::inserter nam omogucava da se u kolekciju std::set dodaje
    // element i takodje obezbedi neophodna memorija pre nego sto se to ucini.

    std::set_union(
        m_set.cbegin(), m_set.cend(),
        s.m_set.cbegin(), s.m_set.cend(),
        std::inserter(result, result.begin())
    );

    return new the_set(result);
}

the_set* the_set::intersect_op(const the_set& s) const
{
    std::set<int> result;

    std::set_intersection(
        m_set.cbegin(), m_set.cend(),
        s.m_set.cbegin(), s.m_set.cend(),
        std::inserter(result, result.begin())
    );

    return new the_set(result);
}

the_set* the_set::diff_op(const the_set& s) const
{
    std::set<int> result;

    std::set_difference(
        m_set.cbegin(), m_set.cend(),
        s.m_set.cbegin(), s.m_set.cend(),
        std::inserter(result, result.begin())
    );

    return new the_set(result);
}
