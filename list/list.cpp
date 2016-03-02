/*
 * =====================================================================================
 *
 *       Filename:  list.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 14时40分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "list.h"

List::List()
{
	m_nSize = 0;
	m_pHead = 0;
	m_pTail = 0;
}

List::List(const List& ls)
{
    m_nSize = 0;
    m_pHead = 0;
    m_pTail = 0;

	ListNode* node = ls.m_pHead;
	while(node != 0 )
	{
		Add(node->data);
		node = node->next;
	}
}

List& List::operator=(const List& ls)
{
    Clear();
	ListNode* node = ls.m_pHead;
	while(node != 0)
	{
		Add(node->data);
		node = node->next;
	}
	return *this;
}

List::~List()
{
	ListNode* node = m_pHead;
	while(node != 0)
	{
		ListNode* tmp = node;
		node = node->next;
		delete tmp;
	}

	m_nSize = 0;
	m_pTail = 0;
	m_pHead = 0;
}

size_t List::Size()
{
	return m_nSize;
}

bool List::Empty()
{
	if(0 == m_nSize)
		return true;

	return false;
}

ListNode* List::Head()
{
	return m_pHead;
}

ListNode* List::Tail()
{
	return m_pTail;
}

ListNode* List::Begin()
{
    return m_pHead;
}

ListNode* List::End()
{
    return 0;
}



void* List::Front()
{
	if(0 == m_pHead)
		return 0;

	return m_pHead->data;
}

void* List::Back()
{
	if(0 == m_pTail)
		return 0;

	return m_pTail->data;
}

ListNode* List::Find(void* data)
{
	ListNode* node = m_pHead;

	while(node != 0)
	{
		if(node->data == data)
			return node;

		node = node->next;
	}

	return 0;
}

bool List::Find(ListNode* node)
{
	ListNode* p = m_pHead;

	while(p != 0)
	{
		if(p == node)
			return true;

		node = node->next;
	}

	return false;
}

void List::Insert(ListNode* element,void* data)
{
	ListNode* node = new ListNode();
	node->data = data;
	Insert(element,node);
}

void List::Insert(ListNode* element,ListNode* data)
{
	if(element == 0)
	{
		++m_nSize;

		if(m_pTail == 0)
		{
			m_pHead = m_pTail = data;
		}
		else
		{
			m_pTail->next = data;
			data->prev = m_pTail;
			m_pTail = data;
		}
	}
	else
	{
		++m_nSize;

		if(m_pHead == element)
		{
			data->next = m_pHead;
			m_pHead->prev = data;
			m_pHead = data;
		}
		else
		{
			ListNode* prev = element->prev;

			data->next = element;
			data->prev = element->prev;
			
			if(prev != 0)
			{
				prev->next = data;
			}

			element->prev = data;
		}
	}
}

void List::Add(void* data)
{
	Insert(0,data);
}

void List::Add(ListNode* node)
{
	Insert(0,node);
}

void List::Remove(void* data)
{
	while(true)
	{
		ListNode* node = Find(data);
		if(node == 0)
		{
			break;
		}

		Remove(node);
	}
}

void List::Remove(ListNode* node)
{
	if(node == 0)
		return;

	ListNode* next = node->next;
	ListNode* prev = node->prev;

	if(next != 0)
	{
		next->prev = prev;
		if(prev != 0)
		{
			// node有上节点和下节点
			prev->next = next;
		}
		else
		{
			// node有下节点没有上节点（即头节点）
			m_pHead = next;
		}
	}
	else
	{
		if(prev != 0)
		{
			// node有上节点没有下节点（即尾节点）
			prev->next = 0;
			m_pTail = prev;
		}
		else
		{
			// node没有上节点也没有下节点
			m_pHead = 0;
			m_pTail = 0;
		}
	}

	delete node;
	--m_nSize;
}


void List::Clear()
{
	ListNode* node = m_pHead;
	while(node != 0)
	{
		ListNode* tmp = node;
		node = node->next;
		delete tmp;
	}

	m_nSize = 0;
	m_pHead = 0;
	m_pTail = 0;
}

// ===================================
// CList双向循环链表

CList::CList()
{
	m_pHead = 0;
	m_nSize = 0;
}

CList::~CList()
{
	ListNode* node = m_pHead;
	while(m_nSize > 0)
	{
		--m_nSize;
		ListNode* tmp = node;
		node = node->next;
		delete tmp;
	}

	m_pHead = 0;
}

ListNode* CList::Head()
{
	return m_pHead;
}

size_t CList::Size()
{
	return m_nSize;

}

bool CList::Empty()
{
	if(0 == m_nSize)
		return true;
	return false;
}

void CList::Insert(ListNode* element,ListNode* node)
{
	++m_nSize;

	if(element == 0)
	{
		if(m_pHead == 0)
		{
			node->next = node;
			node->prev = node;

			m_pHead = node;
		}
		else
		{
			ListNode* tail = m_pHead->prev;
			node->next = m_pHead;
			node->prev = tail;
			tail->next = node;
			m_pHead->prev = node;
		}
	}
	else
	{
		ListNode* next = element->next;
		ListNode* prev = element->prev;

		node->next = element;
		node->prev = prev;

		prev->next = node;
		element->prev = node;

	}
}

void CList::Insert(ListNode* element,void* data)
{
	ListNode* node = new ListNode();
	node->data = data;
	Insert(element,node);
}

void CList::Remove(ListNode* node)
{
	if(node == 0)
		return ;


	if(node == m_pHead)
	{
		if(1 == m_nSize)
		{
			m_pHead = 0;
		}
		else
		{
			ListNode* next = node->next;
			ListNode* prev = node->prev;
			
			prev->next = next;
			next->prev = prev;

			m_pHead = next;
		}
	}
	else
	{
		ListNode* next = node->next;
		ListNode* prev = node->prev;

		prev->next = next;
		next->prev = prev;
	}

	--m_nSize;
	delete node;
}

void CList::Remove(void* data)
{
	while(true)
	{
		ListNode* node = Find(data);
		if(node == 0)
			break;

		Remove(node);
	}
}

void CList::Clear()
{
	ListNode* node = m_pHead;

	while(m_nSize > 0)
	{
		ListNode* tmp = node;
		node = node->next;
		--m_nSize;
		delete tmp;
	}
	m_nSize = 0;
	m_pHead = 0;
}


bool CList::Find(ListNode* node)
{
	if(node == 0)
		return false;

	if(m_pHead == 0)
		return false;

	if(m_pHead == node)
	{
		return true;
	}
	ListNode* p = m_pHead->next;

	while(p != 0 && p != m_pHead)
	{
		if(p == node)
			return true;

		p = p->next;
	}

	return false;
}

ListNode* CList::Find(void* data)
{
	if(data == 0)
		return 0;

	if(m_pHead == 0)
		return 0;

	if(m_pHead->data == data)
		return m_pHead;

	ListNode* node = m_pHead->next;

	while(node != 0 && node != m_pHead)
	{
		if(node->data == data)
			return node;

		node = node->next;
	}

	return 0;
}

void CList::Add(ListNode* node)
{

	Insert(0,node);
}

void CList::Add(void* data)
{

	ListNode* node = new ListNode;
	node->data = data;
	Insert(0,node);
}

