#include "polinomial.hpp"

polinomial::polinomial()
{
}

polinomial::polinomial(const std::vector<float>& coefs)
    : m_coef(coefs)
{
}

void polinomial::add_coef(float c)
{
    m_coef.push_back(c);
}

const std::vector<float>& polinomial::coefs() const
{
    return m_coef;
}

unsigned polinomial::power() const
{
    if (m_coef.empty())
        return 0;
    else
        return this->m_coef.size() - 1;
}

std::ostream& operator<<(std::ostream& out, const polinomial& p)
{
    for (unsigned i = 0; i < p.m_coef.size(); i++) {
        if (p.m_coef[i] > 0) {
            out << " + " << p.m_coef[i] << "x^" << i;
        } else if (p.m_coef[i] < 0) {
            out << p.m_coef[i] << "x^" << i;
        } else {
            // Inace je nula
        }
    }
    return out;
}

polinomial polinomial::operator+(const polinomial& p) const
{
    unsigned stepen = std::max(this->power(), p.power());
    std::vector<float> coefs(stepen + 1);

    for (unsigned i = 0; i < coefs.size(); i++) {
        if (i > this->power() && i > p.power()) {
            coefs[i] = 0;
        } else if (i > this->power()) {
            coefs[i] = p.m_coef[i];
        } else if (i > p.power()) {
            coefs[i] = this->m_coef[i];
        } else {
            coefs[i] = p.m_coef[i] + this->m_coef[i];
        }
    }
    
    return polinomial(coefs); // RVO
}

polinomial operator-(const polinomial& a, const polinomial& b)
{
    unsigned stepen = std::max(a.power(), b.power());
    std::vector<float> coefs(stepen + 1);

    for (unsigned i = 0; i < coefs.size(); i++) {
        if (i > a.power() && i > b.power()) {
            coefs[i] = 0;
        } else if (i > a.power()) {
            coefs[i] = - b.m_coef[i];
        } else if (i > b.power()) {
            coefs[i] = a.m_coef[i];
        } else {
            coefs[i] = a.m_coef[i] - b.m_coef[i];
        }
    }
    
    return polinomial(coefs); // RVO
}

polinomial operator*(const polinomial& a, const polinomial& b)
{
    unsigned deg = a.power() + b.power();
    std::vector<float> coefs(deg + 1, 0);

    for (unsigned i = 0; i < a.m_coef.size(); ++i) {
        for (unsigned j = 0; j < b.m_coef.size(); ++j) {
            coefs[i + j] += a.m_coef[i] * b.m_coef[j];
        }
    }

    return polinomial(coefs);
}

polinomial polinomial::uminus() const
{
    std::vector<float> coefs = m_coef;

    //for (auto i = coefs.begin(); i != coefs.end(); i++)
    //{
        //*i = - *i;
    //}
  
    /*
    for (auto& coef: coefs) {
        coef = - coef;
    }
    */

    for (auto i = coefs.rbegin(); i != coefs.rend(); i++) {
        *i = - (*i);
    }
    
    return polinomial(coefs);
}

bool operator==(const polinomial& a, const polinomial& b)
{
    if (a.power() != b.power()) return false;

    // Polinomi su isti ako su koeficijenti u vektori isti.
    return a.m_coef == b.m_coef;
}

bool operator!=(const polinomial& a, const polinomial& b)
{
    return ! (a == b);
}

