#ifndef PAIR_H
#define PAIR_H

#include <utility>

namespace matf
{   
    //slicno radimo i sablonske klase, a u klasi korisitmo te tipove tamo gde treba

    template<typename T1, typename T2>
    class Pair{
        public:
            Pair(T1 first, T2 second)
              :first_ (first), second_ (second)
            {}

            void swap(Pair &other)
            {
                std::swap(first_, other.first_);
                std::swap(second_, other.second_);
            }

            T1 first_;
            T2 second_;
    };  //kraj klase

    //kada je povratna vrednost nasa sablonska klasa, moramo navesti u <> tipove, slicno kao sto smo imali za npr vector itd
    template<typename T1, typename T2>
    Pair<T1, T2> make_pair(T1 first, T2 second){
        return Pair{first, second};
    }

}

#endif 