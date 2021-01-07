#include "formula.hpp"

formula::formula(LOGIC_VAL val)
    : m_val(val)
{}

LOGIC_VAL formula::and_op(const formula& f) const
{
    if (m_val == FALSE_VAL || f.m_val == FALSE_VAL)
        return FALSE_VAL;
    else if (m_val == TRUE_VAL && f.m_val == TRUE_VAL)
        return TRUE_VAL;
    else
        return UNDEF_VAL;
}

LOGIC_VAL formula::or_op(const formula& f) const
{
    if (m_val == FALSE_VAL && f.m_val == FALSE_VAL)
        return FALSE_VAL;
    else if (m_val == TRUE_VAL || f.m_val == TRUE_VAL)
        return TRUE_VAL;
    else
        return UNDEF_VAL;
}

LOGIC_VAL formula::imp_op(const formula& f) const
{
    // -------------------------------------------------------------------------
    // p => q === ~p || q
    // -------------------------------------------------------------------------
    // Ovde umesto dinamicke alokacije pravimo objekat kao lokalnu promenljivu.
    // Ovo je dozvoljeno u c++-u i razlikuje se u odnosu na jezik Java
    // gde su objekti uvek dinamicki alocirani.
    // Objekat 'negirano_this' ce automatski biti dealociran kada se zavrsi
    // izvrsavanje funkcije 'imp_op'.
    // -------------------------------------------------------------------------
    formula negirano_this = formula(this->not_op()); // ~p
    return negirano_this.or_op(f); // ~p || q
}

LOGIC_VAL formula::eq_op(const formula& f) const
{
    // -------------------------------------------------------------------------
    // a <=> b === (a => b) && (b => a)
    // -------------------------------------------------------------------------
    formula tmp1 = formula(this->imp_op(f)); // a=>b
    formula tmp2 = formula(f.imp_op(*this)); // b=>a
    return tmp1.and_op(tmp2);
}

LOGIC_VAL formula::not_op() const
{
    if (m_val == UNDEF_VAL)
        return UNDEF_VAL;
    else if (m_val == TRUE_VAL)
        return FALSE_VAL;
    else
        return TRUE_VAL;
}

std::string formula::str() const
{
    if (m_val == TRUE_VAL) return "True";
    else if (m_val == FALSE_VAL) return "False";
    else return "Undef";
}

LOGIC_VAL formula::val() const
{
    return m_val;
}
