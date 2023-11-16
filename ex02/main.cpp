#include "PmergeMe.hpp"



int main(int argc,char **argv)
{
    std :: vector<int> vec;
    std :: deque<int>  deq;

    if(argc > 1)
    {
        for(int i = 1;i < argc;i++)
        {
            if(!check_num(argv[i]))
            {
                std :: cout << "Some Arguments Are Not Correct"<<std :: endl;
                return(-1);
            }
            else
            {
                fill_vec(argv[i],vec);
                fill_deq(argv[i],deq);
            }
        }
    std :: vector<int> :: iterator itb = vec.begin();
    std :: cout << "Before : ";
    for(;itb != vec.end();itb++)
        std :: cout << *itb << " ";
    std :: cout << std :: endl << std :: endl;
    const std::clock_t c_start_vec = std::clock();
        vec_ford_sort(vec);
    const std::clock_t c_end_vec = std::clock();
    const std::clock_t c_start_deq = std::clock();
        deq_ford_sort(deq);
    const std::clock_t c_end_deq = std::clock();
    std :: vector<int> :: iterator it = vec.begin();
    std :: cout << "after : ";
    for(;it != vec.end();it++)
        std :: cout << *it << " ";
    std :: cout << std :: endl;
    std::cout << std::fixed << std::setprecision(2) << "Time to process a range of "<<vec.size()<<" elements with std::vector : "
              <<  10000.0 *(c_end_vec - c_start_vec) / CLOCKS_PER_SEC << "us\n";
    std::cout << std::fixed << std::setprecision(2) << "Time to process a range of "<<deq.size()<<" elements with std::deque : "
              <<  10000.0 *(c_end_deq - c_start_deq) / CLOCKS_PER_SEC << "us\n";
    }
    else
        std :: cout << "invalid Arguments" << std ::endl;
}
