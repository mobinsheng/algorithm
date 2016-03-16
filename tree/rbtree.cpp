
#include "rbtree.h"

// 默认的节点值比较函数
int DefaultRBTreeNodeCompareFunc(void* data1,void* data2)
{
    if(data1 == data2)
        return 0;

    if(data1 < data2)
        return -1;

    return 1;
}

RBTree::RBTree()
{
    m_pHead = new RBTreeNode;
    m_pHead->color = RBTreeNode::red;
    m_pHead->left = m_pHead;
    m_pHead->right = m_pHead;
    m_pHead->parent = 0;

    m_nSize = 0;

    m_CompareFunc = DefaultRBTreeNodeCompareFunc;
}

RBTree::RBTree(RBTreeDataCompareFunc compareFunc)
{
    m_nSize = 0;

    m_pHead = new RBTreeNode;
    m_pHead->color = RBTreeNode::red;
    m_pHead->left = m_pHead;
    m_pHead->right = m_pHead;
    m_pHead->parent = 0;

    m_CompareFunc = compareFunc;
}

RBTree::~RBTree()
{
    Clear();
    delete m_pHead;
}

RBTreeNode* RBTree::Root()
{
    return m_pHead->parent;
}

RBTreeNode* RBTree::LeftMost()
{
    return m_pHead->left;
}

RBTreeNode* RBTree::RightMost()
{
    return m_pHead->right;
}

size_t RBTree::Size()
{
    return m_nSize;
}

bool RBTree::Empty()
{
    if(0 == m_nSize)
        return true;

    return false;
}

void RBTree::Clear()
{
    ClearRecu(m_pHead->parent);

    m_pHead->color = RBTreeNode::red;
    m_pHead->left = m_pHead;
    m_pHead->right = m_pHead;
    m_pHead->parent = 0;
    m_nSize = 0;
}

void RBTree::ClearRecu(RBTreeNode *node)
{
    if(node == 0)
        return ;

    ClearRecu(node->left);
    ClearRecu(node->right);
    delete node;
    --m_nSize;
}

// 节点node的值要大于等于左孩子的值
// 插入节点
RBTreeNode* RBTree::Insert(void* data)
{
    RBTreeNode* insertNode = new RBTreeNode;
    insertNode->data = data;
    // 新插入节点的颜色是红色的
    insertNode->color = RBTreeNode::red;

    ++m_nSize;

    // 如果根节点为空，那么把当前节点设置为根节点
    // 把颜色调整为黑，因为红黑树的根是黑色的
    if(m_pHead->parent == 0)
    {
        m_pHead->parent = insertNode;
        m_pHead->parent->color = RBTreeNode::black;

        m_pHead->left = insertNode;
        m_pHead->right = insertNode;
    }
    else
    {
        RBTreeNode* node = m_pHead->parent;
        RBTreeNode* currentpNode = node;

        while(node != 0)
        {
            currentpNode = node;

            int compareRet = m_CompareFunc(node->data,data);

            if(compareRet < 0)
            {
                node = node->right;
            }
            else
            // compareRet >= 0
            {
                node = node->left;
            }
        }

        if(m_CompareFunc(currentpNode->data,data) < 0)
        {
            currentpNode->right = insertNode;
            insertNode->parent = currentpNode;

            if(RightMost() == currentpNode)
                m_pHead->right = insertNode;
        }
        else
        {
            currentpNode->left = insertNode;
            insertNode->parent = currentpNode;

            if(LeftMost() == currentpNode)
                m_pHead->left = insertNode;
        }
    }

    // 插入好了
    // 接下来需要进行调整
    ReBalance(insertNode);
}

// 红黑树的特点：
// （1）根节点是黑色的
// （2）父子节点不能同时是红色（即如果父亲节点是红色，那么子节点必须是黑色）
// （3）任一节点到NULL（即树尾端）的任何路径包含的黑色节点个数都相同

// 假设插入节点是X，X的父亲节点是P，X的祖父是G，X的曾祖父是GG，X的伯父或者叔叔（即P的兄弟）是S
// 有四种情况：
// 1、如果P的颜色是黑色，插入之后可以直接返回
// 2、如果P的颜色是红色，那么进行如下处理
// 2.1、S是黑色：
// 2.1.1、LL：如果X是外侧插入，直接进行LL旋转（对P和G），改变P和G的颜色（P改成黑，G改成红色）
// 2.1.2、LR：如果X是内侧插入，进行LR旋转，先对P、X进行旋转，然后改变G和X的颜色（G改成红色，X改成黑色）
//           再对G进行旋转
// 2.2、S是红色：
// 2.2.1、LL：如果X是外侧插入，直接进行LL旋转（对P和G），改变X的颜色（变成黑色），如果GG是黑色，那么完成
//           否则还需要继续向上处理
//


