#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <cstdlib>

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(char *filename)
{
    std::ifstream file(filename);
    std::string line;
    int current_line;

    current_line = 0;
    if(!file.is_open())
        throw std::exception();
    load_data();
    while(std::getline(file, line))
    {
        if(current_line == 0)
        {
            if(!BitcoinExchange::validate_header(line))
            {
                std::cout   << "file header is incorrect it should be \'date | value\'"
                << std::endl;
                throw std::exception();
            }
        }
        else
        {
            process_line(line);
        }
        current_line++;
    }
}

void BitcoinExchange::load_data()
{
        std::ifstream file("data.csv");
        std::string line;
        std::list<std::string> words;

        while(std::getline(file, line))
        {
            words = split(line, ',');
            _map[words.front()] =  std::atof(words.back().c_str());
        }
}

bool BitcoinExchange::validate_header(std:: string header)
{
    std::list<std::string> words = split(header, '|');
    if(words.size() != 2)
        return (0);
    if(words.front() != "date")
        return (0);
    if(words.back() != "value")
        return (0);
    return (1);
}

bool BitcoinExchange::validate_date(std::string date)
{
    int year;
    int month;
    int day;
    if(!extract_date(date, year, day, month))
        return (false);
    if(month < 1 || month > 12)
        return (false);
    if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return (false);
    if(month == 2)
    {
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            if(day > 29)
                return (false);
        }
        else
        {
            if(day > 28)
                return (false);
        }
    }
    if(day > 31 || day < 1)
        return (false);
    return (1);
}


bool BitcoinExchange::validate_value(std::string value, std::string &error_message)
{

    size_t pos;
    float parsed_val;

    pos = value.find('.');
    if(pos != std::string::npos)
    {
        if(!is_number(value.substr(0, pos))
            || !is_number(value.substr(pos + 1, value.length() - pos - 1)))
        {
            error_message = "Error: Invalid value: should be a number.";
            return (false);
        }
    }
    else
        if(!is_number(value))
        {
            error_message = "Error: Invalid value: should be a number.";
            return (false);
        }
    parsed_val = std::atof(value.c_str());
    if(parsed_val < 0)
    {
        error_message = "Error: not a positive number.";
        return (false);
    }
    if(parsed_val > 1000)
    {
        error_message = "Error: value is larger than 1000";
        return (false);
    }
    return (true);
}

void BitcoinExchange::invalid_input_err(std::string line)
{
    std::cerr << "Error: bad input => " << line << std::endl;
}


// upper_bound -> Returns an iterator pointing to the first element that is ((greater)) than key.
void BitcoinExchange::process_line(std::string line)
{
    std::list<std::string> words = split(line, '|');
    std::string value_err;
    std::map<std::string, double>::iterator ex_pair;
    double ex_value;

    if(words.size() != 2)
        return invalid_input_err(line);
    if(!validate_date(words.front()))
    {
        std::cerr << "Error: Invalid date" << std::endl;
        return;
    }
    if(!validate_value(words.back(), value_err))
    {
        std::cerr << value_err << std::endl;
        return;
    }
    ex_pair = _map.upper_bound(words.front());
    if(ex_pair == _map.begin())
    {
        std::cerr << "Error: no exchange rate available for this date." << std::endl;
        return;
    }
    --ex_pair;
    ex_value = ex_pair->second * std::atof(words.back().c_str());
    std::cout << words.front() << " => " << words.back() << " = " << ex_value << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): _map(other._map)
{

}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if(this == &other)
        return (*this);
    _map = other._map;
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}
