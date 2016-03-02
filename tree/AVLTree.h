/*
 * =====================================================================================
 *
 *       Filename:  AVLTree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月01日 20时03分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <iostream>
#include <string>

using namespace std;

struct TreeNode;

typedef int (*TreeDataCompareFunc)(void* data1,void* data2);
typedef void (*TreeNodeHandle)(TreeNode* node);

struct TreeNode
{
	TreeNode()
	{
		data = 0;
		left = 0;
		right = 0;
		factor = 0;
        hidden = false;
	}
	void* data;
	struct TreeNode* left;
	struct TreeNode* right;
	int factor;
    bool hidden;
};

typedef TreeNode* PTreeNode;

// 节点node的值要大于等于左孩子的值
class AVLTree
{
	public:
		enum
		{
			left_heavy = 1,
			balanced = 0,
			right_heavy = -1,
		};

        AVLTree();
        AVLTree(TreeDataCompareFunc compareFunc);
		~AVLTree();
		TreeNode* Root();
		size_t Size();
		bool Empty();

		TreeNode* Insert(void* data);
		void Remove(void* data);

        void MidOrderTraverseRecu(TreeNode* node,TreeNodeHandle handle);
        void PreOrderTraverseRecu(TreeNode* node,TreeNodeHandle handle);
        void PostOrderTraverseRecu(TreeNode* node,TreeNodeHandle handle);

		TreeNode* Begin();
		TreeNode* End();
		TreeNode* Next();

		TreeNode* Find(void* data);
	private:
        TreeNode* InsertRecu(void* data,PTreeNode& node,bool& isbalanced);
        TreeNode* FindRecu(void* data,TreeNode* node);
        void RotateLeft(PTreeNode& node);
        void RotateRight(PTreeNode& node);
    private:
		TreeNode* m_pRoot;
		size_t m_nSize;
		size_t m_nDepth;
		TreeDataCompareFunc m_CompareFunc;
};

#endif
