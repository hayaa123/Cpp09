#include "BitcoinExchange.hpp"

std::string strip(std::string str)
{
    size_t j;
    size_t k;

    j = str.find_first_not_of(WHITESPACE);
    if(j == std::string::npos)
        j = 0;
    k = str.find_last_not_of(WHITESPACE);
    if(k == std::string::npos)
        k = 0;
    return (str.substr(j,k - j + 1));
}

std::list<std::string> split(std::string str, char delimiter)
{
    std::list<std::string> result;
    size_t start = 0;
    size_t found = str.find(delimiter);

    while(found != std::string::npos)
    {
        result.push_back(strip(str.substr(start, found - start)));
        start = found + 1;
        found = str.find(delimiter, found + 1);
    }
    result.push_back(strip(str.substr(start, str.length() - start)));
    return result;
}

bool is_all_digit(std::string text)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        if(!std::isdigit(text[i]))
            return(0);
    }
    return (1);
}

bool is_number(std::string str)
{
    size_t i = 0;
    if(str[i] == '-' || str[i] == '+')
        i++;
    while(i < str.length())
    {
        if(!std::isdigit(str[i]))
            return (false);
        i++;
    }
    return(true);
}

bool extract_date(std::string date, int &year,int &day,int &month)
{
    std::list<std::string> words = split(date,'-');
    std::list<std::string>::iterator iter = words.begin();

    if(words.size() != 3)
        return (false);
    if(!is_all_digit(*iter) || (*iter).length() < 4)
        return (false);
    year = std::atoi((*iter).c_str());
    iter++;
    if(!is_number(*iter) || (*iter).length() > 2)
        return (false);
    month = std::atoi((*iter).c_str());
    iter++;
    // Day check
    if(!is_number(*iter) || (*iter).length() > 2)
        return (false);
    day = std::atoi((*iter).c_str());
    return (true);
}

