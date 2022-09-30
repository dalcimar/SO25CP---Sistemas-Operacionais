//gcc -o L09_messread L09_messread.c -lrt 
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <unistd.h>

#define ever ;;

typedef struct messbuf{
	int v;
	float a;
}messbuf_t;

int main(){
	mqd_t fd; // descritor da fila de mensagens
	messbuf_t data; // as mensagens são do tipo messbuf_t
	messbuf_t *ptr = &data; // ponteiro para facilitar a vida

	fd = mq_open("/myqueue", O_RDWR); // abre ou cria a fila com permissoes 0666
	
	for(ever){
		mq_receive(fd, (void*)ptr, sizeof(messbuf_t), 0); // recebe cada mensagem e armazena em uma variável do tipo messguf_t
		printf("%d %.2f\n",ptr->v,ptr->a); // imprime seu conteudo
		//sleep(1);
	}
}
