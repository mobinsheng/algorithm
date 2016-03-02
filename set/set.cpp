/*
 * =====================================================================================
 *
 *       Filename:  set.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 17时24分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "set.h"

Set::Set(SetMatchFunc fun)
{
	m_pMatchFun = fun;
}

Set::Set(const Set& s)
{
	m_Set = s.m_Set;
	m_pMatchFun = s.m_pMatchFun;
}
  
Set& Set::operator=(const Set& s)
{
	m_Set = s.m_Set;
	m_pMatchFun = s.m_pMatchFun;
	return *this;
}


size_t Set::Size()
{
	return m_Set.Size();
}

bool Set::Empty()
{
	return m_Set.Empty();
}

void Set::Insert(void* data)
{
	if(IsMember(data))
		return ;
	m_Set.Add(data);
}

void Set::Remove(void* data)
{
	m_Set.Remove(data);
}

bool Set::IsMember(void* data)
{
	ListNode* node = m_Set.Head();
	while(node != 0)
	{
		if(m_pMatchFun(data,node->data))
			return true;
		node = node->next;
	}

	return false;
}

bool Set::IsSubSet(Set& s)
{
	if(Size() < s.Size())
		return false;

	ListNode* node = s.m_Set.Head();

	while(node != 0)
	{
		if(!IsMember(node->data))
			return false;
	}

	return true;
}

bool Set::Equal(Set& s)
{
	if(Size() != s.Size())
		return false;

	return IsSubSet(s);
}

SetNode* Set::Head()
{
	return m_Set.Head();
}

SetNode* Set::Begin()
{
	return m_Set.Begin();
}

SetNode* Set::End()
{
	return m_Set.End();
}

Set Set::Union(Set& set1,Set& set2)
{
	Set result(set1.m_pMatchFun);

	if(set1.Size() > set2.Size())
	{
		result = set1;
		ListNode* node = set2.Head();

		while(node != 0)
		{
			if(!set1.IsMember(node->data))
			{
				result.Insert(node->data);
			}
			node = node->next;
		}
	}
	else
	{
		result = set2;
		ListNode* node = set1.Head();
		while(node != 0)
		{
			if(!set2.IsMember(node->data))
			{
				result.Insert(node->data);
			}
			node = node->next;
		}
	}

	return result;
}

Set Set::Intersection(Set& set1,Set& set2)
{
	Set result(set1.m_pMatchFun);

	if(set1.Size() < set2.Size())
	{
		ListNode* node = set1.m_Set.Head();
		while(node != 0)
		{
			if(set2.IsMember(node->data))
			{
				result.Insert(node->data);
			}
			node = node->next;
		}
	}
	else
	{
		ListNode* node = set2.m_Set.Head();
		while(node != 0)
		{
			if(set1.IsMember(node->data))
			{
				result.Insert(node->data);
			}
			node = node->next;
		}
	}

	return result;
}

Set Set::Difference(Set& set1,Set& set2)
{
	Set result(set1.m_pMatchFun);

	ListNode* node = set1.m_Set.Head();
	while(node != 0 )
	{
		if(!set2.IsMember(node->data))
		{
			result.Insert(node->data);
		}
		node = node->next;
	}
	return result;
}