/*
 * 预处理过程：
 * 从某个节点依次向上，如果遇到某个节点X的两个子节点的颜色都是红色
 * 那么把X两个子节点的颜色改成黑色，X的颜色改成红色，然后继续向上
 * 如果变换之后，X的父亲和X都是红色（那此时X的祖父必是黑色，因为X的父亲是红色），
 * 如果此时X的兄弟是红色，那么可以继续向上处理（因为符合P的两个子节点都是红色这一条件）
 * 如果此时X的兄弟是黑色（那么不满足继续向上的条件了），需要进行旋转
 * 那么对X的父亲进行旋转即可，这里只需要一个LL（或RR）或LR（或RL）旋转即可，而不需要进行多次的向上遍历然后旋转
 */

void RBTree::ReBalance(RBTreeNode *x)
{
    // 插入节点的起始颜色都是红色
    x->color = RBTreeNode::red;

    // 如果P的颜色是黑色，对应情况1，不会进入循环

    // 一直从x向上遍历，直到到达根节点
    while(x != m_pHead->parent && x->parent->color == RBTreeNode::red)
    {
        // P的颜色是红色！！！


        // 如果P是G的左孩子
        if(x->parent == x->parent->parent->left)
        {
            // 取得S
            RBTreeNode* uncle = x->parent->parent->right;

            // S的颜色是红色
            if(uncle && uncle->color == RBTreeNode::red)
            {
                // 这是预处理过程

                // P的颜色设置为黑色
                x->parent->color = RBTreeNode::black;
                // S的颜色设置为黑色
                uncle->color = RBTreeNode::black;
                // G的颜色设置为红色
                x->parent->parent->color = RBTreeNode::red;
                // 然后把X向上移动到G，继续向上遍历，这是一个自下而上的预处理过程
                x = x->parent->parent;
            }
            else
            // S的颜色是黑色
            {
                // 如果X是P的右孩子，而P是G的左孩子，那么将进行LR旋转
                // LR选择即先左旋转，再右旋转
                if(x == x->parent->right)
                {
                    x = x->parent;
                    RotateLeft(x);
                }

                // 如果X是P的左孩子，而P是G的左孩子，那么将进行LL旋转（直接右旋转即可）
                // P的颜色变为黑色
                x->parent->color = RBTreeNode::black;
                // G的颜色变为红色
                x->parent->parent->color = RBTreeNode::red;
                // 进行旋转
                RotateRight(x->parent->parent);
            }
        }
        else
        // 如果P是G的右孩子
        {
            RBTreeNode* uncle = x->parent->parent->left;

            // S的颜色是红色
            if(uncle && uncle->color == RBTreeNode::red)
            {
                // 这是预处理过程


                // P的颜色设置为黑色
                x->parent->color = RBTreeNode::black;
                // S的颜色设置为黑色
                uncle->color = RBTreeNode::black;
                // G的颜色设置为红色
                x->parent->parent->color = RBTreeNode::red;
                // 把X移动到G，依次向上处理，这是一个子下而上的预处理过程
                x = x->parent->parent;
            }
            else
            // S的颜色是黑色
            {
                // 如果X是P的左孩子，而P是G的右孩子，那么需要进行RL旋转（先右旋转，再左旋转）
                if(x == x->parent->left)
                {
                    x =x->parent;
                    RotateRight(x);
                }
                // 如果X是P的右孩子，那么直接进行RR旋转即可（即进行左旋转）
                // P的颜色改成黑色
                x->parent->color = RBTreeNode::black;
                // G的颜色改成红色
                x->parent->parent->color = RBTreeNode::red;
                // 旋转
                RotateLeft(x->parent->parent);
            }
        }
    }

    m_pHead->parent->color = RBTreeNode::black;
}

// 左旋转（以X为中间进行逆时针旋转）
// 旋转之后，X的右孩子right取代X的位置，而X则成为right的左孩子
// 因此right的左孩子应该成为X的右孩子
void RBTree::RotateLeft(RBTreeNode *x)
{
    // 取得x的左孩子
    RBTreeNode* right = x->right;

    // x的右孩子应该是right的左孩子
    x->right =right->left;

    if(right->left != 0)
    {
        // right的左孩子的父亲是x
        right->left->parent = x;
    }

    // right的父亲是x原来的父亲
    right->parent = x->parent;

    if(x == m_pHead->parent)
    {
        m_pHead->parent = right;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = right;
    }
    else
    {
        x->parent->right = right;
    }

    // x变成right的左孩子
    right->left = x;
    x->parent = right;
}

// 右旋转（以X为中心，按照顺时针进行旋转）
// 旋转之后X的左孩子left取代X的位置，X成为left的右孩子
// left原来的右孩子变成X的左孩子
void RBTree::RotateRight(RBTreeNode *x)
{
    RBTreeNode* left = x->left;
    x->left =left->right;

    if(left->right != 0)
    {
        left->right->parent = x;
    }

    left->parent = x->parent;

    if(x == m_pHead->parent)
    {
        m_pHead->parent = left;
    }
    else if(x == x->parent->right)
    {
        x->parent->right = left;
    }
    else
    {
        x->parent->left = left;
    }

    left->right = x;
    x->parent = left;
}

