#include "RPN.hpp"
int main(int argc,char **argv)
{
   if(argc == 2)
   {
        check_parameter(argv[1]);
        push_to_stack(argv[1]);
   }
   else
   std :: cout << "Invalid Parameter !!!" << std :: endl;
}