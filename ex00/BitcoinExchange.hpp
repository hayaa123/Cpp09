#include <iostream>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <cstdlib>

#define WHITESPACE "\t\n\r\f\v "

class BitcoinExchange
{
public:
    BitcoinExchange();
    BitcoinExchange(char *filename);
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    void load_data();

    static bool validate_header(std::string header);
    // static bool validate_and_add(std::string line);
    static bool validate_date(std::string date);
    static bool validate_value(std::string value, std::string &error_message);
    static void invalid_input_err(std::string line);
    // static std::string parse_del(std::string &line);
    // static std::string parse_value(std::string &line);
    void process_line(std::string);
    ~BitcoinExchange();
private:
    std::map<std::string, double> _map;
};

std::string strip(std::string);
std::list<std::string> split(std::string str, char delimiter);
bool is_number(std::string str);
bool is_all_digit(std::string text);