/*
 * =====================================================================================
 *
 *       Filename:  stack.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 11时56分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "stack.h"


Stack::Stack()
{
	m_pTop = 0;
	m_nSize = 0;
}

Stack::~Stack()
{
	StackNode* node = m_pTop;
	while(node != 0 )
	{
		StackNode* tmp = node;
		node = node->prev;
		delete tmp;
	}
	m_pTop = 0;
	m_nSize =0;
}

void Stack::Push(void* data)
{
	StackNode* node = new StackNode();
	node->data = data;

	if(0 == m_pTop)
	{
		m_pTop = node;
		++m_nSize;
		return;
	}

	m_pTop->next = node;
	node->prev = m_pTop;

	m_pTop = node;

	++m_nSize;
}

void* Stack::Pop()
{
	StackNode* node = m_pTop;
	void* data = node->data;

	StackNode* prev = m_pTop->prev;
	
	if(0 == prev)
	{
		m_pTop = 0;
	}
	else
	{
		prev->next = 0;
		m_pTop = prev;
	}

	delete node;
	--m_nSize;
	return data;
}

void* Stack::Top()
{
	if(0 == m_pTop)
		return 0;

	return m_pTop->data;
}

size_t Stack::Size()
{
	return m_nSize;
}

bool Stack::Empty()
{
	if(0 == m_nSize)
		return true;

	return false;
}
