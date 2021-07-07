#include <iostream>
#include <vector>
#include <numeric>

template<typename T>
class averager{

public:
    averager() : values() {}

    void save_value(T new_val){
        values.push_back(new_val);
    }

    //--------------------------------
    double operator()(){
        auto sum = std::accumulate(std::begin(values), std::end(values), 0 );
        return double(sum) / double(values.size());
    }
    //--------------------------------

private:
    std::vector<T> values;

};

int main(){

    averager<int> a;

    a.save_value(5);
    a.save_value(5);
    a.save_value(4);
    a.save_value(4);

    std::cout << a() << std::endl;

    return 0;
}