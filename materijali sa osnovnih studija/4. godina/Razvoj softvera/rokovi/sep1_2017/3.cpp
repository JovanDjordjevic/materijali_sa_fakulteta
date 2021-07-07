#include <iostream>
#include <map>

template<typename K, typename V>
bool myFind( std::map<K, V> &map, K key )
{   
    auto it = map.find(key);
    if( it != std::end(map))
        return true;
    else return false;
}


int main (){

    std::map<int, int> m1{ {1,2}, {3,4}, {5,6} };
    std::cout << myFind(m1, 2) << " " << myFind(m1, 3) << std::endl;

    std::map<std::string, int> m2{ {"aaa",2}, {"bbb",4}, {"ccc",6} };
    std::cout << myFind(m2, std::string{"aaa"}) << " " << myFind(m2, std::string{"ddd"}) << std::endl;
   

    return 0;
}