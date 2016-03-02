/*
 * =====================================================================================
 *
 *       Filename:  set.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 17时23分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _SET_H_
#define _SET_H_
#include "../list/list.h"

// 集合内数据的比较函数
// 需要自己定义比较函数
typedef bool (*SetMatchFunc)(void* data1,void* data2);


typedef ListNode SetNode;

// 集合类
class Set
{
	public:
		Set(SetMatchFunc fun);

		Set(const Set&s);
		Set& operator=(const Set& s);


		// 插入数据
		void Insert(void* data);
		// 移除数据
		void Remove(void* data);

		// 集合大小
		size_t Size();
		// 是否为空
		bool Empty();

		bool IsMember(void* data);
		// 判断集合s是不是自己的子集
		bool IsSubSet(Set& s);
		// 判断集合s是否和自己相等
		bool Equal(Set& s);

		SetNode* Head();
		SetNode* Begin();
		SetNode* End();

		// 两个集合的并集
		static Set Union(Set& set1,Set& set2);
		// 两个集合的交集
		static Set Intersection(Set& set1,Set& set2);
		// 两个集合的差集
		static Set Difference(Set& set1,Set& set2);

	private:
		List m_Set;
		SetMatchFunc m_pMatchFun;
};
#endif
