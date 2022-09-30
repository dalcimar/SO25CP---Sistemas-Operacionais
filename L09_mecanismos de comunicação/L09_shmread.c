//gcc -o L09_shmread L09_shmread.c -lrt 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define ever ;;

typedef struct shmbuf{
	int v;
}shmbuf_t;

int main(){
	int fd;
	shmbuf_t *ptr;
	
	fd = shm_open("/sharedmem", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR); // Passos 1 a 3: abre/cria uma area de memoria compartilhada
	
	ftruncate(fd, sizeof(shmbuf_t)); // ajusta o tamanho da area compartilhada para sizeof (value)
	
	ptr = mmap(NULL, sizeof(shmbuf_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0); // Passos 4 a 6: mapeia a area no espaco de enderecamento deste processo
	
	for(ever){
		printf ("Read value %i\n", ptr->v); // le da area
		sleep(1) ;
	}
}
