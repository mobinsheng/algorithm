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

struct AVLTreeNode;

// 树节点数据的比较函数，如果不设置那么就默认按照指针进行比较
typedef int (*AVLTreeDataCompareFunc)(void* data1,void* data2);

// 遍历一棵树的处理函数
typedef void (*AVLTreeNodeHandle)(void* userData,AVLTreeNode* node);

// 树节点
struct AVLTreeNode
{
    AVLTreeNode()
	{
		data = 0;
		left = 0;
		right = 0;
		factor = 0;
        hidden = false;
	}
	void* data;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
    // 平衡因子
	int factor;
    // 一个隐藏标志，删除节点的时候并不真正删除它，而是把这个节点设置为隐藏
    bool hidden;
};

typedef AVLTreeNode* PAVLTreeNode;

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
        AVLTree(AVLTreeDataCompareFunc compareFunc);
		~AVLTree();

        AVLTreeNode* Root();
		size_t Size();
		bool Empty();
        void Clear();

        // 插入节点
        AVLTreeNode* Insert(void* data);
        // 删除节点
		void Remove(void* data);

        // 中序递归遍历
        void MidOrderTraverse(AVLTreeNodeHandle handle,void* userData,AVLTreeNode* node = 0);
        // 前序递归遍历
        void PreOrderTraverse(AVLTreeNodeHandle handle,void* userData,AVLTreeNode* node = 0);
        // 后续递归遍历
        void PostOrderTraverse(AVLTreeNodeHandle handle,void* userData,AVLTreeNode* node = 0);

        // 查找
        AVLTreeNode* Find(void* data);

        size_t Depth(AVLTreeNode* node = 0);
        size_t Leafs(AVLTreeNode* node = 0);

	private:

        // 递归插入
        AVLTreeNode* InsertRecu(void* data,PAVLTreeNode& node,bool& isbalanced);
        // 递归查找
        AVLTreeNode* FindRecu(void* data,AVLTreeNode* node);

        // 左旋转
        void RotateLeft(PAVLTreeNode& node);
        // 右旋转
        void RotateRight(PAVLTreeNode& node);

        // 中序递归遍历
        void MidOrderTraverseRecu(AVLTreeNode* node,AVLTreeNodeHandle handle,void* userData);
        // 前序递归遍历
        void PreOrderTraverseRecu(AVLTreeNode* node,AVLTreeNodeHandle handle,void* userData);
        // 后续递归遍历
        void PostOrderTraverseRecu(AVLTreeNode* node,AVLTreeNodeHandle handle,void* userData);

        void ClearRecu(AVLTreeNode* node);

        size_t DepthRecu(AVLTreeNode* node);
        size_t LeafsRecu(AVLTreeNode* node);

    private:
        AVLTreeNode* m_pRoot;
		size_t m_nSize;
        AVLTreeDataCompareFunc m_CompareFunc;
};

#endif
