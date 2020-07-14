#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define ADDKEY 123
int main() {
   int shmid ; // identificador da mem�ria comum
   int size = 1000 ;
   char *path="nome_de_arquivo_existente" ;
   char *mem ;
   int flag = 0 ;
   // recupera��o do shmid
   key_t key = ftok(path,ADDKEY);
   shmid = shmget(key, size,0);
   if (shmid == -1){
      perror("Erro no shmget");
      exit(1); 
   }
   printf("Sou o processo com pid: %d \n",getpid());
   printf("Identificador do segmento recuperado: %d \n",shmid);
   printf("Este segmento e associado a chave unica: %d\n",ftok(path,ADDKEY));
   
   // acoplamento do processo a zona de memoria
   mem = shmat(shmid, 0, flag);
   if (mem == (char*)-1){
      perror("acoplamento impossivel");
      exit(1);
   }
   
   // tratamento do conte�do do segmento
   printf("leitura do segmento de mem�ria compartilhada:\n");
   printf("\t==>%s\n",mem);
   exit(0);
}
