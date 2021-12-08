#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

/*when there is condition fuel less than 40 */
#define THREAD_NUMBER 6
int fuel = 0;

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
void *fuelling(void *arg)
{
	for(int i = 0 ; i < 5 ; i++)
	{
		pthread_mutex_lock(&mutexFuel);
		fuel += 60;
		printf("Filling the fuel %d\n",fuel);
		pthread_mutex_unlock(&mutexFuel);
		//pthread_cond_signal(&condFuel);//instead of this we can use the broadcast so whichever waiting get the fuel
		pthread_cond_broadcast(&condFuel);
		sleep(1);
	}
	return NULL;
}

void *car(void *arg)
{
	pthread_mutex_lock(&mutexFuel);
#if 0
	if(fuel >= 40)
	{
        	fuel -= 40;
		printf("Got fuel %d\n",fuel);
	}
	else
		printf("No fuel\n");
#endif
	//no fuel we can have condition
	while(fuel < 40)
	{
		printf("No fuel\n");
		//sleep(1); //we can call pthread condition wait
		pthread_cond_wait(&condFuel,&mutexFuel);
		//Equivalent to:
		//pthread_mutex_unlock(&mutexFuel);
		//wait for condFuel signal
		//pthread_mutex_lock(&mutexFuel);
	}
	fuel -= 40;
        printf("Got fuel %d\n",fuel);
        pthread_mutex_unlock(&mutexFuel);
	return NULL;
}
int main()
{
	pthread_t tids[THREAD_NUMBER];

	pthread_mutex_init(&mutexFuel,NULL);
	pthread_cond_init(&condFuel,NULL);
	for(int i = 0 ; i < THREAD_NUMBER ; i++)
	{
		if(i == 4 || i == 5)
		{
			if(pthread_create(&tids[i],NULL,fuelling,NULL) != 0)
				perror("Failing to create the thread");
		}
		else
		{
			if(pthread_create(&tids[i],NULL,car,NULL) != 0)
                                perror("Failing to create the thread");
		}
	}

	for(int i = 0 ; i < THREAD_NUMBER ; i++)
	{
		if(pthread_join(tids[i],NULL) != 0)
			perror("Failing to join the thread");
	}

	pthread_mutex_destroy(&mutexFuel);
	pthread_cond_destroy(&condFuel);
	return 0;
}
