/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2016年02月28日 14时40分42秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <string>

using namespace std;

struct ListNode
{
public:
    ListNode()
    {
        data = 0;
        prev = 0;
        next = 0;
    }

    struct ListNode* Next()
    {
        return next;
    }

    struct ListNode* Prev()
    {
        return prev;
    }
    void* data;
    struct ListNode* prev;
    struct ListNode* next;
};


class List
{
public:

    List();

    List(const List& ls);

    List& operator=(const List& ls);

    ~List();

    size_t Size();

    bool Empty();

    ListNode* Head();
    ListNode* Tail();

    ListNode* Begin();
    ListNode* End();

    void* Front();
    void* Back();

    void Insert(ListNode* element,void* data);
    void Insert(ListNode* element,ListNode* data);

    void Remove(ListNode* node);
    void Remove(void* data);

    void Clear();

    void Add(void* data);
    void Add(ListNode* node);

    ListNode* Find(void* data);
    bool Find(ListNode* node);
private:
    size_t m_nSize;
    ListNode* m_pHead;
    ListNode* m_pTail;
};

class CList
{
public:
    CList();
    ~CList();

    size_t Size();

    bool Empty();

    ListNode* Head();

    void Insert(ListNode* element,void* data);
    void Insert(ListNode* element,ListNode* data);

    void Remove(ListNode* node);
    void Remove(void* data);

    void Clear();

    void Add(void* data);
    void Add(ListNode* node);

    ListNode* Find(void* data);
    bool Find(ListNode* node);
private:
    size_t m_nSize;
    ListNode* m_pHead;
};
#endif
