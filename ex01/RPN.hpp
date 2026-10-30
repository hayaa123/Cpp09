#pragma once
#include <string>
#include <cctype>
#include <stack>
#include <iostream>


class RPN
{
    public:
        RPN();
        RPN(std::string expr);
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();
        double get_result() const;
        double perform_operation(int operation);
        std::string get_expression() const;
    private:
        std::string _expr;
        double _result;
        std::stack<int> _stack;
        static bool is_operator(int c);
        static bool is_space(int c);
};
