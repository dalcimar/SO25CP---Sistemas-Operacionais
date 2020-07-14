#include <stdio.h>
#include <string.h>
#include "mpi.h"

main(int argc, char * argv[])
{
  int my_rank;            /* rank of process */
  int p;                  /* number of processes */
  int source;             /* rank of sender */
  int dest;               /* rank of receiver */
  int tag = 0;            /* tag for messages */
  char message[100];      /* storage for message */
  MPI_Status status;      /* return status for receive */

/* Start up MPI */
  MPI_Init(&argc, &argv);

/* Find out process rank */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

/* Find out number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  /* create message */
  sprintf(message, "Greetings from process %d!\n",my_rank);
  dest = (my_rank + 1) % p;
  MPI_Send(message, strlen(message)+1,MPI_CHAR,
             dest, tag, MPI_COMM_WORLD);
  source = (my_rank -1) % p;
  MPI_Recv(message,100, MPI_CHAR, source, tag,
                  MPI_COMM_WORLD,&status);
  printf("PE %d received: %s\n",my_rank,message);

/* Shut down MPI */
  MPI_Finalize();
}
