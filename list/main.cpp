/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 14时41分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "list.h"

template<class T>
void PrintList(List& ls)
{
	ListNode* node = ls.Head();

    for(ListNode* node = ls.Begin(); node != ls.End();node = node->Next())
    {
        T* p = (T*)node->data;
        cout << *p << " " ;
    }

	cout << endl;
}

int main()
{
	List ls;

	for(int i = 0;i < 10 ; ++i)
	{
		int* p= new int(i);
		ls.Add(p);
	}

	cout << "Size = " << ls.Size() << endl;



	for(int i = 10 ; i < 20 ; ++i)
	{
		int* p = new int(i);

		if(i % 2 == 0)
		{
			ls.Insert(ls.Head(),p);

		}
		else
		{
			ls.Insert(ls.Tail(),p);
		}
	}

	cout << "Size = " << ls.Size() << endl;
	
	PrintList<int>(ls);

	cout << "===========" << endl;
	int i = 0;
	while(ls.Empty() == false)
	{
		int* head = (int*)ls.Front();
		int* tail = (int*)ls.Back();
		cout << "Head = "<< *head <<" Tail = "<<*tail<< endl;
		if( i % 2 == 0)
		{
			ls.Remove(ls.Head());
		}
		else
		{
			ls.Remove(ls.Tail());
		}
		++i;
	}

	cout << "==CList============" << endl;

	CList cls;

	for(int i =0 ;i < 10 ; ++i)
	{
		int*p = new int(i);
		cls.Add(p);
	}

	cout << "CList Size = " << cls.Size() << endl;

	for(int i = 10; i < 20;++i)
	{
		int* p = new int(i);

		if(i %2 == 0)
		{
			cls.Insert(cls.Head(),p);
		}
		else
		{
			cls.Add(p);
		}
	}

	cout << "CList Size = " << cls.Size() <<endl;

	ListNode* node = cls.Head();

	for(int i = 0; i < cls.Size(); ++i)
	{
		if(node == 0)
			break;
		int * p = (int*)node->data;
		cout << *p << " ";
		node = node->next;
	}
	cout << endl;

	i = 0;
	while(cls.Empty() == false)
	{
		node = cls.Head();

		int *p = (int*)node->data;

		int* tail = (int*)node->prev->data;

		cout << "Head=" << *p << " Tail="<<*tail<<endl;

		if(i % 2 == 0)
		{
			cls.Remove(cls.Head());
		}
		else
		{
			cls.Remove(cls.Head()->prev);
		}
		++i;
	}
	cout << endl;
	return 0;
}
