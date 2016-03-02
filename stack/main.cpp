/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 11时56分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "stack.h"

int main()
{
	Stack st;

	for(int i = 0; i < 10; ++i)
	{
		int* p = new int(i);
		st.Push(p);
		cout << "Size = " << st.Size() << endl;
	}

	while(st.Empty() == false)
	{
		cout << "Size = " << st.Size() << endl;
		int* p = (int*)st.Pop();
		cout << *p << endl;
		delete p;

	}
	return 0;
}
