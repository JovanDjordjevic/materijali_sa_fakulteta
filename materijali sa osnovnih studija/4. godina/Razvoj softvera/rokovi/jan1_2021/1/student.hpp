#include <string>
#include <iostream>
#include <vector>

class Student
{   
    public:
        Student(std::string name, double avg)
            : m_name(name), m_avg(avg)
        {}

    public:
        std::string m_name;
        double m_avg;
};

class StudentTest
{   
    public:
        StudentTest(char c, double avg)
        {
            if( c != 'l' && c !='e' && c!='a')
            {
                throw "Invalid argument";
            }
            else
            {
                m_c = c;
                m_avg = avg;
            }
        }

        std::vector<Student> operator()(std::vector<Student> &students)
        {
            std::vector<Student> res;

            for(const auto &s : students)
            {
                if(m_c == 'l' && s.m_avg < m_avg)         res.push_back(s);
                else if(m_c == 'e' && s.m_avg == m_avg)   res.push_back(s);
                else if(m_c == 'a' && s.m_avg > m_avg)    res.push_back(s);
            }

            return res;
        }


    private:
        char m_c;
        double m_avg;
};