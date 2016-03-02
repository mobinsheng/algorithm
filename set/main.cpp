/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 17时24分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include "set.h"

bool match(void* data1,void* data2)
{
	int* p1=(int*)data1;
	int* p2=(int*)data2;

	if( (*p1) == (*p2))
		return true;

	return false;
}

void Print(const string& str,Set& s)
{
	cout << str << endl;

	SetNode* node = s.Head();
	while(node != 0)
	{
		int* p = (int*)node->data;
		cout << *p <<" ";
		node = node->next;
	}
	cout << endl;
}

int main()
{
	Set s(match);
	Set s1(match),s2(match);

	for(int i=0; i < 10 ;++i)
	{
		int* p = new int(i);
		s1.Insert(p);
	}

	cout << "Set1 Size="<< s1.Size() << endl;
	Print("Set1:",s1);
	for(int i = 5; i < 15; ++i)
	{
		int* p = new int(i);
		s2.Insert(p);
	}
	cout << "Set2 Size="<< s2.Size() << endl;
	Print("Set2:",s2);

	s = Set::Union(s1,s2);
	Print("Union:",s);
	s = Set::Intersection(s1,s2);
	Print("Intersection:",s);
	s = Set::Difference(s1,s2);
	Print("Diff:",s);

	return 0;
}
