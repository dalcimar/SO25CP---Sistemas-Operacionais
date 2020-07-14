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
  char imessage[100];     /* storage for input message */
  char omessage[100];     /* storage for input message */
  MPI_Status status;      /* return status for receive */

/* Start up MPI */
  MPI_Init(&argc, &argv);

/* Find out process rank */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

/* Find out number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  /* create message */
  sprintf(omessage, "Greetings from process %d!\n",my_rank);
  dest = (my_rank + 1) % p;
  source = (my_rank -1) % p;
  MPI_Sendrecv(omessage,strlen(omessage)+1,MPI_CHAR,dest,tag,
               imessage,100,MPI_CHAR,source,tag,MPI_COMM_WORLD,&status);
  printf("PE %d received: %s\n",my_rank,imessage);

/* Shut down MPI */
  MPI_Finalize();
}
