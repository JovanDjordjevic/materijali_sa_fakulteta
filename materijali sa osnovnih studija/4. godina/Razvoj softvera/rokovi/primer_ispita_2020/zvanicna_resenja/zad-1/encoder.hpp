#ifndef __ENCODER_HPP
#define __ENCODER_HPP

#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

class Encoder
{
public:
    explicit Encoder(int encoding_step)
        : m_encoding_step(encoding_step)
    {
    }

    string operator()(const string &str) const
    {
        if (is_empty(str)) {
            return str;
        }

        string result;
        transform(cbegin(str), cend(str), back_inserter(result), [&](const char x){
            return encode_first_char(x)[0];
        });

        return result;
    }

private:
    inline const static string INVALID_HASH = "#";
    inline const static string VALID_LOWERS = "abcdefghijklmnopqrstuvwxyz";

    bool is_empty(const string &str) const
    {
        return str == "";
    }

    auto find_among_lower_characters(const char char_to_find) const
    {
        return find(cbegin(VALID_LOWERS), cend(VALID_LOWERS), char_to_find);
    }

    bool is_valid_lower_char(string::const_iterator iter) const
    {
        return iter != cend(VALID_LOWERS);
    }

    string encode_lower_char(string::const_iterator iter) const
    {
        const auto cycle_min = distance(iter, cbegin(VALID_LOWERS));
        const auto cycle_max = distance(iter, cend(VALID_LOWERS));
        const auto cycle_length = cycle_max - cycle_min;
        auto tmp_step = m_encoding_step;
        while (tmp_step >= cycle_max) {
            tmp_step -= cycle_length;
        }
        while (tmp_step < cycle_min) {
            tmp_step += cycle_length;
        }
        const auto encoded_char_iter = iter + tmp_step;
        return string(1, *encoded_char_iter);
    }

    string encode_first_char(const char & first_char) const
    {
//        const auto first_char = str[0];
        const auto iter = find_among_lower_characters(first_char);
        if (is_valid_lower_char(iter)) {
            return encode_lower_char(iter);
        }

        // Provera ako je veliko slovo...

        // Provera ako je cifra...

        return INVALID_HASH;
    }

    int m_encoding_step;
};

#endif
