/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年02月29日 17时13分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "hash.h"

void Print(void* param,HashItem* item)
{
	long key = (long)item->key;
	long value = (long)item->value;

	cout << "Key="<<key<<",value="<<value<<endl;
}

void testHash()
{
    Hash hash;

    for(int i = 0; i < 10; ++i)
    {
        hash.Insert((void*)i,(void*)i);
    }

    hash.Traversal(Print,0);
    cout <<"===================="<<endl;
    for(int i = 8; i < 16; ++i)
    {
        hash.Insert((void*)i,(void*)i);

    }
    hash.Traversal(Print,0);
    cout << "===================="<<endl;
    cout << "Size="<<hash.Size()<<endl;
    for(int i = 5; i < 10; ++i)
    {
        hash.Remove((void*)i);
    }
    hash.Traversal(Print,0);
    cout << "====================" <<endl;
    HashItem* item = hash.Find((void*)4);
    if(0 != item)
    {
        cout << "Find key:" << (long)item->key<<endl;
    }

    cout << "========================" <<endl;
    item = 0;
    for(item = hash.Begin(); item != hash.End(); item = hash.Next())
    {
        long key = (long)item->key;
        long value = (long)item->value;

        cout << "Key="<<key<<",value="<<value<<endl;
    }
}

void testOpenHash()
{
    OpenHash hash(256);

    HashItem* item = 0;

    for(int i = 0; i < 10; ++i)
    {
        hash.Insert((void*)i,(void*)i);
    }

    for(item = hash.Begin(); item != hash.End(); item = hash.Next())
    {
        long key = (long)item->key;
        long value = (long)item->value;

        cout << "Key="<<key<<",value="<<value<<endl;
    }

    cout <<"===================="<<endl;
    for(int i = 8; i < 200; ++i)
    {
        hash.Insert((void*)i,(void*)i);

    }

    for(item = hash.Begin(); item != hash.End(); item = hash.Next())
    {
        long key = (long)item->key;
        long value = (long)item->value;

        cout << "Key="<<key<<",value="<<value<<endl;
    }

    cout << "===================="<<endl;
    cout << "Size="<<hash.Size()<<endl;
    for(int i = 5; i < 10; ++i)
    {
        hash.Remove((void*)i);
    }

    for(item = hash.Begin(); item != hash.End(); item = hash.Next())
    {
        long key = (long)item->key;
        long value = (long)item->value;

        cout << "Key="<<key<<",value="<<value<<endl;
    }

    cout << "====================" <<endl;
    item = hash.Find((void*)4);
    if(0 != item)
    {
        cout << "Find key:" << (long)item->key<<endl;
    }

    cout << "========================" <<endl;
    item = 0;
    for(item = hash.Begin(); item != hash.End(); item = hash.Next())
    {
        long key = (long)item->key;
        long value = (long)item->value;

        cout << "Key="<<key<<",value="<<value<<endl;
    }

    cout << "Size="<<hash.Size()<<endl;
}

int main()
{

    testOpenHash();;

	return 0;
}
