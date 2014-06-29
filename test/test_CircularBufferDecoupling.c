#include "unity.h"
#include "CircularBufferDecoupling.h"
#include "Integer.h"
#include "Double.h"
#include "ErrorCode.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_circularBufferNew_should_create_new_CircularBuffer_object_of_integer_type(void)
{
	CircularBuffer *cb = circularBufferNew( 7 , sizeof(int) );
	
	TEST_ASSERT_NOT_NULL(cb->head);
	TEST_ASSERT_NOT_NULL(cb->tail);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(4 , cb->sizeOfType);
	TEST_ASSERT_EQUAL(0 , cb->size);
	TEST_ASSERT_EQUAL(7 , cb->length);
	
	circularBufferDel(cb);
}

void test_circularBufferNew_should_create_new_CircularBuffer_object_of_double_type(void)
{
	CircularBuffer *cb = circularBufferNew( 13 , sizeof(double) );
	
	TEST_ASSERT_NOT_NULL(cb->head);
	TEST_ASSERT_NOT_NULL(cb->tail);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(8 , cb->sizeOfType);
	TEST_ASSERT_EQUAL(0 , cb->size);
	TEST_ASSERT_EQUAL(13 , cb->length);
	
	circularBufferDel(cb);
}

void test_circularBufferAddInt_given_10_21_should_add_10_21_into_buffer(void)
{
	CircularBuffer *cb = circularBufferNew( 4 , sizeof(int) );
	
	int integer1 = 10;
	int integer2 = 21;
	int integer3 = 25;
	int integer4 = 26;
	int *headPtr = (int *)cb->head;

	circularBufferAdd(cb , &integer1 , copyInt);
	circularBufferAdd(cb , &integer2 , copyInt);
	circularBufferAdd(cb , &integer3 , copyInt);
	circularBufferAdd(cb , &integer4 , copyInt);
	
	TEST_ASSERT_EQUAL(10 , headPtr[0]);
	TEST_ASSERT_EQUAL(21 , headPtr[1]);
	TEST_ASSERT_EQUAL(25 , headPtr[2]);
	TEST_ASSERT_EQUAL(26 , headPtr[3]);
	TEST_ASSERT_EQUAL(&headPtr[4] , cb->head); //cb->head now is pointing to next location
	TEST_ASSERT_EQUAL(cb->buffer , cb->tail); //cb->tail remain at the 1st location
	TEST_ASSERT_EQUAL(4 , cb->size);
		
	circularBufferDel(cb);
}

