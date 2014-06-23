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
	char *headPtr = (char *)cb->head;

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
	char *headPtr = (char *)cb->head;
	CEXCEPTION_T err;
	
	Try
	{
		circularBufferAdd(cb , &integer1 , copyInt);
		circularBufferAdd(cb , &integer2 , copyInt);
		circularBufferAdd(cb , &integer3 , copyInt);
		circularBufferAdd(cb , &integer4 , copyInt);
	
		TEST_ASSERT_EQUAL(32 , headPtr[0]);
		TEST_ASSERT_EQUAL(33 , headPtr[1]);
		TEST_ASSERT_EQUAL(34 , headPtr[2]);
		TEST_ASSERT_EQUAL(35 , headPtr[3]);
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL(&headPtr[4] , cb->head);
		TEST_ASSERT_EQUAL(cb->buffer , cb->tail);
		TEST_ASSERT_EQUAL(4 , cb->size);
	}
	
	circularBufferDel(cb);
}









void Xtest_circularBufferAddDouble_given_5_dot_65_n_7_dot_21_should_5_dot_65_n_7_dot_21_buffer(void)
{
	CircularBuffer *cb = circularBufferNew( 7 , sizeof(int) );
	
	double integer1 = 5.65;
	double integer2 = 7.21;
	char *headPtr = (char *)cb->head;

	circularBufferAdd(cb , &integer1 , copyDouble);
	circularBufferAdd(cb , &integer2 , copyDouble);
	
	TEST_ASSERT_EQUAL(10 , headPtr[0]);
	TEST_ASSERT_EQUAL(21 , headPtr[1]);
	TEST_ASSERT_EQUAL(&headPtr[2] , cb->head); //cb->head now is pointing to next location
	TEST_ASSERT_EQUAL(cb->buffer , cb->tail); //cb->tail remain at the 1st location
	TEST_ASSERT_EQUAL(2 , cb->size);
		
	circularBufferDel(cb);
}