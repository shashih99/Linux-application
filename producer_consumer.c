#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define THREAD_NUM 3
int buffer[10];
int count = 0;

pthread_mutex_t mutex_buffer;
sem_t semEmpty;
sem_t semFull;
void *producer(void *arg)
{
	int x;
	while(1)
	{
		//producer
		x = rand() % 100;
		sleep(1);
		sem_wait(&semEmpty);
		pthread_mutex_lock(&mutex_buffer);
		//add to buffer 
		//if(count < 10)
		{
			printf("Produced %d\n",x);
			buffer[count] = x;
			count++;
		}
		//else
		//	printf("Skipped %d\n",x);
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&semFull);
	}
}

void *consumer(void *arg)
{
	
	while(1)
	{
		int y = -1;
		sem_wait(&semFull);
		pthread_mutex_lock(&mutex_buffer);
		//if(count > 0)
		{
			//remove from the buffer
			y = buffer[count - 1];
			count--;
		}
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&semEmpty);
		//consumer
		printf("Consumer consumed %d\n",y);
		sleep(1);
	}
}
int main(int argc,char *argv[])
{
	srand(time(NULL));
	pthread_t tids[2];

	pthread_mutex_init(&mutex_buffer,NULL);
	sem_init(&semEmpty,0,10);
	sem_init(&semFull,0,0);
	for(int i = 0 ; i < THREAD_NUM; i++)
	{
		/*if(i > 0)*/if(i % 2 == 0)
		{
			if(pthread_create(&tids[i],NULL,producer,NULL) != 0)
			{	
				perror("Failed to create the thread");
			}
		}
		else
		{
			if(pthread_create(&tids[i],NULL,consumer,NULL) != 0)
                        {
                                perror("Failed to create the thread");
                        }
		}
	}

	for(int i = 0 ; i < THREAD_NUM; i++)
	{
		if(pthread_join(tids[i],NULL)!=0)
		{
			perror("Failed to join thread");
		}
	}

	pthread_mutex_destroy(&mutex_buffer);
	sem_destroy(&semEmpty);
	sem_destroy(&semEmpty);
	return 0;
}
