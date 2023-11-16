#include "PmergeMe.hpp"
void vecInsertionsort(std::vector<int> &arr)
{
    int index;
    int i,j;
    for(i = 1; i < (int)arr.size();i++)
    {
        index = arr[i];
         j = i - 1;

        while( j >= 0 && arr[j] > index)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1]  = index;
    }
}

void deqInsertionsort(std::deque<int> &arr)
{
    int index;
    int i,j;
    for(i = 1; i < (int)arr.size();i++)
    {
        index = arr[i];
         j = i - 1;

        while( j >= 0 && arr[j] > index)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1]  = index;
    }
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




int check_num(std :: string str)
{ 
    str = tirm_string(str);
    if(str.empty())
        return(0);
    std :: string :: iterator it = str.begin();

    for(; it != str.end();it++)
    {
        if(!(std :: isdigit(*it)) && *it != ' ')
            return(0);
    }
    return(1);
}

void fill_vec(std :: string str,std::vector<int> &vec)
{
    (void) vec;
    std :: stringstream ss(str);
    int num;
    while(!ss.eof())
    {
        ss >> num;
        if(num == INT_MAX)
        {
            std :: cout << "Some Arguments Are Not Correct"<< std :: endl;
            exit(0);
        }

       vec.push_back(num);
    }
    
}

void fill_deq(std :: string str,std::deque<int> &vec)
{
    (void) vec;
    std :: stringstream ss(str);
    int num;
    while(!ss.eof())
    {
        ss >> num;
        if(num == INT_MAX)
        {
            std :: cout << "Some Arguments Are Not Correct"<< std :: endl;
            exit(0);
        }

       vec.push_back(num);
    }
    
}

void vec_search(std::vector<int>& x, int arrayelement) 
{
    
    std :: vector<int> :: iterator it = std::lower_bound(x.begin(), x.end(), arrayelement);
        x.insert(it, arrayelement);
}

void deq_search(std::deque<int>& x, int arrayelement) 
{
    
    std :: deque<int> :: iterator it = std::lower_bound(x.begin(), x.end(), arrayelement);
        x.insert(it, arrayelement);
}

void vec_ford_sort(std::vector<int>& array) 
{
    std ::vector<int> main_chaine;
    std ::vector<int> bind;
    size_t size = (array.size() % 2) ? array.size() - 1 : array.size();
    int odd = array[array.size() - 1];

    for (size_t i = 0; i < size; i+=2) 
    {
        if(i + 1 < size)
        {
            if(array[i + 1] > array[i])
            {
                main_chaine.push_back(array[i + 1]);
                bind.push_back(array[i]);
            }
            else
            {
                main_chaine.push_back(array[i]);
                bind.push_back(array[i + 1]);
            }
        }
    }
    if(array.size()%2 != 0)
        bind.push_back(odd);
    vecInsertionsort(main_chaine);
    for(size_t i = 0;i < bind.size();i++)
        vec_search(main_chaine,bind[i]);

    array = main_chaine;

}

void deq_ford_sort(std::deque<int>& array) 
{
    std ::deque<int> main_chaine;
    std ::deque<int> bind;
    size_t size = (array.size() % 2) ? array.size() - 1 : array.size();
    int odd = array[array.size() - 1];

    for (size_t i = 0; i < size; i+=2) 
    {
        if(i + 1 < size)
        {
            if(array[i + 1] > array[i])
            {
                main_chaine.push_back(array[i + 1]);
                bind.push_back(array[i]);
            }
            else
            {
                main_chaine.push_back(array[i]);
                bind.push_back(array[i + 1]);
            }
        }
    }
    if(array.size()%2 != 0)
        bind.push_back(odd);
    deqInsertionsort(main_chaine);
    for(size_t i = 0;i < bind.size();i++)
        deq_search(main_chaine,bind[i]);

    array = main_chaine;

}