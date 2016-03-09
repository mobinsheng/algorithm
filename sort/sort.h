/*
 * =====================================================================================
 *
 *       Filename:  sort.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月08日 16时31分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _MY_SORT_H_
#define _MY_SORT_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef int (*SortCompareFunc)(void* data1,void* data2);

// 插入排序
void issort(void** array,size_t len,SortCompareFunc compareFunc);

// 快速排序
void qksort(void** array,size_t len,SortCompareFunc compareFunc);

// 归并排序
void mgsort(void** array,size_t len,SortCompareFunc compareFunc);

// 计数排序
void ctsort(void** array,size_t len,SortCompareFunc compareFunc);

// 基数排序
void rxsort(void** array,size_t len,SortCompareFunc compareFunc);
//
#endif
