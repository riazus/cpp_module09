#include "RPN.hpp"

RPN::RPN(std::string expression)
{
    this->expression = expression;
    this->expLen = expression.size();
}

RPN::~RPN() {}

int RPN::execute()
{
    for(int i = 0; i < expLen; i++)
    {
        if (std::isdigit(expression[i]))
            operands.push(expression[i] - '0');
        else if (isOperator(expression[i]))
        {
            if (operands.size() < 2)
                throw RPNException("Not Enough Operands Exception");
            int op2 = operands.top();
            operands.pop();
            int op1 = operands.top();
            operands.pop();

            switch(expression[i]) {
                case '+':
                    operands.push(op1 + op2);
                    break;
                case '-':
                    operands.push(op1 - op2);
                    break;
                case '*':
                    operands.push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0) 
                        throw RPNException("Dividing By Zero Exception");
                    operands.push(op1 / op2);
                    break;
            }
        }
        else if (expression[i] == ' ')
            continue;
        else
        {
            std::string str = "Invalid Character Exception => \'";
            str += expression[i];
            str += '\'';
            throw RPNException(str.c_str());
        }
    }

    if (operands.size() != 1)
        throw RPNException("Not Enough Operands Exception");
    
    return operands.top();
}

bool RPN::isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '/' || ch == '*');
}