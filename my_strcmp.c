#include <stdio.h>
#include <string.h>

int my_strncmp(size_t n, const char s1[n], const char s2[n])
{
    for (unsigned int i = 0; i < n; ++i)
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }

    return 0;
}

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        ++s1;
        ++s2;
    }

    return (*s1 - *s2);
}

int main()
{
    char *s1 = "Hello";
    char *s2 = "Hello World!";

    printf("Comparazione tra le stringe \"%s\" e \"%s\".\n", s1, s2);
    printf("Funzione ufficiale: %d\n", strcmp(s1, s2));
    printf("Funzione personale: %d\n\n", my_strcmp(s1, s2));

    size_t limit = 15;

    printf("Comparazione tra le stringe \"%s\" e \"%s\" con limite di %d.\n", s1, s2, limit);
    printf("Funzione ufficiale: %d\n", strncmp(s1, s2, limit));
    printf("Funzione personale: %d\n", my_strncmp(limit, s1, s2));

    return 0;
}
