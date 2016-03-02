/*
 * =====================================================================================
 *
 *       Filename:  hash.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月29日 17时13分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "hash.h"

size_t DefaultHash(void* val,size_t nBuckets)
{
    long key = (long)val;

    double pos = 0.618 * (double)key;
    pos =pos - floor(pos);
	pos *= nBuckets;
	return (size_t)pos;
}

size_t DefaultHash2(void* val,size_t nBuckets)
{
      long key = (long)val;
      key = (~key) + (key << 21); // key = (key << 21) - key - 1;
      key = key ^ (key >> 24);
      key = (key + (key << 3)) + (key << 8); // key * 265
      key = key ^ (key >> 14);
      key = (key + (key << 2)) + (key << 4); // key * 21
      key = key ^ (key >> 28);
      key = key + (key << 31);
      return (size_t)key;

}

bool DefaultCompare(void* key1,void* key2)
{
	if(key1 == key2)
		return true;
	return false;
}
void Hash::Traversal(void(*handle)(void* param,HashItem* item),void* param)
{
	for(size_t i = 0; i < m_nBuckets;++i)
	{
		ListNode* node = m_pTable[i].Head();
		while(node != 0)
		{
			HashItem* item = (HashItem*)node->data;
			handle(param,item);
			node = node->next;
		}
	}
}

Hash::Hash(size_t nbuckets)
{
	m_nBuckets = nbuckets;
	m_pTable = new List[m_nBuckets];
	m_nSize = 0;
	m_HashFunc = DefaultHash;
	m_CompareFunc = DefaultCompare;
}

Hash::Hash(HashFunc hashFunc,HashKeyCompareFunc compareFunc,size_t nBuckets)
{
	m_nBuckets = nBuckets;
	m_pTable = new List[m_nBuckets];
	m_nSize = 0;
	m_HashFunc = hashFunc;
	m_CompareFunc = compareFunc;
}
Hash::Hash(HashFunc hashFunc,size_t nBuckets)
{
	m_nBuckets = nBuckets;
	m_pTable = new List[m_nBuckets];
	m_nSize = 0;
	m_HashFunc = hashFunc;
	m_CompareFunc = DefaultCompare;
}

Hash::Hash(HashKeyCompareFunc compareFunc,size_t nBuckets)
{
	m_nBuckets = nBuckets;
	m_pTable = new List[m_nBuckets];
	m_nSize = 0;
	m_HashFunc = DefaultHash;
	m_CompareFunc = compareFunc;
}

Hash::~Hash()
{
	delete[] m_pTable;
}

HashItem* Hash::Begin()
{

	m_IterInfo.Reset();

	if(m_pTable == 0)
		return 0;

	if(m_nSize == 0 || m_nBuckets == 0)
		return 0;

	for(size_t i = 0; i < m_nBuckets; ++i)
	{
        if(m_pTable[i].Size() > 0)
		{
			m_IterInfo.m_nBucketIndex = i;
			m_IterInfo.m_pCurrentNode = m_pTable[i].Head();
			return (HashItem*)(m_IterInfo.m_pCurrentNode->data);
		}
	}

	return 0;
}

HashItem* Hash::End()
{
	return 0;
}

HashItem* Hash::Current()
{
	if(m_IterInfo.Valid() == false)
		return 0;
	return (HashItem*)(m_IterInfo.m_pCurrentNode->data);
}

HashItem* Hash::Next()
{
	if(m_IterInfo.Valid() == false)
		return 0;

	if(m_IterInfo.m_pCurrentNode->next == 0)
	{
		for(size_t i = m_IterInfo.m_nBucketIndex + 1;
				i < m_nBuckets; ++i)
		{
            if(m_pTable[i].Size() > 0)
			{
				m_IterInfo.m_nBucketIndex = i;
                m_IterInfo.m_pCurrentNode = m_pTable[i].Head();
				return (HashItem*)(m_IterInfo.m_pCurrentNode->data);
			}
		}

		if(m_IterInfo.m_nBucketIndex >= m_nBuckets)
		{
			m_IterInfo.Reset();
			return 0;
		}
	}
	else
	{
		m_IterInfo.m_pCurrentNode = m_IterInfo.m_pCurrentNode->next;
		return (HashItem*)(m_IterInfo.m_pCurrentNode->data);
	}
	return 0;
}

HashItem* Hash::Insert(void* key,void* data)
{
	if(0 != Find(key))
		return 0;

	HashItem* item = new HashItem;
	item->key = key;
	item->value = data;
	size_t index = m_HashFunc(key,m_nBuckets);
	
	m_pTable[index].Add((void*)item);

	++m_nSize;
	return item;
}

void Hash::Remove(void* key)
{
	size_t index = m_HashFunc(key,m_nBuckets);
	ListNode* node = m_pTable[index].Head();
	while(node != 0)
	{
		HashItem* item = (HashItem*)node->data;
		if(item == 0)
			continue;
		if(m_CompareFunc(key,item->key))
		{
			m_pTable[index].Remove(node);
			break;
		}
		node = node->next;
	}
}

HashItem* Hash::Find(void* key)
{
	size_t index = m_HashFunc(key,m_nBuckets);
	ListNode* node = m_pTable[index].Head();
	while(node != 0)
	{
		HashItem* item = (HashItem*)node->data;
		if(item == 0)
			continue;
		if(m_CompareFunc(key,item->key))
			return item;
		node = node->next;
	}
	return 0;
}

bool Hash::Empty()
{
	if(0 == m_nSize)
		return true;

	return false;
}

size_t Hash::Size()
{
	return m_nSize;
}


//=======OpenHash=============

OpenHash::OpenHash(size_t nLength)
{
	m_HashFunc = DefaultHash;
	m_CompareFunc = DefaultCompare;
	m_nLength = nLength;
	m_nSize = 0;
	m_pTable = new HashItemWrap[m_nLength];
    m_nCurrentIndex = -1;

}

OpenHash::OpenHash(HashFunc hashFunc,HashKeyCompareFunc compareFunc,size_t nLength)
{
	m_HashFunc = hashFunc;
	m_CompareFunc = compareFunc;
	m_nLength = nLength;
	m_nSize = 0;
	m_pTable = new HashItemWrap[m_nLength];
    m_nCurrentIndex = -1;

}

OpenHash::OpenHash(HashFunc hashFunc,size_t nLength)
{
	m_HashFunc = hashFunc;
	m_CompareFunc = DefaultCompare;
	m_nLength = nLength;
	m_nSize = 0;
	m_pTable = new HashItemWrap[m_nLength];
    m_nCurrentIndex = -1;

}

OpenHash::OpenHash(HashKeyCompareFunc compareFunc,size_t nLength)
{
	m_HashFunc = DefaultHash;
	m_CompareFunc = compareFunc;
	m_nLength = nLength;
	m_nSize = 0;
	m_pTable = new HashItemWrap[m_nLength];
    m_nCurrentIndex = -1;

}
 OpenHash::~OpenHash()
{
	delete[] m_pTable;
}

HashItem* OpenHash::Begin()
{
    m_nCurrentIndex = -1;

	if(m_nSize == 0)
		return 0;

	for(size_t i = 0; i < m_nLength; ++i)
	{
        if(m_pTable[i].exist_flag == false)
            continue;

        m_nCurrentIndex = i;

        return &m_pTable[i].item;
	}
    return 0;
}

HashItem* OpenHash::End()
{
	return 0;
}

HashItem* OpenHash::Current()
{
    if(m_nCurrentIndex < 0 || m_nCurrentIndex >= m_nLength)
        return 0;

    if(m_pTable[m_nCurrentIndex].exist_flag == false)
        return 0;

    return &m_pTable[m_nCurrentIndex].item;
}

HashItem* OpenHash::Next()
{
    for(int i = m_nCurrentIndex + 1; i < m_nLength; ++i)
    {
        if(m_pTable[i].exist_flag == false)
            continue;

        m_nCurrentIndex = i;
        return &m_pTable[i].item;
    }
    m_nCurrentIndex = -1;
    return 0;
}

HashItem* OpenHash::Insert(void* key,void* data)
{
    if(Find(key) != NULL)
        return 0;


    HashItemWrap item;
    item.item.key = key;
    item.item.value = data;
    item.exist_flag = true;

    int position = 0;
    for(size_t i = 0; i < m_nLength; ++i)
    {
        position = (m_HashFunc(key,m_nLength) + (i * DefaultHash2(key,m_nLength))) % m_nLength;

        if(m_pTable[position].exist_flag == true)
            continue;

        ++m_nSize;
        m_pTable[position] = item;
        return &m_pTable[position].item;
    }

    return 0;
}

void OpenHash::Remove(void* key)
{
    if(Find(key) == NULL)
        return ;

    int position = 0;
    for(size_t i = 0; i < m_nLength; ++i)
    {
        position = (m_HashFunc(key,m_nLength) + (i * DefaultHash2(key,m_nLength))) % m_nLength;

        if(m_pTable[position].exist_flag == false)
            continue;


        m_pTable[position].exist_flag = false;
        break;
    }
    --m_nSize;
}

HashItem* OpenHash::Find(void* key)
{
    int position = 0;
    for(size_t i = 0; i < m_nLength; ++i)
    {
        position = (m_HashFunc(key,m_nLength) + (i * DefaultHash2(key,m_nLength))) % m_nLength;

        if(m_pTable[position].exist_flag == false)
            continue;

        if(m_CompareFunc(key,m_pTable[position].item.key))
            return &m_pTable[position].item;
    }
    return 0;
}

bool OpenHash::Empty()
{
	if(0 == m_nSize)
		return true;

	return false;
}

size_t OpenHash::Size()
{
	return m_nSize;
}

