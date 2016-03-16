#ifndef RB_RBTree_H
#define RB_RBTree_H

#include <iostream>
#include <string>

using namespace std;

struct RBTreeNode;

// 树节点数据的比较函数，如果不设置那么就默认按照指针进行比较
typedef int (*RBTreeDataCompareFunc)(void* data1,void* data2);

// 遍历一棵树的处理函数
typedef void (*RBTreeNodeHandle)(void* userData,RBTreeNode* node);


// 红黑树的节点
struct RBTreeNode
{
    enum RBTreeNodeColor
    {
        // 红色
        red,
        // 黑色
        black,
    };

    RBTreeNode()
    {
        data = 0;
        left = 0;
        right = 0;
        parent = 0;
        color = red;
    }

    // 数据
    void* data;
    // 颜色
    int color;
    // 父亲
    struct RBTreeNode* parent;
    // 左孩子
    struct RBTreeNode* left;
    // 右孩子
    struct RBTreeNode* right;

    // 取得以node为根的子树的最小节点
    static RBTreeNode* Mini(RBTreeNode* node)
    {
        if(node == 0)
            return 0;

        while(node->left != 0)
            node =node->left;

        return node;
    }

    // 取得以node为子树的最大节点
    static RBTreeNode* Max(RBTreeNode* node)
    {
        if(node == 0)
            return 0;

        while(node->right != 0)
            node = node->right;

        return node;
    }
};


typedef RBTreeNode* PRBTreeNode;

// 红黑树
class RBTree
{
public:
    RBTree();
    RBTree(RBTreeDataCompareFunc compareFunc);
    ~RBTree();

    RBTreeNode* Root();
    size_t Size();
    bool Empty();
    void Clear();

    // 插入节点
    RBTreeNode* Insert(void* data);

    // 获得最左边的节点
    RBTreeNode* LeftMost();

    // 获得最右边的节点
    RBTreeNode* RightMost();

    // 重新调整平衡
    void ReBalance(RBTreeNode* x);
    // 向左旋转
    void RotateLeft(RBTreeNode* x);
    // 向右旋转
    void RotateRight(RBTreeNode* x);

    // 删除值等于data的节点
    void Remove(void* data);

    // 删除node节点，连同它的子节点
    void Remove(RBTreeNode* node);

    // 删除node节点的左节点（连同它的子节点）
    void RemoveLeft(RBTreeNode* node);
    // 删除node节点的右节点（连同它的子节点）
    void RemoveRight(RBTreeNode* node);

    // 中序递归遍历
    void MidOrderTraverse(RBTreeNodeHandle handle,void* userData,RBTreeNode* node = 0);
    // 前序递归遍历
    void PreOrderTraverse(RBTreeNodeHandle handle,void* userData,RBTreeNode* node = 0);
    // 后续递归遍历
    void PostOrderTraverse(RBTreeNodeHandle handle,void* userData,RBTreeNode* node = 0);

    // 查找
    RBTreeNode* Find(void* data);

    RBTreeNode* Find(void* data,PRBTreeNode& parentNode);

    size_t Depth(RBTreeNode* node = 0);
    size_t Leafs(RBTreeNode* node = 0);
private:
    void ClearRecu(RBTreeNode* node);
    RBTreeNode* FindRecu(RBTreeNode* node,void* data,PRBTreeNode& parentNode);
    // 中序递归遍历
    void MidOrderTraverseRecu(RBTreeNodeHandle handle,void* userData,RBTreeNode* node );
    // 前序递归遍历
    void PreOrderTraverseRecu(RBTreeNodeHandle handle,void* userData,RBTreeNode* node );
    // 后续递归遍历
    void PostOrderTraverseRecu(RBTreeNodeHandle handle,void* userData,RBTreeNode* node );

    size_t DepthRecu(RBTreeNode* node );
    size_t LeafsRecu(RBTreeNode* node );
private:

    // m_pHead的父亲始终指向根节点
    // m_pHead的left指向最左的节点（也就是值最小的节点）
    // m_pHead的right指向最右的节点（也就是值最大的节点）
    RBTreeNode* m_pHead;

    // 红黑树中节点的个数
    size_t m_nSize;

    // 比较函数
    RBTreeDataCompareFunc m_CompareFunc;
};

#endif // RBTree_H
