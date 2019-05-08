 
/* Program illustrating sharing of variables in Threaads */
/* Compile the program using the command on linux : $ gcc -pthread -o threadvshare threadvshare.c */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>



int pthread_create(pthread_t *thread, const pthread_attr_t *attr,  void *(*start_routine) (void *), void *arg);

void *thread(void *vargp); 
char **ptr;  /* global var */

int main()
{
    long i;
    pthread_t  tid[2];
    char *msgs[2] = {
        "Hello from foo",
        "Hello from bar"
    };

    ptr = msgs;
    for (i = 0; i < 2; i++)
    {
        pthread_create(&tid[i], NULL, thread, (void *)i);
        printf("Thread %d with tid = %d is created \n", i, tid[i]);
    }
    pthread_exit(NULL);
}


void *thread(void *vargp)
{
    long myid = (long)vargp;
    static int cnt = 0;
    printf("Now in thread %ld function \n", myid);
    printf("[%ld]:  %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
    return NULL;
}
