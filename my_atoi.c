#include <stdio.h>
#include <stdlib.h>

int my_atoi(const char *nptr)
{
    int sign = 1;
    int result = 0;

    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' ||
           *nptr == '\r' || *nptr == '\f' || *nptr == '\v')
    {
        ++nptr;   
    }
    
    while (*nptr == '-' || *nptr == '+')
    {
        if (*nptr == '-')
           sign = sign * -1;

        ++nptr;
    }

    while (*nptr >= '0' && *nptr <= '9')
    {
        int digit = *nptr - '0';
        result = (result * 10) + digit;

        ++nptr;
    }

    return (result * sign);
}

int main()
{
    char x[] = " +21474807";
    printf("%d\n", atoi(x));
    printf("%d\n", my_atoi(x));
    return 0;
}
