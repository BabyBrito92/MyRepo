#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n;
int fibseq[1000];

void * fiboacci(void *arg);

void *fibonacci(void *arg)
{
	fibseq[0] = 0;
	fibseq[1] = 1;
	int i;
	for(i = 2; i < n; i++)
	{
		fibseq[i] = fibseq[i - 1] + fibseq[i - 2];
	}
	pthread_exit(0);
}

int main(int argc, char *argv[1])
{
	if(argc != 2)
	{
		printf("Please enter an argument\n");
		return -1;
	}

	int i;
	int pflag = 1;
	for(i = 0; i < strlen(argv[1]); i++)
	{
		pflag = isdigit(argv[1][i]);
		if(pflag == 0)
		{
			printf("Please enter a positive integer only\n");
			return-1;
		}
	}

	n = atoi(argv[1]);
	
	pthread_t tid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, fibonacci, NULL);
	pthread_join(tid, NULL);

	//Printing
	printf("The Sequence is: ");
	for(i = 0; i < n; i++)
	{
		printf("%d ", fibseq[i]);
	}
	printf("\n");
	return 0;
}
