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
#include <math.h>
#include "mpi.h"

main(int argc, char ** argv) {
  int my_rank;              /* My process rank */
  int p;                    /* Number of processes */
  double a = 0.0;           /* Left endpoint */
  double b = 1.0;           /* Right endpoint */
  int n = 16*1024*1024;             /* Number of trapezoids */
  double h;                 /* Trapezoid base length */
  double local_a;           /* Left endpoint in my process */
  double local_b;           /* Right endpoint in my process */
  int local_n;              /* Number of trapezoids for my calc */
  double integral;          /* Integral over my interval */
  double total;             /* Total integral */
  int source;               /* Process sending integral */
  int dest = 0;             /* All messages go to 0 */
  int tag = 0;
  double t0,t1;
  MPI_Status status;

  double Trap(double local_a, double local_b, int local_n, double h);

  MPI_Init(&argc, &argv);


  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

/* Begin timing */
  MPI_Barrier(MPI_COMM_WORLD);
  if (my_rank == 0) {
     t0 = MPI_Wtime();
  }

  MPI_Comm_size(MPI_COMM_WORLD,&p);

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
      MPI_Recv(&integral, 1, MPI_DOUBLE, source, tag, 
               MPI_COMM_WORLD, &status);
      total = total + integral;
    }
  } else {
    MPI_Send(&integral,1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }

/* End timing */
  MPI_Barrier(MPI_COMM_WORLD);
  if (my_rank == 0) {
     t1 = MPI_Wtime();
     printf("time for integral = %f\n",t1-t0);
  }

/* print result */
  if (my_rank == 0) {
    printf("With n = %d trapezoids, our estimate\n",n);
    printf("of the integral from %f to %f = %f\n",a,b,total);
  }
  MPI_Finalize();
}

double Trap(double local_a, double local_b, int local_n, double h) {
  
  double integral;
  double x;
  int i;

  double f(double x);

  integral = (f(local_a) + f(local_b))/2.0;
  x = local_a;
  for (i=1; i<=local_n;i++) {
    x = x+h;
    integral = integral + f(x);
  }
  integral = integral*h;
  return integral;
}


double f(double x) {
  double return_val;

  return_val = exp(-x*x);
  return return_val;
}
