#ifndef THE_SET
#define THE_SET

#include <iostream>
#include <set>

class the_set {
public:
    void add(int val);
    void init(int start, int end);

    friend std::ostream& operator<<(std::ostream& out, const the_set& s);
private:
    std::set<int> m_set;
};

#endif /* ifndef THE_SET */
