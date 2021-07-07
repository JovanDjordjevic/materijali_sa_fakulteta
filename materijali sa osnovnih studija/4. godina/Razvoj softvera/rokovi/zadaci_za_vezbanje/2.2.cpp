//ovaj ne radi

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

template<typename T>
class splitter
{
public:
    splitter(std::map<int, T> values) 
        : m_values(values) 
    {}

     //--------------------------------
    std::vector<T> operator()(int key){
        std::vector<T> v;


        /*std::copy_if(std::begin(m_values), std::end(m_values), std::begin(v), 
                [key](const std::pair<int, T> &entry){ 
                    if(entry.first < key) return entry.second; } );*/

        std::transform(std::begin(m_values), std::end(m_values), std::begin(v), 
                        [&](const std::pair<int, T> &entry){ if(entry.first < key) return entry.second; });


        return v;
    }
    //--------------------------------

private:
    std::map<int, T> m_values;
};



int main(){

    std::map<int, double> testMap = { {1, 2.3}, {2, 3.3}, {3, 4.41}, {6, 7.1} };
    splitter<double> s = splitter<double>(testMap);

    auto res = s(4);
    //auto res = s(10);
    for(const auto& r : res){
        std::cout << r << " ";
    }

    return 0;
}