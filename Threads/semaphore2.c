// Vishwas Karki 
// Mini-Project 3

#include <stdio.h>
#include <pthread.h>

#define max 6000            // numbers to produce
#define num_of_threads 4    // numbers of threads

int array[6000];            // array of size 6000
long sum = 0;               // add=0; 
 

pthread_mutex_t the_mutex ; 
pthread_cond_t condc; 
 

void *consumer(void * ptr)
{ 
    int i;
    int index = (int)ptr; 
    
   printf("id %d \n", ptr);         // prints the id of the thread.
    
     
   for(int k = ((index - 1) * 1500); k < ((index) * 1500); k++)        
    {
        pthread_mutex_lock(&the_mutex);
        sum = sum + array[k];
        pthread_mutex_unlock(&the_mutex);
    }
    
    printf("sum == %d \n ", sum);    // prints the local sum of the thread
    
    pthread_exit(0);
}


//                  Main program                // 
int main(int argc, char **argv)
{
    pthread_t con, threads[num_of_threads];
    int status , i = 0 ;

    
    for(int j = 0; j < 6000; j++)
    {
    array[j] = j + 1; 
    }   


    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    // creating multiple threads
    for(i = 1; i <= num_of_threads; i++)
    {
    pthread_create(&threads[i], NULL, consumer, (void*)i);
    pthread_join(threads[i], NULL);
    }
    pthread_cond_destroy(&condc);
    pthread_mutex_destroy(&the_mutex);

    printf("\nThe total summation of 6000 numbers is %d \n", sum);

}
