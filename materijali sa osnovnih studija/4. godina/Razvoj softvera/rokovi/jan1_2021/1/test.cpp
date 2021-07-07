#define CATCH_CONFIG_MAIN
#include "catch/single_include/catch2/catch.hpp"
#include <string>
#include <vector>

#include "student.hpp"

TEST_CASE("Student", "")
{
    SECTION("Student is constructible", "[cosntructor]")
    {   
        std::string name = "Bean";
        double avg = 6.9;

        REQUIRE_NOTHROW(Student(name, avg));
    }
}

TEST_CASE("StudentTest", "")
{
    SECTION("StudentTest is constructible for valid character", "[cosntructor]")
    {   
        char c = 'l';   //'e'   'a'
        double avg = 5.0;

        REQUIRE_NOTHROW(StudentTest(c, avg));
    }

    SECTION("StudentTest is not constructible for invalid character", "[cosntructor]")
    {   
        char c = 'b';
        double avg = 5.0;

        REQUIRE_THROWS(StudentTest(c, avg));
    }

    SECTION("Call operator for 'l' returns students with avg less than the second paramteter of StudentTest constructor", "[call]")
    {   
        char c = 'l';
        double avg = 8.0;
        std::vector<Student> students{ {"Ime1", 6.7}, {"Ime2", 7.9}, {"Ime3", 8.0},
                                       {"Ime4", 8.0}, {"Ime5", 9.1}, {"Ime6", 9.9}  };
        std::vector<Student> expected{ {"Ime1", 6.7}, {"Ime2", 7.9} };

        StudentTest st(c, avg);
        auto result = st(students);

        REQUIRE( std::equal(std::begin(result), std::end(result), std::begin(expected),
                 [](const Student &s1, const Student &s2){ 
                        return (s1.m_name == s2.m_name && s1.m_avg == s2.m_avg); 
                    })
                 );
    }

    SECTION("Call operator for 'e' returns students with avg equal the second paramteter of StudentTest constructor", "[call]")
    {   
        char c = 'e';
        double avg = 8.0;
        std::vector<Student> students{ {"Ime1", 6.7}, {"Ime2", 7.9}, {"Ime3", 8.0},
                                       {"Ime4", 8.0}, {"Ime5", 9.1}, {"Ime6", 9.9}  };
        std::vector<Student> expected{ {"Ime3", 8.0}, {"Ime4", 8.0} };

        StudentTest st(c, avg);
        auto result = st(students);

        REQUIRE( std::equal(std::begin(result), std::end(result), std::begin(expected),
                 [](const Student &s1, const Student &s2){ 
                        return (s1.m_name == s2.m_name && s1.m_avg == s2.m_avg); 
                    })
                 );
    }

    SECTION("Call operator for 'a' returns students with avg greater than the second paramteter of StudentTest constructor", "[call]")
    {   
        char c = 'a';
        double avg = 8.0;
        std::vector<Student> students{ {"Ime1", 6.7}, {"Ime2", 7.9}, {"Ime3", 8.0},
                                       {"Ime4", 8.0}, {"Ime5", 9.1}, {"Ime6", 9.9}  };
        std::vector<Student> expected{ {"Ime5", 9.1}, {"Ime6", 9.9} };

        StudentTest st(c, avg);
        auto result = st(students);

        REQUIRE( std::equal(std::begin(result), std::end(result), std::begin(expected),
                 [](const Student &s1, const Student &s2){ 
                        return (s1.m_name == s2.m_name && s1.m_avg == s2.m_avg); 
                    })
                 );
    }
}