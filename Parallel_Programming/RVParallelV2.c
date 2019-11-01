/******************************************************
Student names: Ravishka Rathnasuriya, Vishwas Karki
Assignment 1: Using Scatter and Reduce
Professor: Dr. Eduardo Colmenares
Date : 10/21/2019

Description:
// This version of code is to compute the summation for the 
// computation of 640000 elements. The code uses Scatter and reduce
// to compute to summation for nth term. The code utilizes 
// function such as MPI_SCATTER AND MPI_REDUCE

How to run:
// i) Copy the script file and C file in WinScp. Then open Putty
//    and log in.
// ii) Compile the code in Putty.
// command: mpicc filename.c -o executablename
// iii) Submit the script file.
// command: sbatch <scriptfile name>
// iv) The result can be viewed in WinScp fileExplorer
// filename: myjob.o_<submission number>
//
************************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <mpi.h>
#include <stdlib.h>


// global variable defined
#define SIZE 640000
#define num_of_cores 64
#define local_size (SIZE/num_of_cores)
#define master 0

//=============================================================//
//                      Main Program                           // 
int main(){

//variables created to manipulate data
int comm_sz=0;
int my_rank=0; // rank of the process
long long global_sum =0; // stores the value of summation up to nth term 
long long local_sum=0, ret = 0;
double start, end;

// all the parallel program funcitons and process is 
// created inside MPI init
MPI_Init(NULL, NULL);
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
//declare two dynamically allocated arrays one to store
//640000 elemements and the other to number of elements per process
long *buf, *buff_ret;

//if in process 0, initialize the array for 640000 numbers
if(my_rank == 0)
{
buf = (long *)malloc(SIZE * sizeof(long));
//fill the array from 1 to 640000
for(int i = 0; i < SIZE; i++)
{    
buf[i] = i+1;
}
}

// if rank 0 check if communicator size is less than number of processes
if(my_rank == 0){
      if(comm_sz < num_of_cores){
printf("Required number of processors %d, available %d. Porgram ends ", num_of_cores,comm_sz);


//mpi scatter evenly distribute the number of elements per process to other processes
MPI_Scatter(buf,local_size, MPI_LONG_LONG,&buff_ret , local_size, MPI_LONG_LONG,0, MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD); //mpi_barrier

goto END;
}
printf("parallel summation of %d numbers \n", SIZE);
 start = MPI_Wtime(); //time starts 

//computing the local addition 
for(long r = 0; r < SIZE; r++)
{
local_sum += buf[r];
}

}

//mpi reduce will compute the global addition using MPI_SUM
MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG,MPI_SUM,master, MPI_COMM_WORLD);

 
//back again in process 0
if(my_rank == master){
//global_sum += ret ;
//time ends
end = MPI_Wtime();
printf("Summation: %lld\n", global_sum);
printf("Elapsed time: %f sec \n" , end-start);
}

END:
MPI_Finalize();  //finish all mpi tasks
return 0;
}