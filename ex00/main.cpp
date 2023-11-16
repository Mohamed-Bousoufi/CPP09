
#include "BitcoinExchange.hpp"
void compare_values(std :: multimap<std::string,float> file,std::multimap<std :: string,float> data)
{
	(void)data;
	int print;
	std :: multimap<std :: string,float> :: iterator  fileit = file.begin(); 
	for(; fileit != file.end(); ++fileit)
	{
		print = -1;
		std :: multimap<std :: string,float> :: iterator  datait = data.begin();
		for(;datait != data.end();++datait)
		{
			if(fileit->first.substr(4,fileit->first.size()) == datait->first )
			{
					std :: cout <<std :: fixed<<std :: setprecision(2)<< fileit->first.substr(4,fileit->first.size()) << "|" << fileit->second * datait->second << std :: endl;
					print = 1;
					break;
			}
			else if(fileit->first.find("Error") != std :: string :: npos)
			{
					std :: cout << fileit->first.substr(4,fileit->first.size()) << std :: endl;
					print = 1;
					break;
			}
		}
		std :: multimap<std :: string,float> :: iterator l;
		l = data.lower_bound(fileit->first.substr(4,fileit->first.size()));
		l = std :: prev(l);
		if(l != data.end() && print == -1)
		{
			std :: cout <<std :: fixed<<std :: setprecision(2)<< fileit->first.substr(4,fileit->first.size()) << " => "<<fileit->second<<" = "<< fileit->second * l->second << std :: endl;
		}
	}
}




int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std :: multimap<std :: string,float> file;
		std :: multimap<std :: string,float> data_base;
        check_data_file();
		parse_input_file(argv[1]);
		file = read_input_content(argv[1]);
		data_base = fill_data_file();
		compare_values(file,data_base);
	}
	else
		std ::cout << "Error: could not open file." << std ::endl;
}