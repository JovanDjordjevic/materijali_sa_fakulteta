#include "the_set.hpp"

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
