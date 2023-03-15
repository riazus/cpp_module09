#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
    (void)other;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::parseInputFile(std::string path)
{
    stringVector content = getFile(path);

    for(unsigned long i = 1; i < content.size(); i++)
    {
        stringVector cell = ft_split(content[i], " | ");
        if (cell.size() != 2)
            this->results.push_back("Error: bad input => " + content[i]);
        else if (cell[0].length() != 10)
            this->results.push_back("Error: bad input of date => " + cell[0]);
        else if (cell[1][0] == '-')
            this->results.push_back("Error: not a positive number => " + content[i]);
        else 
            this->getRateFromDB(cell[0], this->TryParseCount(cell[1]));

        //this->fileRates.insert(std::pair<std::string, float>(cell[0], this->TryParseCount(cell[1])));
    }

}

void BitcoinExchange::showResults() const
{
    for(unsigned long i = 0; i < this->results.size(); i++)
        std::cout << results[i] << std::endl;
}

void BitcoinExchange::ParseFromDB()
{

}

void BitcoinExchange::getRateFromDB(std::string date, float count)
{
    std::ifstream file("data.csv");
    bool found = false;
    std::string line;

    if (count == -777)
    {
        this->results.push_back("Error: too large a number");
        return;
    }

    while (std::getline(file, line)) 
    {
        if (line.find(date) != std::string::npos) 
        {
            std::string tmp = line.substr(11, line.length()-11);
            float rate = std::atof(tmp.c_str());
            float fin = count * rate;
            this->results.push_back(date + " => " + to_string(count) + " = " + to_string(fin));
            found = true;
            break;
        }
    }

    if (!found)
        this->results.push_back("Rate on specify date not found => " + date);
}

stringVector BitcoinExchange::getFile(std::string fileName)
{
	std::ifstream file;
	std::string s;

	file.open(fileName.c_str());
	if (!file.is_open())
		throw BitcoinExchange::FileOpenException();
	std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
    data.append("\0");
    if (!data.length())
        throw BitcoinExchange::FileLengthException();
    stringVector content = ft_split(data, "\n");
    int tmplen = content.size();
    if (tmplen == 0)
    {
        throw BitcoinExchange::FileSizeException();
    }
	return content;
}

float BitcoinExchange::TryParseCount(std::string cell)
{
    
    float count = 0;
    if (cell.find('.') != std::string::npos)
    {
        try
        {
            count = std::atof(cell.c_str());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
    {
        try
        {
            long tmp = std::atol(cell.c_str());
            if (tmp > INT_MAX)
                count = -777;
            else
                count = tmp;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    return count;
}

bool	ft_in_charset(char const c, const std::string &charset)
{
	int	i_charset;

	i_charset = 0;
	while (charset[i_charset])
	{
		if (c == charset[i_charset++])
			return true;
	}
	return false;
}

std::vector<std::string> ft_split(const std::string &str, const std::string &charset)
{
	std::vector<std::string> res;
	std::string			tmp;
	unsigned long int   i;

	i = 0;
	while (i < str.length())
	{
		while (i < str.length() && ft_in_charset(str[i], charset))
			i++;
		if (i < str.length())
		{
			tmp = "";
			while (i < str.length() && !ft_in_charset(str[i], charset))
				tmp += str[i++];
			res.push_back(tmp);
		}
	}
	return res;
}

template <typename T>
std::string to_string(const T& value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

const char *BitcoinExchange::FileOpenException::what() const throw()
{
    return "Error: Input file: cannot open";
}

const char *BitcoinExchange::FileLengthException::what() const throw()
{
    return "Error: Input file: invalid file length";
}

const char *BitcoinExchange::FileSizeException::what() const throw()
{
    return "Error: Input file: invalid file size";
}
