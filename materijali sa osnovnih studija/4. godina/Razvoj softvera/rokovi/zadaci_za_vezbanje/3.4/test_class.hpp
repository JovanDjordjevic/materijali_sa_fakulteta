#include <map>
#include <string>
#include <iostream>
#include <fstream>

class TermSearch
{   
    public:
        TermSearch(){}

        void addFromDictionary(std::string &filepath);
        void addTerm(std::string &term, std::string &definition);
        std::pair<std::string, std::string> operator()(std::string &search_term);

        std::map<std::string, std::string>& getTerms() { return m_dictionary; }

    private:
        std::map<std::string, std::string> m_dictionary;
};


void TermSearch::addTerm(std::string &term, std::string &definition)
{
    m_dictionary[term] = definition;
}


void TermSearch::addFromDictionary(std::string &filepath)
{
    std::fstream file(filepath);

    while(file.good())
    {
        std::string line;
        getline(file, line);

        size_t separatorPos = line.find_first_of('-');
        std::string term = line.substr(0, separatorPos - 1);
        std::string definition = line.substr(separatorPos + 2, line.length());

        //std::cout << term << " - " << definition << std::endl;

        addTerm(term, definition);
    }

    file.close();
}

std::pair<std::string, std::string> TermSearch::operator()(std::string &search_term)
{
    std::pair<std::string, std::string> returnPair{"", ""};

    auto it = m_dictionary.find(search_term);
    if(it != m_dictionary.end()){
        returnPair.first = it->first;
        returnPair.second = it->second;
    }

    return returnPair;
}