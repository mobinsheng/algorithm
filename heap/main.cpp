/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月07日 19时12分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "heap.h"
#include "pqueue.h"

void testHeap()
{
    Heap heap(Heap::BigHeap);


    for(int i = 0 ; i < 6 ; ++i)
    {
        heap.Insert((void*)i);
    }

    for(int i = 10; i >= 6; --i)
    {
        heap.Insert((void*)i);
    }


    for(int i = 7; i < 20; ++i)
    {
        heap.Insert((void*)i);
    }
    while(heap.Size() > 0)
    {
        long i = (long)heap.Pop();
        cout << i << endl;
    }
}

void testPQueue()
{
    PQueue Q;


    for(int i = 0 ; i < 6 ; ++i)
    {
        Q.EnQueue((void*)i);
    }

    for(int i = 10; i >= 6; --i)
    {
        Q.EnQueue((void*)i);
    }


    for(int i = 7; i < 20; ++i)
    {
        Q.EnQueue((void*)i);
    }
    while(Q.Size() > 0)
    {
        long i = (long)Q.Front();
        Q.DeQueue();
        cout << i << endl;
    }
}

int main()
{
    testPQueue();
    return 0;
}
