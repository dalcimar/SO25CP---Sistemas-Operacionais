#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define ADDKEY 123
#define MSG "Mensagem escrita na memoria comum"
int main() {
   int shmid; // identificador da memoria comum
   int size = 1024;
   char *path="nome_de_arquivo_existente" ;
   char *mem;
   int flag = 0;
   
   // recuperacao do shmid
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
   // escrita na zona de memoria compartilhada
   strcpy(mem,MSG);
   exit(0);
}

