#include "shell.h"
/* main.c  cria um processo progénito e executa um programa */
char prompt[100];

int main(){
    char buf[1024]; /* um comando */
    char *args[64]; /* com um maximo de 64 argumentos */
    strcpy (prompt, "SOSHELL: Introduza um comando: prompt>"); /*prompt inicial*/
    while (1){
        printf("%s", prompt );
	scanf("%s",buf);

        parse(buf,args); /* particiona a string em argumentos */
        if (!builtin(args))
            execute(args); /* executa o commando se não for uma funcionalidade embutida */
    }
    
    return 0;
}

int builtin(char *args[]){ /* verifiicar se o comando é embutido no shell */
    if (strcmp (args[0], "sair") == 0){
        exit (0);
        return 1; /* funcionalidade embutida */
    }
    
    if (strncmp (args[0], "42", 2) == 0){
        printf("42 is the answer to life the universe and everything\n");
        return 1; /* funcionalidade embutida*/
    }
    
    return (0); /* indicar que vamos continuar para a função execute*/
}
