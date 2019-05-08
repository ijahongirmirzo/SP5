/*Program illustrating improper synchronization in Threaads */
/* Compile the program using the command on linux : $ gcc -pthread -o badcntn badcntn.c */
/* To execute the program enter: $ ./badcntn 10000 200  */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>



int pthread_create(pthread_t *thread, const pthread_attr_t *attr,  void *(*start_routine) (void *), void *arg);

void *thread(void *vargp); 
/* Global shared variable */
volatile long cnt = 0; /* Counter */

int main(int argc, char **argv)
{
    long niters; 
     int i, nthreads;
    pthread_t tid[1000];

    niters = atoi(argv[1]);
    nthreads = atoi(argv[2]);
    for (i=0; i < nthreads; i++)
    {
	pthread_create(&tid[i], NULL, thread, &niters);
	printf("THREAD %d with tid= %ld CREATED \n", i, tid[i]);
    }
    for (i=0; i < nthreads; i++)
    {
     	pthread_join(tid[i], NULL);
	printf("THREAD %d with tid= %ld TERMINATED \n", i, tid[i]);
    }

    /* Check result */
    if (cnt != (nthreads * niters))
        printf("BOOM! cnt=%ld  ---  RACE CONDITION\n", cnt);
    else
        printf("OK cnt=%ld\n", cnt);

    printf("PRESS CTRL-C to terminate or CTRL-Z to suspend \n");
     pause();
    exit(0);
}

/* Thread routine */
void *thread(void *vargp) 
{                                         
    long i, niters =  *((long *)vargp); 
                                            
    for (i = 0; i < niters; i++)
        cnt++;                   
                                             
    return NULL; 
} 

