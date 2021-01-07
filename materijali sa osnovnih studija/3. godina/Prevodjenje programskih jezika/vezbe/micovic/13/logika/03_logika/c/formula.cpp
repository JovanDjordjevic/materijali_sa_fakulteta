#include "formula.hpp"

formula::formula(LOGIC_VAL val)
    : m_val(val)
{}

LOGIC_VAL formula::and_op(const formula& f) const
{
    if (m_val == TRUE_VAL && f.m_val == TRUE_VAL)
        return TRUE_VAL;
    else
        return FALSE_VAL;
}

LOGIC_VAL formula::or_op(const formula& f) const
{
    if (m_val == TRUE_VAL || f.m_val == TRUE_VAL)
        return TRUE_VAL;
    else
        return FALSE_VAL;
}

LOGIC_VAL formula::imp_op(const formula& f) const
{
    if (m_val == TRUE_VAL && f.m_val == FALSE_VAL)
        return FALSE_VAL;
    else
        return TRUE_VAL;
}

LOGIC_VAL formula::eq_op(const formula& f) const
{
    if (m_val == f.m_val)
        return TRUE_VAL;
    else
        return FALSE_VAL;
}

LOGIC_VAL formula::not_op() const
{

    if (m_val == TRUE_VAL)
        return FALSE_VAL;
    else
        return TRUE_VAL;
}

std::string formula::str() const
{
    if (m_val == TRUE_VAL) return "True";
    else return "False";
}

LOGIC_VAL formula::val() const
{
    return m_val;
}
