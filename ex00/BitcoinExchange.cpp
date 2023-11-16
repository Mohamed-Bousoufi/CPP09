#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

int check_pipe(std ::string str)
{
	int fnd = 0;
	size_t index = str.find('|');
	while (index != std ::string ::npos)
	{
		fnd++;
		index = str.find('|', index + 1);
	}
	return (fnd);
}

std ::string tirm_string(std ::string str)
{
	int start = 0;
	int high = str.size();

	std :: string :: iterator it = str.begin();
	std :: string :: iterator end = str.end();
	end--;
	while(isspace(*it))
	{
		it++;
		start++;
	}
	while(isspace(*end))
	{
		end--;
		high--;
	}
	return(str.substr(start,(high - start)));
}

void parse_input_file(char *argv)
{
	std ::ifstream inputFile;

	inputFile.open(argv);

	if (inputFile.is_open())
	{
		if (inputFile.get() == EOF)
		{
			std ::cout << "Error: file is empty." << std ::endl;
			inputFile.close();
			exit(-1);
		}
		inputFile.unget();
		std ::string first_line;
		getline(inputFile, first_line);
		first_line = tirm_string(first_line);
		if (first_line.empty() || first_line.compare("date | value"))
		{
			std ::cout << "Error: invalid file" << std ::endl;
			inputFile.close();
			exit(-1);
		}
	}
	else
	{
		std ::cout << "Error: could not open file." << std ::endl;
		inputFile.close();
		exit(-1);
	}
}

int check_is_valide_date(std ::string date)
{
	if(date.size() > 10)
		return(1);
	std ::tm tme;
	const char *str = date.c_str();
	str = const_cast<char *>(str);
	if(strptime(const_cast<char *>(str),"%Y-%m-%d",&tme))
	{
		if((tme.tm_year + 1900) < 2009 )
			return(1);
		if((tme.tm_year+1900) > 2022)
			return(1);
		if((tme.tm_year + 1900) <= 2009 && tme.tm_mon <= 0 && tme.tm_mday < 2)
			return(1);
		if((tme.tm_year + 1900) >= 2022 && tme.tm_mon >= 2 && tme.tm_mday >29)
			return(1);
		if(tme.tm_mday < 1 || tme.tm_mday > 31 || tme.tm_mon < 0 || tme.tm_mon> 11)
			return(1);
		if((tme.tm_year + 1900)%4 == 0  && (tme.tm_year + 1900)%100 != 0 && (tme.tm_year + 1900)%400 != 0&& tme.tm_mon == 1 && tme.tm_mday > 29)
			return(1);
		if((tme.tm_year + 1900)%4 != 0 && tme.tm_mon == 1 && tme.tm_mday > 28)
			return(1);
		else
			return(0);
	}
	else
		return(0);
}
float check_float(std ::string line)
{
	std ::string ::iterator it = line.begin();

	int point = 0;
	int flt = 0;
	size_t size = 0;
	for (; it != line.end(); it++)
	{
		if (isdigit(*it) || (*it == '.' && point == 0) || (*it == 'f' && flt == 0 && *it == line.back() ))
		{
			if ((*it == '.' && point == 0))
				point++;
			if ((*it == 'f' && flt == 0))
				flt++;
			size++;
		}
	}
	if (size != line.size())
		return (-1);
	return (strtod(line.c_str(), NULL));
}

std ::pair<std ::string, float> parse_lines(std ::string line, int i)
{
	std ::pair<std ::string, float> Content;
	std::string str;
	char temp[20];
	sprintf(temp, " %02d ", i);
	str = temp;
	line = tirm_string(line);
	if (line.empty())
	{
		Content.first = str + line;
		Content.second = -1;
		return (Content);
	}
	int delm = line.find('|');

	std ::string date = tirm_string(line.substr(0, delm));

	if (check_is_valide_date(date))
	{
		Content.first = str + "Error: bad input =>" +line;
		Content.second = -1;
		return (Content);
	}
	std ::string floating = tirm_string(line.substr(delm + 1, line.size()));
	if (check_float(floating) == -1 || floating.empty())
	{
		Content.first = str + "Error: not a positive number or number not found.";
		Content.second = -1;
		return (Content);
	}
	if (check_float(floating) > 1000)
	{
		Content.first = str + "Error: too large a number.";
		Content.second = -1;
		return (Content);
	}

	Content.first = str + date;
	Content.second = check_float(floating);
	return (Content);
}

