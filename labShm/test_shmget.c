#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define ADDKEY 123
// OBS: SHM_R=0400 SHM_W=200 SHM_R AND SHM_W = 0600

int main() {
   int shmid ;  // identificador da memória comum
   int size = 1024 ;
   char *path="nome_de_arquivo_existente" ;
   
   key_t key = ftok(path,ADDKEY);
   shmid = shmget(key, size, IPC_CREAT|IPC_EXCL|SHM_R|SHM_W);   
   
   if (shmid == -1) {
   	perror("Erro no shmget") ;
   	exit(1) ;
   }
   
   printf("Identificador do segmento: %d \n",shmid) ;
   printf("Este segmento e associado a chave unica: %d\n", ftok(path,ADDKEY)) ;
   exit(0);
}

