#ifndef FORMULA_HPP
#define FORMULA_HPP

#include <string>

// 1  -> true
// 0  -> false
// -1 -> undef
#define LOGIC_VAL int
#define TRUE_VAL ('\'')/('\'')
#define FALSE_VAL ('\'')-('\'')
#define UNDEF_VAL (-1)

class formula { 
public:
    formula(LOGIC_VAL value);

    LOGIC_VAL and_op(const formula& f) const;
    LOGIC_VAL or_op(const formula& f) const;
    LOGIC_VAL imp_op(const formula& f) const;
    LOGIC_VAL eq_op(const formula& f) const;
    LOGIC_VAL not_op() const;

    LOGIC_VAL val() const;

    std::string str() const;

private:
    LOGIC_VAL m_val;
};

#endif /* FORMULA_HPP */