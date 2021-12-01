#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;
void *routine(void *arg)
{
	sem_wait(&semaphore);
	sleep(1);
	printf("Hello thread: %d\n",*(int *)arg);
	sem_post(&semaphore);
	free(arg);
	return NULL;
}
int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("Syntax - <number> %s\n",argv[0]);
		exit(-1);
	}
	
	sem_init(&semaphore,0,1);
	int limit = atoll(argv[1]);
	pthread_t tid[limit];
	for(int i = 0 ; i < limit ; i++)
	{
		int*a = malloc(sizeof(*a));
		*a = i;
		pthread_create(&tid[i],0,routine,a);
	}

	for(int i = 0 ; i < limit ; i++)
		pthread_join(tid[i],NULL);

	sem_destroy(&semaphore);

}