std :: multimap<std :: string,float> read_input_content(char *argv)
{
	std ::ifstream inputFile;

	inputFile.open(argv);
	std ::string line;
	int size = 0;
	while (getline(inputFile, line))
	{
		size++;
	}

	inputFile.close();
	inputFile.open(argv);
	inputFile.seekg(0, std ::ios ::beg);
	std ::string Content_of_string[size];
	for (int i = 0; i < size; i++)
	{
		getline(inputFile, line);
		Content_of_string[i] = line;
	}
	std ::multimap<std::string, float> map_Content;
	for (int i = 1; i < size; i++)
	{
		map_Content.insert(parse_lines(Content_of_string[i], i));
	}
	return(map_Content);
}

void parse_data(std :: string line)
{
	line = tirm_string(line);
	if (line.empty())
	{
		std :: cout << line << std :: endl;
		std :: cout << "Data file invalide" << std :: endl;
		exit(-1);
	}
	int delm = line.find(',');

	std ::string date = tirm_string(line.substr(0, delm));

	if (check_is_valide_date(date))
	{
		std :: cout << date <<" Error : Data file : Data part invalide" << std :: endl;
		exit(-1);
	}
	std ::string floating = tirm_string(line.substr(delm + 1, line.size()));
	if ((int)check_float(floating) == -1)
	{
		std :: cout << date <<","<<floating<<" Error : Data file :  floating part invalide" << std :: endl;
		exit(-1);
	}
}

void read_data_file()
{
	std ::ifstream DataFile;

	DataFile.open("data.csv");
	std ::string line;
	int size = 0;
	while (getline(DataFile, line))
	{
		size++;
	}

	DataFile.close();
	DataFile.open("data.csv");
	DataFile.seekg(0, std ::ios ::beg);
	std ::string data_string[size];
	for (int i = 0; i < size; i++)
	{
		getline(DataFile, line);
		data_string[i] = line;
	}
	for (int i = 1; i < size; i++)
	{
		parse_data(data_string[i]);
	}

}
std :: multimap<std :: string,float> fill_data_file()
{
	std ::ifstream DataFile;
	std :: multimap<std :: string,float> data;

	DataFile.open("data.csv");
	std ::string line;
	std :: string firs_part;
	float second;
	int size = 0;
	while (getline(DataFile, line))
	{
		size++;
	}
	DataFile.close();
	DataFile.open("data.csv");
	DataFile.seekg(0, std ::ios ::beg);
	std ::string data_string[size];
	for (int i = 0; i < size; i++)
	{
		getline(DataFile, line);
		data_string[i] = line;
	}
	int delm;
	for (int i = 1; i < size; i++)
	{
		delm = data_string[i].find(',');
		second = strtod(data_string[i].substr(delm+1,data_string[i].size()).c_str(),NULL);
		std :: pair<std :: string,float> p(data_string[i].substr(0,delm),second);
		data.insert(p);
	}

	return(data);
}

void check_data_file()
{
	std ::ifstream dataFile;

	dataFile.open("data.csv");

	if (dataFile.is_open())
	{
		if (dataFile.get() == EOF)
		{
			std ::cout << "Error: data file is empty." << std ::endl;
			dataFile.close();
			exit(-1);
		}
		dataFile.unget();
		std ::string first_line;
		getline(dataFile, first_line);
		first_line = tirm_string(first_line);
		if (first_line.empty() || first_line.compare("date,exchange_rate"))
		{
			std ::cout << "Error: data invalid file" << std ::endl;
			dataFile.close();
			exit(-1);
		}
		read_data_file();
	}
	else
	{
		std ::cout << "Error: could not open file." << std ::endl;
		dataFile.close();
		exit(-1);
	}
}





