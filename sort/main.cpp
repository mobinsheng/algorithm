/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月08日 16时31分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "sort.h"

int compare(void* data1,void* data2)
{
    if(data1 == data2)
        return 0;

    if(data1 < data2)
        return -1;

    return 1;
}

void PrintArray(void** array,size_t len)
{
    for(size_t i = 0; i < len; ++i)
    {
        cout << (long)array[i] << " ";
    }
    cout << endl;
}

int main()
{

    const size_t len = 10;
    void* array[len] =
    {
      (void*)5,
        (void*)3,
        (void*)4,
        (void*)2,
        (void*)1,
        (void*)9,
        (void*)7,
        (void*)8,
        (void*)6,
        (void*)0
    };

    void* array2[len] =
    {
        (void*)9,
          (void*)8,
          (void*)7,
          (void*)6,
          (void*)5,
          (void*)4,
          (void*)3,
          (void*)2,
          (void*)1,
          (void*)0
    };

    void* array3[len] =
    {
        (void*)0,
          (void*)1,
          (void*)2,
          (void*)3,
          (void*)4,
          (void*)5,
          (void*)6,
          (void*)7,
          (void*)8,
          (void*)9
    };

    mgsort(array,len,compare);
    mgsort(array2,len,compare);
    mgsort(array3,len,compare);
    PrintArray(array,len);
    PrintArray(array2,len);
    PrintArray(array3,len);
    return 0;
}
