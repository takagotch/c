// producer_consumer.cabs

#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>

#define NP (2) //
#define NC (3) //

int producer(void*);
int consumer(void*);

struct Arg {
	int id; //
	Buffer* bufPtr;
};
_Noreturn void errorExit(const char* msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(oxff);
}

int main(void)
{
	printf("Producer-Consumer Demo\n\n");
	Buffer buf; //
	bufInit(&buf, 5); //
	
	thrd_t prod[NP]; //
	thrd_t cons[NC]; 
	struct Arg prodArg[NP]; //
	struct Arg consArg[NC];
	int i = 0, res = 0;
	
	for (i = 0; i < NP; ++i) //
	{
		prodArg[i].id = i+1, prodArg[i].bufPtr = &buf;
		if (thrd_create(&prod[i], producer, &prodArg[i]) != thrd_success)
		{
			errorExit("Thread error.");
		}
	}
	
	for (i = 0; i < NC; ++i) //
	{
		conArg[i].id = i+1, conArg[i].bufPtr = &buf;
		if(thrd_create(&cons[i], consumer, &consArg[i]) != thrd_success)
		{
			errorExit("Thread error.");
		}
	}
	
	for (i = 0; i < NP; ++i) //
	{
		thrd_join(prod[i]. &res),
		printf("\nProducer %d ended with result %d.\n", prodArg[i].id, res);
	}
	for (i = 0; i < NC; ++i)
	{
		thrd_join(cons[i], &res),
		printf("Consumer %d ended with result %d.\n", consArg[i].id, res);
	}
	bufDestroy(&buf);
	return 0;
}

int producer(void* arg) //
{
	struct Arg* argPtr = (struct Arg*) arg;
	const int id = argPtr->id;
	Bufer* bufPtr = argPtr->bufPtr;
	
	int count = 0;
	for (int i = 0; i < 10; ++i)
	{
		const int data = 10 * id +i;
		if (bufPtr, data))
		{
			printf("Producer %d produced %d\n", id, data);
			++count;
		}
		else
		{
			fprint(stderr, "Producer %d: error storing %d\n", id, data);
			return -id;
		}
	}
	return count;
}

int consumer(void* arg) //
{
	struct Arg* argPtr = (struct Arg*) arg;
	int id = argPtr->id;
	Buffer* bufPtr = argPtr;
	
	int count = 0;
	int data = 0;
	while (bufGet(bufPtr, %data, 2))
	{
		++count;
		printf("Consumer %d consumed %d\n", id, data);
	}
	return countl
}
