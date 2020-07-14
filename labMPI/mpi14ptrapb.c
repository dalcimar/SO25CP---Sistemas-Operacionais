/* Parallel Trapezoidal Rule
 * 
 * Input: none
 * Output: Estimate of the integral from a to b of f(x)
 *   using the trapezoidal rule and n trapezoids.
 *
 * Algorithm:
 *  1.  Each process calcualtes "its" interval of integration
 *  2.  Each process estimates the integral of f(x) over its
 *      interval using the trapezoidal rule.
 *  3a. Each process != 0 sends its integral to 0.
 *  3b. Process 0 sums the calculations received from the
 *      individual processes and prints the result.
 *
 * Note:  f(x), a, b, and n are all hardwired.
 */

#include <stdio.h>
#include "mpi.h"

main(int argc, char ** argv) {
  int my_rank;              /* My process rank */
  int p;                    /* Number of processes */
  float a;                  /* Left endpoint */
  float b;                  /* Right endpoint */
  int n;                    /* Number of trapezoids */
  float h;                  /* Trapezoid base length */
  float local_a;            /* Left endpoint in my process */
  float local_b;            /* Right endpoint in my process */
  int local_n;              /* Number of trapezoids for my calc */
  float integral;           /* Integral over my interval */
  float total;              /* Total integral */
  int source;               /* Process sending integral */
  int dest = 0;             /* All messages go to 0 */
  int tag = 0;
  MPI_Status status;

  float Trap(float local_a, float local_b, int local_n, float h);
  void Get_data(float * a_ptr, float * b_ptr, int* n_ptr,
         int  my_rank, int  p);

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&p);

  Get_data(&a, &b, &n, my_rank, p);

  if (my_rank == 0) {
    printf("a = %f, b = %f, n = %d\n",a,b,n);
  }

  h = (b-a)/n;  /* h is the same for all processes */
  local_n = n/p; /* So is the number of trapezoids */

/* length of each process's interval of integration = local_n*h */
  local_a = a + my_rank*local_n*h;
  local_b = local_a + local_n*h;
  integral = Trap(local_a,local_b, local_n, h);

/* add up the integrals calculated by each process */
  if (my_rank == 0) {
    total = integral;
    for (source = 1; source < p; source++) {
      MPI_Recv(&integral, 1, MPI_FLOAT, source, tag, 
               MPI_COMM_WORLD, &status);
      total = total + integral;
    }
  } else {
    MPI_Send(&integral,1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
  }

/* print result */
  if (my_rank == 0) {
    printf("With n = %d trapezoids, our estimate\n",n);
    printf("of the integral from %f to %f = %f\n",a,b,total);
  }
  MPI_Finalize();
}

float Trap(float local_a, float local_b, int local_n, float h) {
  
  float integral;
  float x;
  int i;

  float f(float x);

  integral = (f(local_a) + f(local_b))/2.0;
  x = local_a;
  for (i=1; i<=local_n;i++) {
    x = x+h;
    integral = integral + f(x);
  }
  integral = integral*h;
  return integral;
}


float f(float x) {
  float return_val;

  return_val = x*x;
  return return_val;
}

/* Function Get_data
 * Reads in the user input a, b, and n.
 * Input parameters:
 *   1. int my_rank: rank of current process.
 *   2. int p: number of processes.
 * Output parameters:
 *   1. float * a_prt: pointer to left endpoint.
 *   2. float * b_prt: pointer to right endpoint.
 *   3. int * n_ptr: pointer to number of trapezoids.
 * Algorithm:
 *   1. Process 0 prompts user for input and reads the values.
 *   2. The input values are broadcast to all processes.
 */

void Get_data(
         float* a_ptr  /* out */,
         float* b_ptr  /* out */,
         int* n_ptr    /* out */,
         int  my_rank  /* in */,
         int  p        /* in */)
{
  int source = 0;   /* All local variables used by MPI_Send and MPI_Recv */
  int dest;
  int tag;
  MPI_Status status;

  if (my_rank == 0) {
    printf("Enter a, b and n\n");
    scanf("%f %f %d", a_ptr, b_ptr, n_ptr);
    printf("Inside:  a = %f, b = %f, n = %d\n",*a_ptr,*b_ptr,*n_ptr);
    }
  MPI_Bcast(a_ptr,1, MPI_FLOAT, 0, MPI_COMM_WORLD);
  MPI_Bcast(b_ptr,1, MPI_FLOAT, 0, MPI_COMM_WORLD);
  MPI_Bcast(n_ptr,1, MPI_INT, 0, MPI_COMM_WORLD);
}
