#include <stdio.h>    // Include la libreria standard di I/O (printf, ecc.)
#include <stdlib.h>   // Include funzioni di gestione memoria dinamica (malloc, free)

/* Cambia il puntatore del chiamante a un nuovo buffer s3 = s1 + s2 */
int my_strcat_repoint(char *restrict *ps1, const char *restrict s2) { // Funzione che riceve: indirizzo del puntatore s1 (char **)
                                                             // e un puntatore costante a char s2 (sorgente da concatenare).
                                                             // 'restrict' suggerisce al compilatore che ps1 e s2 non aliasano memorie sovrapposte.

    if (!ps1 || !s2) return -1;        // Controllo parametri: fallisce se l'indirizzo del puntatore o s2 sono NULL.

    // 1) Calcolo tsize manualmente (tuo metodo)
    size_t tsize = 0;                   // tsize conterrà la dimensione totale necessaria (s1 + s2 + '\0').
    const char *p = (*ps1) ? *ps1 : ""; // p scorre i caratteri di s1; se *ps1 è NULL, trattiamo s1 come stringa vuota "".
    while (*p != '\0') { tsize++; p++; } // Conta i caratteri di s1: incrementa tsize finché non incontra il terminatore '\0'.
    p = s2;                              // Riusa p per scorrere s2 dall'inizio.
    while (*p != '\0') { tsize++; p++; } // Conta i caratteri di s2 e li somma a tsize.
    tsize++;                             // Spazio per il terminatore finale '\0' della stringa concatenata.

    // 2) Creo il terzo "array" s3 (buffer dinamico)
    char *s3 = (char *)malloc(tsize);   // Alloca un nuovo buffer di tsize byte sull'heap per contenere s1 + s2 + '\0'.
    if (!s3) return -1;                 // Se malloc fallisce (ritorna NULL), segnala errore.

    // 3) Copia manuale s1 -> s3
    char *d = s3;                       // d è il cursore di scrittura dentro s3 (destinazione).
    p = (*ps1) ? *ps1 : "";             // p torna a puntare all'inizio di s1 (o "" se *ps1 è NULL).
    while (*p != '\0') { *d++ = *p++; } // Copia ogni char di s1 in s3, avanzando entrambi i cursori, fino al '\0' (escluso).

    // 4) Copia manuale s2 -> s3 (in coda)
    p = s2;                             // p ora scorrerà s2 dall'inizio.
    while (*p != '\0') { *d++ = *p++; } // Appende i caratteri di s2 in coda a s3, avanzando d e p.

    // 5) Terminatore
    *d = '\0';                          // Scrive il terminatore di stringa alla fine del buffer s3.

    // 6) Libero il vecchio buffer (se esistente) e RIASSEGNO il puntatore del chiamante
    free(*ps1);                         // Libera la memoria precedentemente puntata da *ps1.
                                        // ATTENZIONE: questo è sicuro solo se *ps1 proveniva da malloc/realloc/calloc
                                        // (nel main di esempio *ps1 è NULL alla prima chiamata, quindi free(NULL) è OK).
    *ps1 = s3;                          // Aggiorna il puntatore del chiamante: ora s1 punterà al nuovo buffer s3.
    return 0;                           // Ritorna 0 per indicare successo.
}

int main(void) {                        // Entry point del programma; non riceve argomenti.
    char *s1 = NULL;                    // s1 non punta ancora a nessuna memoria valida (stringa vuota “logica”).
    my_strcat_repoint(&s1, "Hello");    // Prima concatenazione: alloca s3 di dimensione 6 ("Hello\0"), s1 -> "Hello".
    my_strcat_repoint(&s1, " World!");  // Seconda concatenazione: alloca un nuovo s3 più grande e copia "Hello" + " World!".
    printf("%s\n", s1);                 // Stampa la stringa risultante: "Hello World!".
    free(s1);                           // Rilascia l’ultimo buffer allocato per evitare memory leak.
    return 0;                           // Termina il programma con codice di uscita 0 (successo).
}
