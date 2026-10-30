#include "RPN.hpp"

RPN::RPN(): _expr(""), _result(0), _stack()
{

}

bool RPN::is_operator(int c)
{
    if(c == '+' || c == '-' || c == '/' || c == '*')
        return (true);
    return (false);
}

double RPN::perform_operation(int operation)
{
    double num1;
    double num2;

    num2 = _stack.top();
    _stack.pop();
    num1 = _stack.top();
    _stack.pop();
    if(operation == '+')
        _result = num1 + num2;
    else if(operation == '-')
        _result = num1 - num2;
    else if(operation == '*')
        _result = num1 * num2;
    else if(operation == '/')
    {
        if(num2 == 0)
            throw std::domain_error("Error: Division by zero");
        else 
            _result = num1 / num2;
    }
    _stack.push(_result);
    return (_result);
}

bool RPN::is_space(int c)
{
    std::string white_space = "\t\n\r\f\v ";

    for (size_t i = 0; i < white_space.length(); i++)
    {
        if(c == white_space[i])
            return (true);
    }
    return (false);
}

RPN::RPN(std::string expr): _expr(expr), _result(0)
{
    for(size_t i=0; i < _expr.length(); i++)
    {
        if(is_space(_expr[i]))
            continue;
        if(std::isdigit(_expr[i]))
        {
            _stack.push(_expr[i] - '0');
            continue;
        }
        if(!is_operator(_expr[i]))
            throw std::invalid_argument("Error: Invalid Token");
        if(_stack.size() < 2)
            throw std::invalid_argument("Error: Invalid Syntax");
        perform_operation(_expr[i]);
    }
    if(_stack.size() > 1)
        throw std::invalid_argument("Error: Invalid Syntax");
    std::cout << _result << std::endl;
}

RPN::RPN(const RPN &other): _expr(other._expr), _result(other._result), _stack(other._stack)
{

}

RPN &RPN::operator=(const RPN &other)
{
    if(this != &other)
    {
        _expr = other._expr;
        _result = other._result;
        _stack = other._stack;
    }
    return (*this);
}

RPN::~RPN()
{

}

double RPN::get_result() const
{
    return (_result);
}

std::string RPN::get_expression() const
{
    return(_expr);
}