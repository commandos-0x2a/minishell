#include <stdio.h>
#include <wait.h>
#include <sys/wait.h>

union u_test
{
    unsigned char data;

    struct s_data
    {
        unsigned int A:7;
        unsigned int B:1;
    }   S_data;
    
};


int main()
{
    union u_test test;

    printf("bit7: %d\n", test.S_data.B);

}