#ifndef ppj_POLINOMIAL_HPP
#define ppj_POLINOMIAL_HPP

#include <vector>
#include <iostream>

class polinomial {
public:
    polinomial();
    polinomial(const std::vector<float>& coefs);

    void add_coef(float c);

    // GETeri
    const std::vector<float>& coefs() const;
    unsigned power() const;

    polinomial uminus() const;

    polinomial operator+(const polinomial& p) const;
    friend polinomial operator-(const polinomial& a, const polinomial& b);
    friend polinomial operator*(const polinomial& a, const polinomial& b);

    // Opet imamo izbor kako cemo implementirati operator:
    // 1) bool operator==(const polinomial& p) const;
    // 2) friend bool operator==(const polinomial& a, const polinomial& b);
    // 3) bool provera_jednakosti(const polinomial& a, const polinomial& b);
    // Bice uradjena varijanta pod 2)
    friend bool operator==(const polinomial& a, const polinomial& b);
    friend bool operator!=(const polinomial& a, const polinomial& b);
    

private:
    std::vector<float> m_coef;

    friend std::ostream& operator<<(std::ostream& out, const polinomial& p);
};

#endif
