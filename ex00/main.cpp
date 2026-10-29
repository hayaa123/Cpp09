#include "BitcoinExchange.hpp"


int main(int argc, char *argv[])
{
    char * filename;
    if(argc !=2)
    {
        std::cerr   << "invalid usage, program usage: ./btc <file_relative_path>"
                    << std::endl;
        return (1);
    }
    filename = argv[1];
    BitcoinExchange bs(filename);
}