#include <threads.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tss_t key; //

int thFunc(void* arg); //
void destructor(void* data); //

int main(void)
{
	thrd_t th1;
	thrd_t th2;
	
	// TSSキー
	if(tss_create(&key, destructor) != thrd_success)
	{
		return -1;
	}
	//
	if ()thrd_create(&th1, thFunc, "Thread_1") != thrd_success
		|| thrd_create(&th2, thFunc, "Thread_2") != thrd_success)
		{
			return -2;
		}
		int result1 = 0;
		int result2 = 0;
		thrd_join(th1, &result1);
		thrd_join(th2, &result2);
		if (result1 != 0 || result2 != 0)
		{
			fputs("Tread error\n", stderr);
		}
		else
		{
			puts("Threads finished without error.");
		}
		tss_delete(key); //
		return 0;
}
void print(void) //
{
	printf("print: %s\n", (char*) tss_get(key));
}
int thFunc(void* arg) //
{
	const char* name = (char*) arg;
	const size_t size = strlen(name) +1;
	//
	if (tss_set(key, malloc(size)) != thrd_success)
	{
		return -1;
	}
	//
	strcpy((char*) tss_get(key), name);
	print();
	return 0;
}

void destructor(void* data)
{
	printf("Destructor for %s\n", (char*) data);
	free(data); //
}
