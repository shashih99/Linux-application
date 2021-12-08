#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define THREAD_NUMBER 8

//the queue without conditional variable can use lot of CPU resource so we need to use the this

typedef struct task
{
	int a,b;
}Task;

Task taskQueue[256];
int taskCount=0;

pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;
void executedTask(Task *task)
{
	usleep(50000);
	int result = task->a + task->b;
	printf("The sum of %d and %d is %d\n",task->a,task->b,result);
}

void submitTask(Task task)
{
	pthread_mutex_lock(&mutexQueue);
	taskQueue[taskCount] = task;
	taskCount++;
	pthread_mutex_unlock(&mutexQueue);
	pthread_cond_signal(&condQueue);
}
void *start_thread(void *arg)
{
	while(1)
	{
		Task task;
		//int found = 0;
		pthread_mutex_lock(&mutexQueue);

		while(taskCount == 0)
		{
			pthread_cond_wait(&condQueue,&mutexQueue);
		}
		//if(taskCount > 0)
		{
		//	found = 1;
			task = taskQueue[0];

			for(int i = 0 ; i < taskCount - 1; i++)
			{
				taskQueue[i] = taskQueue[i+1];
			}
			taskCount--;
		}
		pthread_mutex_unlock(&mutexQueue);
		//if(found)
			executedTask(&task);
	} 
}
int main()
{
	pthread_t tids[THREAD_NUMBER];

	pthread_mutex_init(&mutexQueue,NULL);
	pthread_cond_init(&condQueue,NULL);
	for(int i = 0 ; i < THREAD_NUMBER ;i++)
	{
		if(pthread_create(&tids[i],NULL,start_thread,0) != 0)
			perror("Failed to create the thread");
	}
	srand(time(NULL));
	for(int i = 0 ; i < 100 ; i++)
	{
		Task t = {.a = rand() % 100,.b = rand() % 100};
		submitTask(t);
	}
	for(int i = 0 ; i < THREAD_NUMBER; i++)
	{
		if(pthread_join(tids[i],NULL) != 0)
			perror("Failed to join the thread");
	}

	pthread_mutex_destroy(&mutexQueue);
	pthread_cond_destroy(&condQueue);
	return 0;
}
