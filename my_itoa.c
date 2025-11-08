#include <stdio.h>
#include <stdlib.h>

static size_t numlen(int n)
{
    size_t len = 0;
    if (n <= 0)
    {
        ++len;
        n = -n;
    }

    while(n != 0)
    {
        n /= 10;
        ++len;
    }

    return len;
}

char *itoa(const int num)
{
    int x = num;
    int len = (int)numlen(num);

    char *ascii = (char *)malloc((len + 1) * sizeof(char));
    if (!ascii)
        return NULL;

    ascii[len] = '\0';
    if (x < 0)
    {
        ascii[0] = '-';
        x = -x;
    }

    while (--len >= 0 && ascii[len] != '-')
    //for (int i = (int)len - 1; i >= 0 && ascii[i] != '-'; --i)
    {
        ascii[len] = (x % 10) + '0';
        x /= 10;
    }

    return ascii;
}

int main()
{
    char *num = itoa(214748364);
    printf("%s\n", num);
    free(num);

    return 0;
}
