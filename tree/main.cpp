/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月01日 20时03分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "AVLTree.h"

void PrintNode(void* userData,TreeNode* node)
{
    cout << (long)node->data << " ";
}

int main(int argc, char *argv[])
{

    AVLTree t;
    /*for(int i = 5; i < 10; ++i)
        t.Insert((void*)i);

    for(int i = 0; i < 5; ++i)
        t.Insert((void*)i);*/
    t.Insert((void*)1);
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;
    t.Insert((void*)2);
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;
    t.Insert((void*)3);
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;
    t.Insert((void*)4);
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;
    t.Insert((void*)5);
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;
    t.Insert((void*)6);
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;
    t.Insert((void*)7);
    t.Insert((void*)6);

    t.PreOrderTraverse(PrintNode,0);
    cout << endl;

    cout << "Depth="<<t.Depth() << endl;
    cout << "Leafs=" << t.Leafs() << endl;
    ///
    t.Remove((void*)6);
    t.MidOrderTraverse(PrintNode,0);
    cout << endl;

    t.Remove((void*)4);
    t.MidOrderTraverse(PrintNode,0);
    cout << endl;

    t.Remove((void*)2);
    t.MidOrderTraverse(PrintNode,0);
    cout << endl;


    return 0;
}
