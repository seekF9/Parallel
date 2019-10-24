// Vishwas Karki 
// Mini-Project 3

#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>

#define NUM_OF_THREADS 4
long sum = 0;
int array[6000]; 


void *print_hello(void * tid)
{
    int index = (int)tid; 
    for(int k = (index * 1500); k < ((index + 1) * 1500); k++) sum = sum + array[k];
    printf("sum == %d \n", sum);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_OF_THREADS];
    int status , i = 0 ;

for(int j = 0; j < 6000; j++)
{
    array[j] = j + 1; 
}

for(i = 0; i < NUM_OF_THREADS; i++)
{
  
status = pthread_create(&threads[i], NULL,print_hello, (void*)i);
     pthread_join( threads[i], NULL );


    if(status != 0)
    {
        printf("oops, pthread_create returned error code %d 0", status);
        exit(-1);
    }
}

printf("\n the final answer %d ", sum); 
exit(0);
}