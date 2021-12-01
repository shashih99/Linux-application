#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUMBER_OF_LOOPS 20000
long long sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *counting_thread(void *arg)
{
	int *offset_ptr = (int *)arg;
	int offset = *offset_ptr;

	pthread_mutex_lock(&mutex);
	for(int i = 0 ; i <= NUMBER_OF_LOOPS ; i++ )
		sum += offset;

	pthread_mutex_unlock(&mutex);
	return NULL;
}
int main()
{
	
	pthread_t tid1;
	int offset1=1;
	pthread_create(&tid1,0,counting_thread,&offset1);

	pthread_t tid2;
	int offset2=-1;
	pthread_create(&tid2,0,counting_thread,&offset2);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("Sum = %lld\n",sum);
	return 0;
}
