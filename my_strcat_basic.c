#include <stdio.h>
#include <string.h> // strlen
#include <stddef.h> // size_t

int my_strcat(char *s1, const char *restrict s2) {
    if (!s1 || !s2) return -1;
    while (*s1) s1++;
    
    while ((*s1++ = *s2++)) {}
    return 0;
}

int main(void) {
    char buf[64] = "Hello";  // buffer con CAPACITÀ sufficiente
    const char *tail = " World!";
    
    //Verifica capacità prima di concatenare
    size_t l1 = strlen(buf);
    size_t l2 = strlen(tail);
    if (l1 + l2 + 1 > sizeof buf) {
        fprintf(stderr, "Buffer troppo piccolo (%zu > %zu)\n",
                l1 + l2 + 1, sizeof buf);
        return 1;
    }

    if (my_strcat(buf, tail) != 0) {
        fprintf(stderr, "Errore my_strcat\n");
        return 1;
    }
    //Output
    fprintf(stdout, "%s\n", buf); // Output
    return 0;
}
