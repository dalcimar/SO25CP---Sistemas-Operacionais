#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
// Neste exemplo, supõe-se que o segmento de memória compartilhada tem a chave de acesso 123 utilizada no Exemplo 1.

#define ADDKEY 123

struct shmid_ds buf;

int main() {
   char *path="./testshmget.c" ;
   int shmid ;
   int size = 1024 ;
   
   // recuperação do identificador do segmento associado à chave 123
   shmid = shmget(ftok(path,(key_t)ADDKEY),size,0);
   if (shmid == -1 ){
   	perror ("Erro shmget()");
   	exit(1); 
   }
   
   // recuperação das informações relativas ao segmento
   int b = shmctl(shmid,IPC_STAT,&buf)
   if (b == -1){ 
      perror("Erro shmctl()");
      exit(1);
   }
   printf("ESTADO DO SEGMENTO DE MEMORIA COMPARTILHADA %d\n",shmid) ;
   printf("ID do usuario proprietario: %d\n",buf.shm_perm.uid) ;
   printf("ID do grupo do proprietario: %d\n",buf.shm_perm.gid) ;
   printf("ID do usuario criador: %d\n",buf.shm_perm.cuid) ;
   printf("ID do grupo criador: %d\n",buf.shm_perm.cgid) ;
   printf("Modo de acesso: %d\n",buf.shm_perm.mode) ;
   printf("Tamanho da zona de memoria: %d\n",buf.shm_segsz) ;
   printf("pid do criador: %d\n",buf.shm_cpid) ;
   printf("pid (ultima operacao): %d\n",buf.shm_lpid) ;
   
   // destruicao do segmento
   b = shmctl(shmid, IPC_RMID, NULL)
   if (b == -1){ 
      perror("Erro shmctl()");
   	exit(1); 
   }
   exit(0);
}

