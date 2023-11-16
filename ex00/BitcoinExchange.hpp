#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>


int check_pipe(std :: string str);
void parse_input_file(char *argv);
int check_is_valide_date(std :: string date);
float check_float(std :: string line);
std :: pair<std :: string,float>  parse_lines(std :: string line,int i);
std :: multimap<std :: string,float> read_input_content(char *argv);
void check_data_file();
void read_data_file();
void parse_data(std :: string line);
std :: multimap<std :: string,float> fill_data_file();