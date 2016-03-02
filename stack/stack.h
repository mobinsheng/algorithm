/*
 * =====================================================================================
 *
 *       Filename:  stack.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 11时56分16秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <string>
using namespace std;

struct StackNode
{
	StackNode()
	{
		data = 0;
		prev = 0;
		next = 0;
	}

	void* data;
	struct StackNode* prev;
	struct StackNode* next;
};

class Stack
{
	public:
		Stack();
		~Stack();

		void Push(void* data);
		void* Pop();
		void* Top();
		size_t Size();
		bool Empty();
	private:
		size_t m_nSize;
		StackNode* m_pTop;
};
#endif
