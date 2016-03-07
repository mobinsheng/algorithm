#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>

using namespace std;

struct TreeNode;

// 树节点数据的比较函数，如果不设置那么就默认按照指针进行比较
typedef int (*TreeDataCompareFunc)(void* data1,void* data2);

// 遍历一棵树的处理函数
typedef void (*TreeNodeHandle)(void* userData,TreeNode* node);
struct TreeNode
{
    TreeNode()
    {
        data = 0;
        left = 0;
        right = 0;
    }


    void* data;
    struct TreeNode* left;
    struct TreeNode* right;
};


typedef TreeNode* PTreeNode;

class Tree
{
public:
    Tree();
    Tree(TreeDataCompareFunc compareFunc);
    ~Tree();

    TreeNode* Root();
    size_t Size();
    bool Empty();
    void Clear();

    // 插入节点
    TreeNode* InsertLeft(PTreeNode& node,void* data);
    TreeNode* InsertRight(PTreeNode& node,void* data);

    // 删除值等于data的节点
    void Remove(void* data);

    // 删除node节点，连同它的子节点
    void Remove(TreeNode* node);

    // 删除node节点的左节点（连同它的子节点）
    void RemoveLeft(TreeNode* node);
    // 删除node节点的右节点（连同它的子节点）
    void RemoveRight(TreeNode* node);

    // 中序递归遍历
    void MidOrderTraverse(TreeNodeHandle handle,void* userData,TreeNode* node = 0);
    // 前序递归遍历
    void PreOrderTraverse(TreeNodeHandle handle,void* userData,TreeNode* node = 0);
    // 后续递归遍历
    void PostOrderTraverse(TreeNodeHandle handle,void* userData,TreeNode* node = 0);

    // 查找
    TreeNode* Find(void* data);

    TreeNode* Find(void* data,PTreeNode& parentNode);

    size_t Depth(TreeNode* node = 0);
    size_t Leafs(TreeNode* node = 0);
private:
    void ClearRecu(TreeNode* node);
    TreeNode* FindRecu(TreeNode* node,void* data,PTreeNode& parentNode);
    // 中序递归遍历
    void MidOrderTraverseRecu(TreeNodeHandle handle,void* userData,TreeNode* node );
    // 前序递归遍历
    void PreOrderTraverseRecu(TreeNodeHandle handle,void* userData,TreeNode* node );
    // 后续递归遍历
    void PostOrderTraverseRecu(TreeNodeHandle handle,void* userData,TreeNode* node );

    size_t DepthRecu(TreeNode* node );
    size_t LeafsRecu(TreeNode* node );
private:
    TreeNode* m_pRoot;
    size_t m_nSize;
    TreeDataCompareFunc m_CompareFunc;
};

#endif // TREE_H
