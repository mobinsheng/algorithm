#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <string>
#include <iostream>
using namespace std;

// 队列节点
struct QueueNode
{

	QueueNode()
	{
		data = 0;
		next = 0;
		prev = 0;
	}

	// 数据
	void* data;
	// 下一个节点
	struct QueueNode* next;
	// 上一个节点
	struct QueueNode* prev;
};

// 队列
class Queue
{
	public:

		Queue();

		~Queue();

		void EnQueue(void* data);

		void* DeQueue();

		bool Empty();

		size_t Size();

		QueueNode* Head();

		QueueNode* Tail();

		void* First();

		void* Back();

	private:
		QueueNode* m_pHead;
		QueueNode* m_pTail;
		size_t m_nSize;

};
#endif
