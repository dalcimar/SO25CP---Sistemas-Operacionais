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
  char smessage[100];     /* storage for message */
  char dmessage[100];     /* storage for message */
  MPI_Status status;      /* return status for receive */

/* Start up MPI */
  MPI_Init(&argc, &argv);

/* Find out process rank */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

/* Find out number of processes */
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  /* create message */
  sprintf(smessage, "Greetings from process %d!\n",my_rank);
  dest = (my_rank + 1) % p;
  source = (my_rank -1) % p;
  if (my_rank % 2 == 0) {
    MPI_Send(smessage, strlen(smessage)+1,MPI_CHAR,
               dest, tag, MPI_COMM_WORLD);
    MPI_Recv(dmessage,100, MPI_CHAR, source, tag,
                    MPI_COMM_WORLD,&status);
  } else {
    MPI_Recv(dmessage,100, MPI_CHAR, source, tag,
                    MPI_COMM_WORLD,&status);
    MPI_Send(smessage, strlen(smessage)+1,MPI_CHAR,
               dest, tag, MPI_COMM_WORLD);
  }
  printf("PE %d received: %s\n",my_rank,dmessage);

/* Shut down MPI */
  MPI_Finalize();
}
