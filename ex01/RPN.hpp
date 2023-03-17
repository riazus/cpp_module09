#include <string>
#include <stack>
#include <stdexcept>

class RPN
{
    public :
        RPN(std::string expression);
        ~RPN();

        int execute();

    private :
        std::string     expression;
        int             expLen;
        std::stack<int> operands;

        bool isOperator(char ch);

};

class RPNException : public std::exception {
    public:
        explicit RPNException(const char* message) : message_(message) {}
        virtual const char* what() const throw() {
            return message_.c_str();
        }
        virtual ~RPNException() throw() {}
    private:
        std::string message_;
};
