#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *sum_runner(void *arg)
{
	long long *limit_ptr = (long long *)arg;
	long long limit = *limit_ptr;
	free(arg);

	long long sum = 0;
	for(long long i = 0 ; i < limit ; i++)
		sum += i;

	long long *answer = malloc(sizeof(*answer));
	*answer = sum;
	pthread_exit(answer);	
}
int main(int argc,char *argv[])
{
	
	if(argc < 2)
	{
		printf("Syntax: Usage <number> %s\n",argv[0]);
		exit(-1);
	}

	long long *limit = malloc(sizeof(*limit));
	*limit = atoll(argv[1]);

	pthread_t tid;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,sum_runner,limit);

	long long *result;
	pthread_join(tid,(void **)&result);
	printf("Sum is %lld\n",*result);
	free(result);

}
