/**
 * A pthread program illustrating deadlock.
 *
 * Usage
 *	gcc deadlock.c -lpthread
 *	./a.out
 *
 * Figure 7.1
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Seventh Edition
 * Copyright John Wiley & Sons - 2005.
 */

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t first_mutex;
pthread_mutex_t second_mutex;

void *do_work_one(void *param); 
void *do_work_two(void *param); 

int main(int argc, char *argv[])
{
pthread_t tid1, tid2; /* the thread identifiers */
pthread_attr_t attr; /* set of attributes for the thread */

/* get the default attributes */
pthread_attr_init(&attr);

/* create the mutex locks */
pthread_mutex_init(&first_mutex,NULL);
pthread_mutex_init(&second_mutex,NULL);

/* create the threads */
pthread_create(&tid1,&attr,do_work_one,NULL);
pthread_create(&tid2,&attr,do_work_two,NULL);

/* now wait for the thread to exit */
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);

printf("Parent DONE\n");

/* destroy the mutex before exiting */
pthread_mutex_destroy(&first_mutex);
pthread_mutex_destroy(&second_mutex);
}

void *do_work_one(void *param) 
{
	pthread_mutex_lock(&first_mutex);
	pthread_mutex_lock(&second_mutex);
	/**
	 * Do some work
	 */
	pthread_mutex_unlock(&second_mutex); 
	pthread_mutex_unlock(&first_mutex); 

	pthread_exit(0);
}

void *do_work_two(void *param)
{
        pthread_mutex_lock(&second_mutex);
        pthread_mutex_lock(&first_mutex);
        /**
         * Do some work
         *
         * We ensure deadlock by having this thread sleep before releasing the lock.
         */ 
         
	sleep(2000);
         
        pthread_mutex_unlock(&first_mutex);
        pthread_mutex_unlock(&second_mutex);

        pthread_exit(0);
}

