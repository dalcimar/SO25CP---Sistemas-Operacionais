/* shell.h bibliotecas de inclusao e prototipos. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

void parse(char *buf, char **args);
void execute(char **args);
int builtin (char **args);

/* constantes que podem tornar uteis*/
#define BG 0
#define FG 1
