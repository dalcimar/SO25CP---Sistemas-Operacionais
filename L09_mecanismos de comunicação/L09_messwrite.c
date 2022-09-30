//gcc -o L09_messwrite L09_messwrite.c -lrt 
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
	struct mq_attr attr; // atributos da fila de mensagens
	messbuf_t data; // as mensagens são do tipo messbuf_t
	messbuf_t *ptr = &data; // ponteiro para facilitar a vida
	
	attr.mq_maxmsg = 10; // capacidade para 10 mensagens
	attr.mq_msgsize = sizeof(messbuf_t); // tamanho de cada mensagem
	attr.mq_flags = 0;

	//mq_unlink("/myqueue");
	fd = mq_open("/myqueue", O_RDWR|O_CREAT, 0666, &attr); // abre ou cria a fila com permissoes 0666
	
	for(ever){
		ptr->v = rand()%1000;
		ptr->a = rand()/(double)RAND_MAX;
		
		mq_send(fd, (void*)ptr, sizeof(messbuf_t), 0); // envia a mensagem
		printf("Enviando mensagem %d %.2f\n", ptr->v, ptr->a);
		
		sleep(1);
	}
}
