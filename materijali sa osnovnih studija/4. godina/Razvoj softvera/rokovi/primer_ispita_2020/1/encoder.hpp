#include <string>
#include <iostream>

//note: iz nekog razloga jedino ovako sa kastovanjem char-a u int() prolazi sve testove

class Encoder
{
    public:
        Encoder(int n) :  m_pi(n) {}
        int getPi() { return m_pi; }

        std::string& operator()(std::string& str)
        {
            for(unsigned i = 0; i < str.length(); i++)
            {
                if( str[i] >= 97 && str[i] <= 122 ) 
                    str[i] = encodeLowerCase(str[i]);
                else if( str[i] >= 65 && str[i] <= 90 ) 
                    str[i] = encodeUpperCase(str[i]);
                else if( str[i] >= 48 && str[i] <= 57 ) 
                    str[i] = encodeNumber(str[i]);
                else
                    str[i] = '#';
            }

            return str;
        }

        char encodeLowerCase(char c)
        {   
            
            if(m_pi >= 0) m_pi %= 26;
            else m_pi = 26 - ( (m_pi * -1) % 26 );

            int num = int(c) + m_pi;
            if(num > 122) num -= 26;

            return char(num);
        }

        char encodeUpperCase(char c)
        {   
            if(m_pi >= 0) m_pi %= 26;
            else m_pi = 26 - ( (m_pi * -1) % 26 );

            int num = int(c) + m_pi;
            if(num > 90) num -= 26;

            return char(num);
        }

        char encodeNumber(char c)
        {   
            if(m_pi >= 0) m_pi %= 10;
            else m_pi = 10 - ( (m_pi * -1) % 10 );

            int num = int(c) + m_pi;
            if(num > 57) num -= 10;

            return char(num);
        }

    private:
        int m_pi;
};