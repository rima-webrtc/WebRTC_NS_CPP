#include <iostream>
#include <stdio.h>

int main()
{

      char * apple = (char *)malloc(40);
          short *banana=(int16_t *)apple;
    std::cout<<"apple"<<apple<<std::endl;
    apple+=16;
        std::cout<<"apple"<<apple<<std::endl;
banana+=16;
    std::cout<<"banana"<<banana<<std::endl;

}

//
// g++ -g test_ptr.cc -o test_ptr