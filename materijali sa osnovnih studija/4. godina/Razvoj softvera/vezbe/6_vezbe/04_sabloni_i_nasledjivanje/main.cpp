#include <iostream>
#include <string>

//u ovoj klasi T ce biti klasa test
template<typename T>
class equality_testable{
    public:
        bool operator==(const T &other) const{
            //objketi su jednaki ako nisu razliciti
            return !(static_cast<const T&>(*this) != other);
        }

        bool operator!=(const T &other) const{
            //objketi su razliciti ako nisu jendaki
            return !(static_cast<const T&>(*this) == other);
        }
};

//ako imamo template klasu koja treba da se nasledi, moramo obavezno pri nasledjivanju 
//proslediti i tip u <>, i sad kad nasledimo metode iz te kalse radice sa nasim novim tipom
class test : public equality_testable<test>{
    public:
        test(const std::string &data)
        : data_(data)
        {}

        //ideja je da jedan od operatora iz nadklase prevazidjemo ovde
        // a drugi cemo dobiti "besplatno" iz nadklase
        bool operator==(const test& other) const
        {
           return data_ == other.data_; 
        }
    private:
        std::string data_;
};

int main(){

    using namespace std;

    const test t1("data1"), t2("data2");

    cout.setf(ios_base::boolalpha); //true/false umesto 0/1 za cout
    cout << (t1 == t1) << endl;
    cout << (t1 != t1) << endl;
    cout << (t1 == t2) << endl;
    cout << (t1 != t2) << endl;

    return 0;
}