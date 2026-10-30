#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cerr << "Invalid usage, the program mush have 2 args:" << std::endl;
        std::cerr << "./RPN \"<your reverse polish notation>\""<< std::endl;
        return (1);
    }
    try
    {
        RPN rpn(argv[1]);
        return(0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (1);
    }
}