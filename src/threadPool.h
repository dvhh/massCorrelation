#pragma once
/**
@file

@author DINH Viet Huy Hubert <dinh@ifrec.osaka-u.ac.jp>
@version 1.0
@section DESCRIPTION

generic pthread threadpool
**/

/**
worker routine definition
**/
typedef void (tp_worker_t )(void*);

typedef struct tp_threadpool tp_threadpool_t;

/**
Create a threadpool

@param count [in] number of threads available in the threadpool
@return new threadpool created
**/
tp_threadpool_t* tp_init(unsigned int count);

/**
destroy a threadpool 

@param pool pool to be destroyed
**/
void tp_destroy(tp_threadpool_t* pool);

/**
enqueue a work request to the pool

@param pool pool to be used
@param worker routine to be used for the task
@param arg task paramters
**/
void tp_enqueue(tp_threadpool_t* pool,tp_worker_t* worker,void* arg);

/**
wait for current outstanding task queue in the pool to finish 

@param pool threadpool to wait task upon
**/
void tp_wait(tp_threadpool_t* pool);
