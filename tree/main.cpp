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
#include "tree.h"

void PrintNode(void* userData,AVLTreeNode* node)
{
    cout << (long)node->data << " ";
}


void PrintNode(void* userData,TreeNode* node)
{
    cout << (long)node->data << " ";
}


void testAVLTree()
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
}

void testTree()
{
    Tree t;
    TreeNode* node = 0;
    TreeNode* node0 = t.InsertLeft(node,(void*)0);

    TreeNode* node1 = t.InsertLeft(node0,(void*)1);
    TreeNode* node2 = t.InsertRight(node0,(void*)2);

    TreeNode* node3 = t.InsertLeft(node1,(void*)3);
    TreeNode* node4 = t.InsertRight(node1,(void*)4);

    TreeNode* node5 = t.InsertLeft(node2,(void*)5);
    TreeNode* node6 = t.InsertRight(node2,(void*)6);

    TreeNode* node7 = t.InsertLeft(node3,(void*)7);
    TreeNode* node8 = t.InsertRight(node3,(void*)8);

    TreeNode* node9 = t.InsertLeft(node4,(void*)9);
    TreeNode* node10 = t.InsertRight(node4,(void*)10);

    TreeNode* node11 = t.InsertLeft(node5,(void*)11);
    TreeNode* node12 = t.InsertRight(node5,(void*)12);

    cout << "Size = " << t.Size() << endl;
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;

    PTreeNode parent  = 0;
    PTreeNode nodex = t.Find((void*)10,parent);

    //t.Remove(node1);

    cout << "Size = " << t.Size() << endl;
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;

    //t.RemoveLeft(node2);

    cout << "Size = " << t.Size() << endl;
    t.PreOrderTraverse(PrintNode,0);
    cout << endl;

    cout << "Depth = " << t.Depth(node4) << endl;
    cout << "Depth = " << t.Depth(t.Root()) << endl;

    cout << "Leafs = " << t.Leafs(node2) << endl;
    cout << "Leafs = " << t.Leafs() << endl;
}

int main(int argc, char *argv[])
{

    testTree();


    return 0;
}
