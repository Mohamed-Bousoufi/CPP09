#include "RPN.hpp"

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


void check_parameter(std :: string str)
{
    str = tirm_string(str);
    if(str.empty())
    {
        std :: cout << "Notation Not Correct " << std :: endl;
        exit(-1);
    }
    std :: string :: iterator it = str.begin();
    size_t valid = 0;
    for(; it != str.end();it++)
    {
        if(std :: isdigit(*it) || *it == '/' || *it == '+'\
        || *it == '-' || *it == '*' || *it == ' ')
            valid++;
    }
    if(valid != str.size())
    {
        std :: cout << "Notation Not Correct " << std :: endl;
            exit(-1);
    }
}

int calcul(int first,int seconde,char cal)
{
    if(cal == '*')
        return(first * seconde);
    else if(cal == '+')
        return(first + seconde);
    else if(cal == '-')
        return(seconde - first);
    else if(cal == '/')
    {
        if(first == 0)
            return(INT_MAX);
        else
        return(seconde/first);
    }
    else
        return(INT_MAX);
}

void push_to_stack(std :: string str)
{
    std :: stack<int> st;
    int num;
    int first;
    int seconde;
    int result;
    std :: string :: iterator it = str.begin();
    for(;it != str.end();it++)
    {
        if(std :: isdigit(*it))
        {
            num = static_cast<int>(*it - '0');
            st.push(num);
        }
        else if((*it == '/' || *it == '+'\
        || *it == '-' || *it == '*') && st.size() >= 2)
        {
            first = st.top();
            st.pop();
            seconde = st.top();
            st.pop();
            result = calcul(first,seconde,*it);
            if(result != INT_MAX)
                st.push(result);
            else
            {
                std :: cout << "Division by zero is not allowed" << std :: endl;
                return;
            }
        }
        else if(*it != ' ')
        {
                std :: cout << "Notation Not Correct 3" << std :: endl;
                return;
        }

    }
    if(st.size() == 1)
        std :: cout << st.top() << std :: endl;
    else
        std :: cout << "Notation Not Correct " << std :: endl;
}