#include <stdio.h>
#include <stdlib.h>

int my_strcat_repoint(char *restrict *ps1, const char *restrict s2) {
    if (!ps1 || !s2) return -1;

    size_t tsize = 0;
    const char *p = (*ps1) ? *ps1 : "";
    while (*p != '\0') { tsize++; p++; }
    p = s2;
    while (*p != '\0') { tsize++; p++; }
    tsize++;

    char *s3 = (char *)malloc(tsize);
    if (!s3) return -1;

    char *d = s3;
    p = (*ps1) ? *ps1 : "";
    while (*p != '\0') { *d++ = *p++; }

    p = s2;
    while (*p != '\0') { *d++ = *p++; }

    *d = '\0';

    free(*ps1);
    *ps1 = s3;
    return 0;
}

int main(void) {
    char *s1 = NULL;
    my_strcat_repoint(&s1, "Hello");
    my_strcat_repoint(&s1, " World!");
    printf("%s\n", s1);
    free(s1);
    return 0;
}
