#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

#define ever ;;

typedef struct pipebuf{
	int v;
	float a;
}pipebuf_t;

int main(){
	int fd;
	pipebuf_t data;
	pipebuf_t *ptr = &data;
	
	mkfifo("myfifo", 0666); // cria um pipe nomeado
  
  	fd = open("myfifo", O_WRONLY); // abre o pipe com permissão de escrita. bloqueante até que read seja aberto
	
	for(ever){
		ptr->v = rand()%1000;
		ptr->a = rand()/(double)RAND_MAX;

		printf("Inserindo no pipe %d %.2f\n", ptr->v, ptr->a);
		write(fd, ptr, sizeof(pipebuf_t)); // escreve no pipe
		sleep(1);
	}
}
