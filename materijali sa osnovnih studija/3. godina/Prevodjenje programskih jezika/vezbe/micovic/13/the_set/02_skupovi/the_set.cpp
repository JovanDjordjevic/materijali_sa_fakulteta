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

bool the_set::contains(int x) const
{
    /* Linearna pretraga
    for (const auto& e: m_set) {
        if (e == x) return true;
    }
    return false;
    */

    // Ugradjena funkcija koja vraca iterator na
    // element koji se trazi. Ako se ne nadje element,
    // vraca se iterator koji se dobija sa .end().
    auto result = m_set.find(x);
    return result != m_set.end();
}

bool the_set::subset(const the_set& s) const
{
    // Opet bi mogli linearnom pretragom da trazimo elemente,
    // no koristeci find mozemo dobiti kompaktniji kod.
    // Dodatno, find potencijalno radi efikasnije od linearne pretrage
    // jer pretrazuje stablo binarnom pretragom.
    //
    // this je podskup od s ako svaki element koji se sadrzi u this
    // postoji u s.
    for (const auto& e: m_set) {
        auto finder = s.elements().find(e);
        // Ako nadjemo da e ne postoji u s onda this nije podskup
        if (finder == s.elements().end()) return false;
    }

    // Inace, uspeli smo za svaki element iz this da pokazemo da je u s
    // cime je this podskup od s.
    return true;
}

const std::set<int>& the_set::elements() const
{
    return m_set;
}

unsigned the_set::card() const
{
    return m_set.size();
}

the_set* the_set::complement(const the_set& s) const
{
    std::set<int> result;
    // UniversalSet = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    // this -> {1, 3, 5, 7, 9}
    // ~this -> {2, 4, 6, 8, 10}
    // Odnosno trazimo elemente iz UniversalSet koji ne postoje u this
    for (const auto& e: s.elements()) {
        auto finder = m_set.find(e);
        if (finder == m_set.end()) {
            // e nije pronadjen u this tako da ga dodajemo u rezultat
            result.insert(e);
        }
    }

    return new the_set(result);
}
