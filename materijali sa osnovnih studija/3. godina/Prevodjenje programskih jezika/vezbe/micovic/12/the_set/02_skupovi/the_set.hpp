#ifndef THE_SET
#define THE_SET

#include <iostream>
#include <set>
#include <algorithm> // std::set_union...

class the_set {
public:
    the_set(const std::set<int>& s);
    the_set();
    void add(int val);
    void init(int start, int end);

    // Ne volimo sirove pokazivace pa funkciji stavljamo da prihvata
    // objekat kao const ref.
    the_set* union_op(const the_set& s) const;
    the_set* intersect_op(const the_set& s) const;
    the_set* diff_op(const the_set& s) const;

    friend std::ostream& operator<<(std::ostream& out, const the_set& s);
private:
    std::set<int> m_set;
};

#endif /* ifndef THE_SET */
