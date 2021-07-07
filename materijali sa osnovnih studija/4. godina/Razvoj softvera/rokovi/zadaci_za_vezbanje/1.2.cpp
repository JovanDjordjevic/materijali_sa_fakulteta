#include <iostream>
#include <vector>
#include <map>

template<typename T>
class splitter
{
public:
    splitter(std::map<int, T> values) 
        : m_values(values) 
    {}

    std::vector<T> operator()(int key){
        std::vector<T> v;
        for(const auto& entry : m_values){
            if(entry.first < key){
                v.push_back(entry.second);
            }
        }
        return v;
    }

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