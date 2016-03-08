/*
 * =====================================================================================
 *
 *       Filename:  pqueue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月08日 16时06分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "pqueue.h"

PQueue::PQueue(HeapDataCompareFunc compareFunc)
{
    if(compareFunc == 0)
        m_pQueue = new Heap(Heap::BigHeap);
    else
        m_pQueue = new Heap(Heap::BigHeap,compareFunc);
}


PQueue::~PQueue()
{
    delete m_pQueue;
}

size_t PQueue::Size()
{
    return m_pQueue->Size();
}

bool PQueue::Empty()
{
    return m_pQueue->Empty();
}

void PQueue::EnQueue(void *data)
{
    m_pQueue->Insert(data);
}

void* PQueue::Front()
{
    return m_pQueue->Top();
}

void* PQueue::DeQueue()
{
    return m_pQueue->Pop();
}
