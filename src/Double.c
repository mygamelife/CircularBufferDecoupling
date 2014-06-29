#include "Double.h"
#include "stdio.h"

void copyDouble(void *dest , void *source)
{
	double *sourceDouble = (double *)source;
	double *headPtr = (double *)dest;
	
	*headPtr = *sourceDouble; 
}