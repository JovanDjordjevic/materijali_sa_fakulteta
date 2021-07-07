#ifndef GENERICFUNCIONS_H
#define GENERICFUNCIONS_H

namespace matf
{   
    //sabloni se smeju cuvati samo u .h fajlovima

    //genericke funkcije pravimo ovako, prvo navedemo kljucnu rec template i u <> stavimo typename T,U,V,K... oznaku za tip
    template<typename T>
    T max(T a, T b)
    {
        return a > b ? a : b;
    }

    //kada imamo vise naziva:
    template<typename ForwardIterator, typename T>
    void iota(ForwardIterator begin, ForwardIterator end, T value)
    {
        while(begin != end)
        {
            *begin = value;
            value++;
            begin++;
        }
    }

    template<typename ForwardIterator, typename T>
    T accumulate(ForwardIterator begin, ForwardIterator end, T init)
    {
        for (; begin != end; begin++)
        {
            init = init + *begin;
        }
        return init;
    }

}

#endif