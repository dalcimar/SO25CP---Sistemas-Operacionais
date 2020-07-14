#include "shell.h"
/* parse.c particiona o comando Unix (armazenado em buf) em argumentos */
void parse (char *buf, char **args) {
    while (*buf != '\0'){
        /* strip whitespace. Usa um NULL para indicar que o argumento anterior e o ultimo */
        while ((*buf == ' ') || (*buf == '\t'))
            *buf++ = '\0';
        
        *args++ = buf; /* salvaguarda argumento */
        while ((*buf != NULL) && (*buf != ' ') && (*buf != '\t')) /* salta sobre o argumento*/
            buf++;
    }
    *args = NULL; /* o ultimo argumento e NULL */
}
