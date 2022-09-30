#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define ever ;;

char prompt[100];

void execute(char **args){
	pid_t pid, status;

	pid = fork();
	if (pid==0) {
		execvp(*args, args); // há outras formas de passasr argumentos 
		perror(*args); // o numero de argumentos nao e conhecido
		exit(1); 
	} 

	waitpid(pid,NULL,0); // O progenitor executa a espera 
}

void parse(char *buf, char **args) {
	while(*buf != '\0'){ // strip whitespace
	
	while((*buf == ' ') || (*buf == '\t'))
		*buf++ = '\0';

	*args++ = buf; // salvaguarda argumento
	while((*buf != NULL) && (*buf != ' ') && (*buf != '\t')) // salta sobre o argumento
		buf++;
	}
	*args = NULL; // o ultimo argumento e NULL
}

int builtin(char *args[]){ // verifiicar se o comando é embutido no shell
	if(strcmp(args[0], "sair") == 0){
		exit(0);
	}

	if(strncmp(args[0], "42", 2) == 0){
		printf("42 is the answer to life the universe and everything\n");
		return(1); // indicar que o comando é embutido
	}

	return(0); // indicar que vamos continuar para a função execute
}

int main(){
	char buf[1024]; // um comando
	char *args[64]; // com um maximo de 64 argumentos

	printf("Joven Gafanhoto SHELL!\n");
	for(ever){
		
		printf("jgs:~$ ");
		scanf("%s", buf);

		parse(buf,args); // particiona a string em argumentos
		if(!builtin(args))
			execute(args); // executa o commando se não for uma funcionalidade embutida
	}

	exit(0);
}
