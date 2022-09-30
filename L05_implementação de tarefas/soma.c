#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int a=1;
	int b=2;
	
	int soma = a+b;
	
	printf("O resultado é: %d\n", soma);
	
	exit(0);
}
