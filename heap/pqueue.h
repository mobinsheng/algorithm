/*
 * =====================================================================================
 *
 *       Filename:  pqueue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月08日 16时06分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _PQUEUE_H_
#define _PQUEUE_H_

#include "heap.h"

class PQueue
{
public:
    PQueue(HeapDataCompareFunc compareFunc = 0);
    ~PQueue();

    void EnQueue(void* data);
    void* DeQueue();
    size_t Size();
    void* Front();
    bool Empty();
private:
    Heap* m_pQueue;
};
#endif
