#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>

//note: radjeno bez range v3 jer se to ne radi na kursu ove godine

int main (){

    std::vector<int> vect;
    std::copy(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::back_inserter(vect) );

    std::vector<std::pair<int, int>> vectIndexed;
    int i = 1;
    std::transform(std::begin(vect), std::end(vect), std::back_inserter(vectIndexed), 
                  [&](auto &num){ return std::make_pair(num, i++); } );

    /*for(const auto& v : vectIndexed)
    {
        std::cout << v.first << " " << v.second << std::endl;
    }*/

    int res = std::accumulate(std::begin(vectIndexed), std::end(vectIndexed), int(0),
                             [](int &acc, std::pair<int, int> &elem){ 
                                    if(elem.second % 2 == 0){
                                        acc += elem.first;
                                    }
                                    return acc;
                              } );   

    //drugo resenje: samo accumulate bez indeksiranja
    // int index = 1;
    // int sum = std::accumulate(std::begin(vect), std::end(vect), 0
    //                          , [&](int &acc, int &elem)
    //                          {  
    //                             if(index % 2 == 0)
    //                             {  
    //                                 acc += elem;
    //                             }
    //                             index++;
    //                             return acc;
    //                          }); 
    // std::cout << "sum: " << sum << std::endl;                       

    std::cout << "res: " << res << std::endl;

    return 0;
}


