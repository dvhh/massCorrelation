#pragma once
/**
@file

@author DINH Viet Huy Hubert <dinh@ifrec.osaka-u.ac.jp>
@version 1.0
@section DESCRIPTION

A general purpose pthread ring buffer queue 
**/
#include <stdbool.h>

typedef struct rb_ringBuffer rb_ringBuffer_t;

/**
Create a new queue 

@param capacity [in] desired queue capacity 

@return newly created queue
**/
rb_ringBuffer_t* rb_init(size_t capacity);

/**
destroy queue

@param queue to destroy 

only destroy the queue, any remaining elements are up to the developper
**/
void rb_destroy(rb_ringBuffer_t* buffer);

/**
enqueue an element in the queue

@param buffer [out] queue to add element in
@param item [in] queue 
**/
void rb_enqueue(rb_ringBuffer_t* buffer,void* item);

/**
dequeue en element from the queue
@param buffer queue to get the element from
@return element dequeued from the queue
**/
void* rb_dequeue(rb_ringBuffer_t* buffer);

/**
return the element count in the list (not thread safe)
@param buffer queue to get the elements count from
@return count of elemnt in the queue 
**/
size_t rb_count(rb_ringBuffer_t* buffer);

/**
check if the queue is full 
@param buffer queue to check
@return true if the queue is full
**/
bool rb_isFull(rb_ringBuffer_t* buffer);

/**
enqueue an element in the queue (non blocking version)

@param buffer [out] queue to add element in
@param item [in] queue 
@return true if the operation succeeded
**/
bool rb_enqueueNonBlocking(rb_ringBuffer_t* buffer,void* item);

/**
dequeue en element from the queue (non blocking version)
@param buffer queue to get the element from
@param output [out] pointer to write the dequeued element
@return true if the operation succeeded
**/
bool rb_dequeueNonBlocking(rb_ringBuffer_t* buffer,void** output);
