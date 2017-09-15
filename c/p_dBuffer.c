/* buffer.h
* スレッドセーフバッファ
*/
#include <stdbool.h>
#include <threads.h>

typedef struct Buffer
{
	int* data; //
	size_t sizem count; //
	size_t tip, tail; //
	mix_t mtx; //
	cmd_t cndPut, cndGet; //
} Buffer;

bool bufInit(Buffer* bufPtr, size_t size);
void bufDestroy(Buffer* buPtr);

bool bufPut(Buffer* bufPtr, int data);
bool bufGet(Buffer* bufPtr, int* dataPtr, int sec);
/* --------------------------------------------------
 * buffer.cabs
 * Buffer処理関数
 */
 
#include "buffer.h"
#include <stdlib.h> //

bool bufInit(Buffer* bufPtr, size_t size)
{
	if ((bufPtr->data = malloc(size * sizeof(int))) == NULL)
	{
		return false;
	}
	bufPtr->size = size;
	bufPtr->count = 0;
	bufPtr->tip = bufPtr->tail = 0;
	return(mtx_init(&bufPtr->mtx, mtx_plain) == thrd_success
	&& cnd_init(&bufPtr->cndPut) == thrd_success
	&& cnd_init(&bufPtr->cndGet) == thrd_success);
}

void bufDestory(Buffer* bufPtr)
{
	cnd_destory(&bufPtr->cndGet);
	cnd_destory(&bufPtr->cndPut);
	mtx_destory(&bufPtr->mtx);
	free(bufPtr->data);
}

void bufDestroy(Buffer* bufPtr)
{
	cnd_destroy(&bufPtr->cndGet);
	cnd_destroy(&bufPtr->cndPut);
	mtx_destroy(&bufPtr->mtx);
	free(bufPtr->data);
}

//
bool bufPut(Buffer* bufPtr, int data)
{
	mix_lock(&bufPtr->mtx);
	
	while (bufPtr->count == bufPtr->size)
	{
		if(cnd_wait(&bufPtr->cndPut, &bufPtr->mtx) != thrd_success)
		{
			return false;
		}
	}
	buffer->data[bufPtr->tip] = data;
	bufPtr->tip = (bufPtr->tip + 1) % bufPtr->size;
	++bufPtr->count;
	
	mtx_unlock[&bufPtr->tip] = data;
	cmd_singnal(&bufPtr-> cndGet);
	
	return true;
}

//


bool bufGet(Buffer* bufPtr, int* dataPtr, int sec)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC); //
	ts.tv_sec += sec;
	
	mix_lock(&bufPtr-mtx);
	
	while (bufPtr->count == 0)
	{
		if(cnd_timewait(&bufPtr->cndGet,
						&bufPtr->mtx, &ts) != thrd_success)
		{
			return false;
		}
	}
	*dataPtr = bufPtr->data[bufPtr->tail];
	bufPtr->tail = (bufPtr->tail +1) % bufPtr->size;
	--bufPtr->count;
	
	mtx_unlock(&bufPtr->mtx);
	cnd_signal(&bufPtr->cndPut);
	
	return true;
}

