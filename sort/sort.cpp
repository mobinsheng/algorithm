/*
 * =====================================================================================
 *
 *       Filename:  sort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月08日 16时31分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "sort.h"

// 插入排序
void issort(void** array,size_t len,SortCompareFunc compareFunc)
{
    void* temp = 0;

    for(size_t i = 1; i < len; ++i)
    {
        temp = array[i];

        int j = i - 1;

        for( ; j >= 0; --j)
        {
            if(compareFunc(array[j],temp) < 0)
            {
                break;
            }
            array[j + 1] = array[j];
        }

        array[j + 1] = temp;
    }
}

// 进行分区
// 选定一个点，索引比该点小的元素的值都比该点小
// 索引比该点大的元素的值都比该点大
int partition(void** array,int i,int j,SortCompareFunc compareFunc)
{
    if(array == 0 || i >= j || i <0 || j < 0 || compareFunc == 0)
        return -1;

    int mid = (i + j ) / 2;

    while(i < j)
    {
        while(j >= mid)
        {
            if(compareFunc(array[j],array[mid]) > 0)
                --j;
            else
                break;
        }

        while(i <= mid)
        {
            if(compareFunc(array[i],array[mid]) < 0)
                ++i;
            else
                break;
        }

        if(i == j)
            break;

        void* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        ++i;
        --j;
    }

    return mid;
}

// 快速排序的主函数
void qksort_main(void** array,int i,int j ,SortCompareFunc compareFunc)
{
    while(i < j)
    {
        // 选择一个分区
        int mid = partition(array,i,j,compareFunc);
        if(mid < 0)
            return;
        // 对分区左边进行排序
        qksort_main(array,i,mid,compareFunc);

        // 下一次排序在右边进行
        i = mid + 1;
    }
}

// 快速排序
void qksort(void** array,size_t len,SortCompareFunc compareFunc)
{
    qksort_main(array,0,len - 1,compareFunc);
}


void merge(void** array,int i,int mid,int j,SortCompareFunc compareFunc)
{
    if(i == mid && mid == j)
        return;

    if(array == 0 || compareFunc == 0)
        return;

    if(i < 0 || mid < 0 || j < 0)
        return;

    if(i > mid || mid > j || i > j)
        return ;



    void** temp = new void*[j - i + 1];

    int indexTemp = 0;

    int index1 = i;

    int index2 = mid + 1;


    while(index1 <= mid && index2 <= j)
    {
        if(compareFunc(array[index1],array[index2]) < 0)
        {
            temp[indexTemp++] = array[index1];
            ++index1;
        }
        else
        {
            temp[indexTemp++] = array[index2];
            ++index2;
        }
    }

    if(index1 > mid)
    {
        while(index2 <= j)
        {
            temp[indexTemp++] = array[index2];
            ++index2;
        }
    }
    else
    {
        while(index1 <= mid)
        {
            temp[indexTemp++] = array[index1];
            ++index1;
        }
    }

    memcpy(array+i ,temp,(j - i + 1)* sizeof(void*));


    delete[] temp;
}

int mgsort_main(void** array,int i,int j,SortCompareFunc compareFunc)
{
    int k = (i + j ) / 2;
    if(i < j)
    {
        mgsort_main(array,i,k,compareFunc);
        mgsort_main(array,k + 1,j,compareFunc);
        merge(array,i,k,j,compareFunc);
    }
}

// 归并排序
void mgsort(void** array,size_t len,SortCompareFunc compareFunc)
{
    mgsort_main(array,0,len - 1,compareFunc);
}

// 计数排序
void ctsort(void** array,size_t len,SortCompareFunc compareFunc)
{

}

// 基数排序
void rxsort(void** array,size_t len,SortCompareFunc compareFunc)
{

}
