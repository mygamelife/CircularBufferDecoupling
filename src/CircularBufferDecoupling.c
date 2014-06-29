#include "CircularBufferDecoupling.h"
#include "malloc.h"
#include "Integer.h"
#include "Double.h"
#include "stdio.h"
#include "ErrorCode.h"
#include "CException.h"

/* Create a new buffer for integer/double type
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
	if(circularBufferIsFull(cb))
	{
		Throw(ERR_BUFFER_FULL);
	}
	
	copy(cb->head , obj);
	cb->size++;
	cb->head += cb->sizeOfType;	
	
	if(&cb->head == &cb->buffer+cb->size)
		cb->head = cb->buffer;
}

/*Remove integer/double data from buffer
 *After remove size will decrement one
 *cb->size element inside circular buffer
 *obj is element wanted to be remove
 *cb->tail will point to the next data that going to be remove
*/
void circularBufferRemove(CircularBuffer *cb , void *obj , void(*copy)(void * , void *))
{	
	if(circularBufferIsEmpty(cb))
		Throw(ERR_BUFFER_EMPTY);
		
	copy(cb->tail , obj);
	cb->size--;
	cb->tail += cb->sizeOfType;
	
	if(cb->tail == cb->buffer+(cb->sizeOfType * cb->length))
		cb->tail = cb->buffer;
}

int circularBufferIsFull(CircularBuffer *cb)
{
	if(cb->size >= cb->length)
		return 1;
		
	else return 0;
}

int circularBufferIsEmpty(CircularBuffer *cb)
{
	if(cb->size <= 0)
		return 1;
		
	else return 0;
}