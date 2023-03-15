#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        BitcoinExchange bitcoin;
        bitcoin.parseInputFile(argv[1]);
        bitcoin.showResults();
    }

    return 0;
}