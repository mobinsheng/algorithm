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

// 树节点数据的比较函数，如果不设置那么就默认按照指针进行比较
typedef int (*TreeDataCompareFunc)(void* data1,void* data2);

// 遍历一棵树的处理函数
typedef void (*TreeNodeHandle)(void* userData,TreeNode* node);

// 树节点
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
    // 平衡因子
	int factor;
    // 一个隐藏标志，删除节点的时候并不真正删除它，而是把这个节点设置为隐藏
    bool hidden;
};

typedef TreeNode* PTreeNode;

// 节点node的值要大于等于左孩子的值

// 二叉平衡树
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
        void Clear();

        // 插入节点
		TreeNode* Insert(void* data);
        // 删除节点
		void Remove(void* data);

        // 中序递归遍历
        void MidOrderTraverse(TreeNodeHandle handle,void* userData,TreeNode* node = 0);
        // 前序递归遍历
        void PreOrderTraverse(TreeNodeHandle handle,void* userData,TreeNode* node = 0);
        // 后续递归遍历
        void PostOrderTraverse(TreeNodeHandle handle,void* userData,TreeNode* node = 0);

        // 查找
		TreeNode* Find(void* data);

        size_t Depth(TreeNode* node = 0);
        size_t Leafs(TreeNode* node = 0);

	private:

        // 递归插入
        TreeNode* InsertRecu(void* data,PTreeNode& node,bool& isbalanced);
        // 递归查找
        TreeNode* FindRecu(void* data,TreeNode* node);

        // 左旋转
        void RotateLeft(PTreeNode& node);
        // 右旋转
        void RotateRight(PTreeNode& node);

        // 中序递归遍历
        void MidOrderTraverseRecu(TreeNode* node,TreeNodeHandle handle,void* userData);
        // 前序递归遍历
        void PreOrderTraverseRecu(TreeNode* node,TreeNodeHandle handle,void* userData);
        // 后续递归遍历
        void PostOrderTraverseRecu(TreeNode* node,TreeNodeHandle handle,void* userData);

        void ClearRecu(TreeNode* node);

        size_t DepthRecu(TreeNode* node);
        size_t LeafsRecu(TreeNode* node);

    private:
		TreeNode* m_pRoot;
		size_t m_nSize;
		TreeDataCompareFunc m_CompareFunc;
};

#endif
