#pragma once

# include <vector>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>

# define stringVector std::vector<std::string>

class BitcoinExchange
{
    public :
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &other);
        BitcoinExchange &operator=(BitcoinExchange const &other);
        ~BitcoinExchange();

        void parseInputFile(std::string path);
        void showResults() const;

    private :
        std::map<std::string,float> fileRates;
        stringVector results;

        void ParseFromDB();
        float getRate(std::string date);
        void getRateFromDB(std::string date, float count);


        stringVector getFile(std::string fileName);
        float TryParseCount(std::string cell);

        class FileOpenException : public std::exception
        {
            public:

                virtual const char* what() const throw();
        };

        class FileLengthException : public std::exception
        {
            public:

                virtual const char* what() const throw();
        };

        class FileSizeException : public std::exception
        {
            public:

                virtual const char* what() const throw();
        };

};

std::vector<std::string> ft_split(const std::string &str, const std::string &charset);
bool	ft_in_charset(char const c, const std::string &charset);

template <typename T>
std::string to_string(const T& value);