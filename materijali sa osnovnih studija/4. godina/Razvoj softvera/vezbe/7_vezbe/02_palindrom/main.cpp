//proveravamo da li je data niska palindrom
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

bool is_palindrome(const std::string &str)
{   
    //equal uzima iterator na [) segmente iz prve kolekcije (pri cemu pretpostavlja da moze da se stigne do drugog
    //iteratora) i provearava da li je to jednako segmentu druge kolekcije koji pocinje iteratoru koji je treci argument
    //u opstem slucaju equal nece proveriti da li se duzine ova dva intervala poklapaju pa to moramo sami
    return std::equal(begin(str), end(str), rbegin(str));
}

int main()
{
    std::string word = "bananab";
    std::cout << word << ( is_palindrome(word) ? " jeste " : " nije " ) << "palindrom" << std::endl;

    return 0;
}