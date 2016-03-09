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
#include <math.h>

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

    // 取中间索引
    int mid = (i + j ) / 2;

    while(i < j)
    {
        // 从右到左，找到第一个比中间点小的元素
        while(j >= mid)
        {
            if(compareFunc(array[j],array[mid]) > 0)
                --j;
            else
                break;
        }

        // 从左到右，找到第一个比中间点大的元素
        while(i <= mid)
        {
            if(compareFunc(array[i],array[mid]) < 0)
                ++i;
            else
                break;
        }

        if(i == j)
            break;

        // 交换两个元素的值
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

void mgsort_main(void** array,int i,int j,SortCompareFunc compareFunc)
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
    if(array == 0 || len <= 0)
        return;

    long maxNum = (long)array[0];

    long value = 0;

    // 选取数组中的最大值
    for(size_t i = 1; i < len ;++i)
    {
        value = (long)array[i];
        if(value> maxNum)
            maxNum = value;
    }

    // 建立索引数组
    long* indexArray = new long[maxNum + 1];
    memset(indexArray,0,(1+maxNum) * sizeof(long));

    // 记录每一个数出现的次数
    // 索引数组的下标就是这个数，而对应的元素值就是这个值出现的次数
    // 这意味着数值最小的数的统计信息在最左边
    // 而数值最大的数的统计信息出现在最右边
    // 所有的数的统计信息相加就是源数组的元素数目
    for(size_t i =0 ;i < len; ++i)
    {
        value = (long)array[i];
        indexArray[value]++;
    }

    // 这个循环之后，索引数组中实际存放了某个数排序之后在数组中的索引
    // 例如num这个数排序之后的索引就是indexArray[num]
    for(int i = 1; i < maxNum + 1; ++i)
    {
        indexArray[i] = indexArray[i - 1] + indexArray[i];
    }

    void** tempArray = new void*[len];

    // 进行排序处理
    for(int i = len - 1; i >= 0; --i)
    {
        // 元素值
        value = (long)array[i];
        // 元素值的排序好之后的索引
        int indexOfValue = indexArray[value];
        // 放在准确的位置
        tempArray[indexOfValue - 1] = (void*)value;
        // 这里减一的目的是有些元素值可能相同
        // 所以减去1就表示重复的元素依次往前排
        indexArray[value] = indexArray[value] - 1;
    }

    memcpy(array,tempArray,sizeof(void*) * len);

    delete[] tempArray;
    delete[] indexArray;
}

// 基数排序
void rxsort(void** array,size_t len,SortCompareFunc compareFunc)
{
    if(array == 0 || len <= 0)
        return ;

    // 临时数组
    void** tempArray = new void*[len];


    // 得到数组的最大值
    long maxNum = (long)array[0];
    for( int i = 0 ; i < len; ++i)
    {
        if(maxNum < (long)array[i])
            maxNum = (long)array[i];
    }

    // 根据最大值计算位数（例如199是三位数）
    int count = 0;
    while(maxNum != 0)
    {
        ++count;
        maxNum /= 10;
    }

    // 索引数组，用于计数排序
    int* indexArray = new int[10];

    // 对每一位进行计数排序
    for(int i = 0 ; i < count; ++i)
    {
        // 清空索引数组
        for(int i = 0; i < 10; ++i)
            indexArray[i] = 0;

        // 当前进行到1,10,100,1000……中的哪一个级别
        long pvalue = pow(10,i);

        // 得到整个数组某一位的统计信息
        for(int j = 0; j <len; ++j)
        {
            // 得到某个数第i位的数值
            int index = ((long)array[j] / pvalue) % 10;

            // 统计信息
            indexArray[index]++;
        }

        // 得到排序后的索引位置
        for(int j = 1; j < 10; ++j)
            indexArray[j] += indexArray[j - 1];

        // 进行排序
        for(int j = len - 1; j >=0; --j)
        {
            int index = ((long)array[j] / pvalue) % 10;
            tempArray[indexArray[index] - 1] = array[j];
            indexArray[index]--;
        }

        memcpy(array,tempArray,sizeof(long)* len);
    }

    delete[] tempArray;
    delete[] indexArray;
}
