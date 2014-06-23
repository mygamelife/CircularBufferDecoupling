#include "CircularBufferDecoupling.h"
#include "malloc.h"
#include "Integer.h"
#include "Double.h"
#include "ErrorCode.h"
#include "CException.h"

/* void(*cpy)(void * , void *)
/* copy the typedata (double , int , char) into the buffer 
/* Integer.c (copyInt(void * , void*))
/* Double.c (copyDouble(void * , void*)))
/* char *headPtr = (char *)head;
/* headPtr[cb->sizeOfType * i];
*/

CircularBuffer *circularBufferNew(int length , int sizeOfType)
{
	CircularBuffer *cb = malloc(sizeof(CircularBuffer));
	cb->length = length;
	cb->size = 0;
	cb->sizeOfType = sizeOfType; 
	cb->head = cb->tail = cb->buffer = malloc(sizeOfType * length);
	return cb;
}

void circularBufferDel(CircularBuffer *cb)
{
	if(cb)
	{
		if(cb->buffer)
			free(cb->buffer);
	
		free(cb);
	}
}

void circularBufferAdd(CircularBuffer *cb , void *obj , void(*copy)(void * , void *))
{	
	char *headPtr = (char *)cb->head;
	
	if(circularBufferIsFull(cb))
		Throw(ERR_BUFFER_FULL);

	copy(headPtr , obj);
	cb->head++;
	cb->size++;
}

int circularBufferIsFull(CircularBuffer *cb)
{
	if(cb->size == cb->length)
		return 1;
		
	else return 0;
}