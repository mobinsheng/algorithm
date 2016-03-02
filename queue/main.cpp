#include "queue.h"

int main()
{
	Queue Q;

	for(int i = 0; i < 10; ++i)
	{
		int* p = new int(i);
		Q.EnQueue(p);
		cout << "Size = " << Q.Size() << endl;
	}

	for(QueueNode* node = Q.Head(); node != 0; node = node->next)
	{
		int* p =(int*)node->data;
		cout << *p<< " ";
	}
	cout << endl;


	while(Q.Empty() == false)
	{
		int* p = (int*)Q.DeQueue();
		cout << *p << " ";
		cout << "Size = " << Q.Size() << endl;
		
	}
	cout << endl;
	return 0;
}
