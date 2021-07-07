#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class BigInteger
{
    public:
        BigInteger()
            :_digits({0})
        {}

        BigInteger(string number)
        {   
            /*TDD podrazumeva refaktorisanje posle uspesnog testa, i ovo u komentaru je pre refaktorisanja
                  takodje posle refaktorisanja opet treba testirati sitim testovima da se uverimod a nismo pokvarili
            //pooto TDD kaze da pisemo implementaciju tek toliko da prodje test, a ne da kodiramo unapred
            //za drugi test koji smo napisali dovoljna je samo sledeca linija jer znamo da ce ulaz biti 1 karakter (cifra)
            _digits.push_back(number.back() - '0');
            */
            extractDigits(number);
        }

        int toInt() const
        {
            return accumulate(begin(_digits), end(_digits), 0, 
            [](const auto acc, const auto next){
                return 10*acc + next;
            });
        }

        size_t numberOfDigits() const
        {
            return _digits.size();
        }

    private:
        void extractDigits(string number)
        {
            extractFirstDigit(number);
            extractTail(number);
        }

        void extractFirstDigit(string number)
        {
            _digits.push_back(digitFromChar(number.front()));
        }

        void extractTail(string number)
        {   
            auto tail{number.substr(1)};
            if(tail.empty())
            {
                return;
            }
            extractDigits(tail);
        }

        unsigned digitFromChar(char digit) const
        {
            return static_cast<unsigned>(digit - '0');
        }

        vector<unsigned> _digits;
};