void test_circularBufferIsFull_given_32_33_34_35_36_should_add_32_33_34_35_and_throw_exception(void)
{
	CircularBuffer *cb = circularBufferNew( 4 , sizeof(int) );
	
	int integer1 = 32;
	int integer2 = 33;
	int integer3 = 34;
	int integer4 = 35;
	int integer5 = 36;
	int *headPtr = (int *)cb->head;
	int *bufferPtr = (int *)cb->buffer;
	CEXCEPTION_T err;
	
	Try
	{
		circularBufferAdd(cb , &integer1 , copyInt);
		circularBufferAdd(cb , &integer2 , copyInt);
		circularBufferAdd(cb , &integer3 , copyInt);
		circularBufferAdd(cb , &integer4 , copyInt);
		circularBufferAdd(cb , &integer5 , copyInt);
	
		TEST_ASSERT_EQUAL(32 , headPtr[0]);
		TEST_ASSERT_EQUAL(33 , headPtr[1]);
		TEST_ASSERT_EQUAL(34 , headPtr[2]);
		TEST_ASSERT_EQUAL(35 , headPtr[3]);
		TEST_FAIL_MESSAGE("Should throw ERROR_BUFFER_FULL exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_BUFFER_FULL , err , "Expect ERROR_BUFFER_FULL exception");
		TEST_ASSERT_EQUAL(4 , cb->size);
		TEST_ASSERT_EQUAL(&bufferPtr[0] , headPtr);
	}
	
	circularBufferDel(cb);
}

void test_circularBufferRemoveInt_given_4_and_6_should_remove_4_and_6(void)
{
	CircularBuffer *cb = circularBufferNew( 5 , sizeof(int) );
	
	int integer1 = 4;
	int integer2 = 6;
	int *headPtr = (int *)cb->head;
	int *tailPtr = (int *)cb->tail;

	circularBufferAdd(cb , &integer1 , copyInt);
	circularBufferAdd(cb , &integer2 , copyInt);
	
	circularBufferRemove(cb , &integer1 , copyInt);
	circularBufferRemove(cb , &integer2 , copyInt);
	
	TEST_ASSERT_EQUAL(4 , tailPtr[0]);
	TEST_ASSERT_EQUAL(6 , tailPtr[1]);
		
	circularBufferDel(cb);
}

void test_circularBufferRemoveInt_given_40_41_42_and_remove_4times_should_throw_exception(void)
{
	CircularBuffer *cb = circularBufferNew( 3 , sizeof(int) );
	
	int integer1 = 40;
	int integer2 = 41;
	int integer3 = 42;
	int *headPtr = (int *)cb->head;
	int *tailPtr = (int *)cb->tail;
	int *bufferPtr = (int *)cb->buffer;
	CEXCEPTION_T err;

	
	Try
	{
		circularBufferAdd(cb , &integer1 , copyInt);
		circularBufferAdd(cb , &integer2 , copyInt);
		circularBufferAdd(cb , &integer3 , copyInt);
		
		circularBufferRemove(cb , &integer1 , copyInt);
		circularBufferRemove(cb , &integer2 , copyInt);
		circularBufferRemove(cb , &integer3 , copyInt);
		circularBufferRemove(cb , &integer3 , copyInt);
		TEST_FAIL_MESSAGE("Should throw ERROR_BUFFER_EMPTY exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_BUFFER_EMPTY , err , "Expect ERROR_BUFFER_EMPTY exception");
		TEST_ASSERT_EQUAL(0 , cb->size);
		TEST_ASSERT_EQUAL(cb->buffer , cb->tail);
	}
	
	circularBufferDel(cb);
}

void test_circularBufferAddDouble_given_5_dot_65_n_7_dot_21_should_5_dot_65_n_7_dot_21_buffer(void)
{
	CircularBuffer *cb = circularBufferNew( 13 , sizeof(double) );
	
	double integer1 = 5.65;
	double integer2 = 7.21;
	double *headPtr = (double *)cb->head;
 
	circularBufferAdd(cb , &integer1 , copyDouble);
	circularBufferAdd(cb , &integer2 , copyDouble);
	
	TEST_ASSERT_EQUAL_FLOAT(5.65 , headPtr[0]);
	TEST_ASSERT_EQUAL_FLOAT(7.21 , headPtr[1]);
	 	
	circularBufferDel(cb);
}

void test_circularBufferIsFull_given_3dot2_4dot3_5dot4_6dot5_7dot6_8dot6_should_add_3dot2_4dot3_5dot4_6dot5_7dot6_8dot6_and_throw_exception(void)
{
	CircularBuffer *cb = circularBufferNew( 5 , sizeof(double) );
	
	double integer1 = 3.2;
	double integer2 = 4.3;
	double integer3 = 5.4;
	double integer4 = 6.5;
	double integer5 = 7.6;
	double integer6 = 8.6;
	double *headPtr = (double *)cb->head;
	double *bufferPtr = (double *)cb->buffer;
	CEXCEPTION_T err;
	
	Try
	{
		circularBufferAdd(cb , &integer1 , copyDouble);
		circularBufferAdd(cb , &integer2 , copyDouble);
		circularBufferAdd(cb , &integer3 , copyDouble);
		circularBufferAdd(cb , &integer4 , copyDouble);
		circularBufferAdd(cb , &integer5 , copyDouble);
		circularBufferAdd(cb , &integer6 , copyDouble);
	
		TEST_ASSERT_EQUAL_FLOAT(3.2 , headPtr[0]);
		TEST_ASSERT_EQUAL_FLOAT(4.3 , headPtr[1]);
		TEST_ASSERT_EQUAL_FLOAT(5.4 , headPtr[2]);
		TEST_ASSERT_EQUAL_FLOAT(6.5 , headPtr[3]);
		TEST_ASSERT_EQUAL_FLOAT(7.6 , headPtr[4]);
		TEST_FAIL_MESSAGE("Should throw ERROR_BUFFER_FULL exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_BUFFER_FULL , err , "Expect ERROR_BUFFER_FULL exception");
		TEST_ASSERT_EQUAL(5 , cb->size);
		TEST_ASSERT_EQUAL(&bufferPtr[0] , headPtr);
	}
	
	circularBufferDel(cb);
}

void test_circularBufferRemoveInt_given_14dot8_and_16dot6_should_remove_4_and_6(void)
{
	CircularBuffer *cb = circularBufferNew( 5 , sizeof(double) );
	
	double integer1 = 14.8;
	double integer2 = 16.6;
	double *headPtr = (double *)cb->head;
	double *tailPtr = (double *)cb->tail;

	circularBufferAdd(cb , &integer1 , copyDouble);
	circularBufferAdd(cb , &integer2 , copyDouble);
	
	circularBufferRemove(cb , &integer1 , copyDouble);
	circularBufferRemove(cb , &integer2 , copyDouble);
	
	TEST_ASSERT_EQUAL_FLOAT(14.8 , tailPtr[0]);
	TEST_ASSERT_EQUAL_FLOAT(16.6 , tailPtr[1]);
		
	circularBufferDel(cb);
}

void test_circularBufferRemoveInt_given_24dot8_26dot6_27dot3_and_remove_4times_should_throw_exception(void)
{
	CircularBuffer *cb = circularBufferNew( 3 , sizeof(int) );
	
	double integer1 = 24.8;
	double integer2 = 26.6;
	double integer3 = 27.3;
	double *headPtr = (double *)cb->head;
	double *tailPtr = (double *)cb->tail;
	double *bufferPtr = (double *)cb->buffer;
	CEXCEPTION_T err;

	
	Try
	{
		circularBufferAdd(cb , &integer1 , copyInt);
		circularBufferAdd(cb , &integer2 , copyInt);
		circularBufferAdd(cb , &integer3 , copyInt);
		
		circularBufferRemove(cb , &integer1 , copyInt);
		circularBufferRemove(cb , &integer2 , copyInt);
		circularBufferRemove(cb , &integer3 , copyInt);
		circularBufferRemove(cb , &integer3 , copyInt);
		TEST_FAIL_MESSAGE("Should throw ERROR_BUFFER_EMPTY exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_BUFFER_EMPTY , err , "Expect ERROR_BUFFER_EMPTY exception");
		TEST_ASSERT_EQUAL(0 , cb->size);
		TEST_ASSERT_EQUAL(cb->buffer , cb->tail);
	}
	
	circularBufferDel(cb);
}