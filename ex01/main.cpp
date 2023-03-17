#include <iostream>
#include "RPN.hpp"

int main(int argc , char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./RPN \" <some nums> \" " << std::endl;
        return 1;
    }

    RPN rnp(argv[1]);
    try
    {
        int res = rnp.execute();
        std::cout << res << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}