// 删除值等于data的节点
void RBTree::Remove(void* data)
{
    RBTreeNode* parent = 0;
    RBTreeNode* node = Find(data,parent);
    if(node == 0)
        return ;

    if(parent->left == node)
        parent->left = 0;
    else
        parent->right = 0;

    ClearRecu(node);
}

// 删除node节点，连同它的子节点
void RBTree::Remove(RBTreeNode* node)
{
    if(node == 0)
        return ;

    RBTreeNode* parent = 0;

    node = Find(node->data,parent);

    if(node == 0)
        return ;

    if(parent == 0)
    {
        Clear();
        return;
    }

    if(parent->left == node)
        parent->left = 0;
    else
        parent->right = 0;

    ClearRecu(node);
}

RBTreeNode* RBTree::Find(void *data)
{
    PRBTreeNode node = 0;
    return FindRecu(m_pHead->parent,data,node);
}

RBTreeNode* RBTree::Find(void *data, PRBTreeNode &parentNode)
{
    parentNode = 0;
    return FindRecu(m_pHead->parent,data,parentNode);
}

RBTreeNode* RBTree::FindRecu(RBTreeNode *node, void *data,PRBTreeNode& parentNode)
{
    if(node == 0)
    {
        parentNode = 0;
        return 0;
    }

    if(m_CompareFunc(node->data,data) == 0)
        return node;

    parentNode = node;

    RBTreeNode* temp = FindRecu(node->left,data,parentNode);



    if(0 != temp)
        return temp;

    parentNode = node;

    return FindRecu(node->right,data,parentNode);
}

// 删除node节点的左节点（连同它的子节点）
void RBTree::RemoveLeft(RBTreeNode* node)
{
    if(node == 0)
    {
        if(m_pHead->parent == 0)
            return ;
        else
        {
            ClearRecu(m_pHead->parent);
            m_pHead->parent = 0;
            m_nSize = 0;
        }
    }
    else
    {
        ClearRecu(node->left);
        node->left = 0;
    }
}

// 删除node节点的右节点（连同它的子节点）
void RBTree::RemoveRight(RBTreeNode* node)
{
    if(node == 0)
    {
        if(m_pHead->parent == 0)
            return ;
        else
        {
            ClearRecu(m_pHead->parent);
            m_pHead->parent = 0;
            m_nSize = 0;
        }
    }
    else
    {
        ClearRecu(node->right);
        node->right = 0;
    }
}

void RBTree::PreOrderTraverse(RBTreeNodeHandle handle, void *userData, RBTreeNode *node)
{
    if(node == 0)
        return PreOrderTraverseRecu(handle,userData,m_pHead->parent);
    return PreOrderTraverseRecu(handle,userData,node);
}

void RBTree::MidOrderTraverse(RBTreeNodeHandle handle, void *userData, RBTreeNode *node)
{
    if(node == 0)
        return MidOrderTraverseRecu(handle,userData,m_pHead->parent);
    return MidOrderTraverseRecu(handle,userData,node);
}

void RBTree::PostOrderTraverse(RBTreeNodeHandle handle, void *userData, RBTreeNode *node)
{
    if(node == 0)
        return PostOrderTraverseRecu(handle,userData,m_pHead->parent);
    return PostOrderTraverseRecu(handle,userData,node);
}

void RBTree::PreOrderTraverseRecu(RBTreeNodeHandle handle, void *userData, RBTreeNode *node)
{
    if(node == 0)
        return ;
    handle(userData,node);
    PreOrderTraverseRecu(handle,userData,node->left);
    PreOrderTraverseRecu(handle,userData,node->right);

}

void RBTree::MidOrderTraverseRecu(RBTreeNodeHandle handle, void *userData, RBTreeNode *node)
{
    if(node == 0)
        return ;

    MidOrderTraverseRecu(handle,userData,node->left);
    handle(userData,node);
    MidOrderTraverseRecu(handle,userData,node->right);

}

void RBTree::PostOrderTraverseRecu(RBTreeNodeHandle handle, void *userData, RBTreeNode *node)
{
    if(node == 0)
        return ;

    PostOrderTraverseRecu(handle,userData,node->left);
    PostOrderTraverseRecu(handle,userData,node->right);
    handle(userData,node);
}

size_t RBTree::Depth(RBTreeNode *node)
{
    if(node == 0)
        return DepthRecu(m_pHead->parent);
    else
        return DepthRecu(node);
}

size_t RBTree::DepthRecu(RBTreeNode *node)
{
    if(node == 0)
        return 0;

    if(node->left == 0 && node->right == 0)
        return 1;

    int leftDepth = DepthRecu(node->left);
    int rightDepth = DepthRecu(node->right);

    if(leftDepth > rightDepth)
        return leftDepth + 1;
    else
        return rightDepth + 1;

}

size_t RBTree::Leafs(RBTreeNode *node)
{
    if(node == 0)
        return LeafsRecu(m_pHead->parent);
    else
        return LeafsRecu(node);
}

size_t RBTree::LeafsRecu(RBTreeNode *node)
{
    if(node == 0)
        return 0;

    if(node->left == 0 && node->right == 0)
        return 1;
    else
        return LeafsRecu(node->left) + LeafsRecu(node->right);
}
