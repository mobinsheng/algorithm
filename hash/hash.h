/*
 * =====================================================================================
 *
 *       Filename:  hash.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月29日 17时13分22秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _HASH_H_
#define _HASH_H_

#include <math.h>
#include "../list/list.h"

// 哈希函数类型
typedef size_t (*HashFunc)(void* key,size_t nBuckets);
// 键的比较函数
typedef bool (*HashKeyCompareFunc)(void* key1,void* key2);

// 哈希表的项
struct HashItem
{
	void* key;
	void* value;
};

class Hash
{
	public:
		enum
		{
			// 默认的哈希桶的个数
			default_buckets = 64,
		};

		// 构造函数
		Hash(size_t nBuckets = default_buckets);
		Hash(HashFunc hashFunc,HashKeyCompareFunc compareFunc,size_t nBuckets = default_buckets);
		Hash(HashFunc hashFunc,size_t nBuckets = default_buckets);
		Hash(HashKeyCompareFunc compareFunc,size_t nBuckets = default_buckets);
		// 析钩函数
		~Hash();

		// 下面四个函数主要用于遍历
		HashItem* Begin();
		HashItem* End();
		HashItem* Current();
		HashItem* Next();

		// 插入数据
		HashItem* Insert(void* key,void* data);
		// 删除数据
		void Remove(void* key);
		// 查找
		HashItem* Find(void* key);
		bool Empty();
		size_t Size();
		// 遍历哈希表，并对每一项调用handle函数
		void Traversal(void(*handle)(void* param,HashItem* item),void* param);
	private:
		// 哈希桶的个数
		size_t m_nBuckets;
		// 数据的个数
		size_t m_nSize;
		// 哈希表，用list模拟
		List*  m_pTable;
		// 哈希函数
		HashFunc m_HashFunc;
		// 键的比较函数
		HashKeyCompareFunc m_CompareFunc;
		struct IteratorInfo
		{
			IteratorInfo()
			{
				m_nBucketIndex = -1;
				m_pCurrentNode = 0;
			}

			void Reset()
			{
				m_nBucketIndex = -1;
				m_pCurrentNode = 0;
			}

			bool Valid()
			{
				if(m_nBucketIndex < 0 || m_pCurrentNode == 0)
					return false;

				return true;
			}

			int  m_nBucketIndex;
			ListNode* m_pCurrentNode;
		};
		IteratorInfo m_IterInfo;

};

class OpenHash
{
	public:
		// 构造函数
		OpenHash(size_t nLength);
		OpenHash(HashFunc hashFunc,HashKeyCompareFunc compareFunc,size_t nLength);
		OpenHash(HashFunc hashFunc,size_t nLength);
		OpenHash(HashKeyCompareFunc compareFunc,size_t nLength);
		// 析钩函数
		~OpenHash();

		// 下面四个函数主要用于遍历
		HashItem* Begin();
		HashItem* End();
		HashItem* Current();
		HashItem* Next();

		// 插入数据
		HashItem* Insert(void* key,void* data);
		// 删除数据
		void Remove(void* key);
		// 查找
		HashItem* Find(void* key);
		bool Empty();
		size_t Size();

	private:
		struct HashItemWrap
		{
			HashItem item;
			bool exist_flag;
			HashItemWrap()
			{
				exist_flag = false;
			}
        };
		HashItemWrap* m_pTable;
		size_t    m_nLength;
		// 数据的个数
		size_t m_nSize;
		// 哈希函数
		HashFunc m_HashFunc;
		// 键的比较函数
		HashKeyCompareFunc m_CompareFunc;


        int m_nCurrentIndex;

};
#endif
