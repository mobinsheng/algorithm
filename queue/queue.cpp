#include "queue.h"

Queue::Queue()
{
	m_nSize = 0;
	m_pHead = 0;
	m_pTail = 0;
}

Queue::~Queue()
{
	QueueNode* node = m_pHead;
	while(node != 0)
	{
		QueueNode* tmp = node;
		node = node->next;
		delete tmp;
	}
	m_nSize = 0;
	m_pHead = 0;
	m_pTail = 0;
}

void Queue::EnQueue(void* data)
{
	QueueNode* node = new QueueNode;
	node->data = data;

	if(m_pTail == 0)
	{
		m_pHead = m_pTail = node;
	}
	else
	{
		m_pTail->next = node;
		node->prev = m_pTail;
		m_pTail = node;
	}

	++m_nSize;
}

void* Queue::DeQueue()
{
	if(m_pHead == 0)
		return 0;

    if(m_pHead == m_pTail)
    {
        void* data = m_pHead->data;
        delete m_pHead;
        m_pHead = m_pTail = 0;
        m_nSize = 0;
        return data;
    }

	QueueNode* node = m_pHead;

	m_pHead = m_pHead->next;

	if(m_pHead != 0)
	{
		m_pHead->prev = 0;
	}
	--m_nSize;

	void* data = node->data;

	delete node;

	return data;
}

size_t Queue::Size()
{
	return m_nSize;
}

bool Queue::Empty()
{
	if(0 == m_nSize)
		return true;

	return false;
}

void* Queue::First()
{
	if(m_pHead == 0)
		return 0;

	return m_pHead->data;
}

void* Queue::Back()
{
	if(m_pTail == 0)
		return 0;

	return m_pTail->data;
}

QueueNode* Queue::Head()
{
	return m_pHead;
}

QueueNode* Queue::Tail()
{
	return m_pTail;
}
