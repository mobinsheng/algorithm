
#include "tree.h"

int DefaultTreeNodeCompareFunc(void* data1,void* data2)
{
    if(data1 == data2)
        return 0;

    if(data1 < data2)
        return -1;

    return 1;
}

void DeleteNode(void* userData,TreeNode* node)
{
    delete node;
}

Tree::Tree()
{
    m_nSize = 0;
    m_pRoot = 0;
    m_CompareFunc = DefaultTreeNodeCompareFunc;
}

Tree::Tree(TreeDataCompareFunc compareFunc)
{
    m_nSize = 0;
    m_pRoot = 0;
    m_CompareFunc = compareFunc;
}

Tree::~Tree()
{
    Clear();
}

TreeNode* Tree::Root()
{
    return m_pRoot;
}

size_t Tree::Size()
{
    return m_nSize;
}

bool Tree::Empty()
{
    if(0 == m_nSize)
        return true;

    return false;
}

void Tree::Clear()
{
    ClearRecu(m_pRoot);
    m_pRoot = 0;
    m_nSize = 0;
}

void Tree::ClearRecu(TreeNode *node)
{
    if(node == 0)
        return ;

    ClearRecu(node->left);
    ClearRecu(node->right);
    delete node;
    --m_nSize;
}

// 插入节点
TreeNode* Tree::InsertLeft(PTreeNode& node,void* data)
{
    if(node == 0)
    {
        if(m_pRoot == 0)
        {
            ++m_nSize;
            TreeNode* insertNode = new TreeNode;
            insertNode->data = data;
            m_pRoot = insertNode;
            return insertNode;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(node->left != 0)
            return 0;

        TreeNode* insertNode = new TreeNode;
        insertNode->data = data;
        node->left = insertNode;
        ++m_nSize;
        return insertNode;
    }
}

TreeNode* Tree::InsertRight(PTreeNode& node,void* data)
{
    if(node == 0)
    {
        if(m_pRoot == 0)
        {
            ++m_nSize;
            TreeNode* insertNode = new TreeNode;
            insertNode->data = data;
            m_pRoot = insertNode;
            return insertNode;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(node->right != 0)
            return 0;

        TreeNode* insertNode = new TreeNode;
        insertNode->data = data;
        node->right = insertNode;
        ++m_nSize;
        return insertNode;
    }
}

// 删除值等于data的节点
void Tree::Remove(void* data)
{
    TreeNode* parent = 0;
    TreeNode* node = Find(data,parent);
    if(node == 0)
        return ;

    if(parent->left == node)
        parent->left = 0;
    else
        parent->right = 0;

    ClearRecu(node);
}

// 删除node节点，连同它的子节点
void Tree::Remove(TreeNode* node)
{
    if(node == 0)
        return ;

    TreeNode* parent = 0;

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

TreeNode* Tree::Find(void *data)
{
    PTreeNode node = 0;
    return FindRecu(m_pRoot,data,node);
}

TreeNode* Tree::Find(void *data, PTreeNode &parentNode)
{
    parentNode = 0;
    return FindRecu(m_pRoot,data,parentNode);
}

TreeNode* Tree::FindRecu(TreeNode *node, void *data,PTreeNode& parentNode)
{
    if(node == 0)
    {
        parentNode = 0;
        return 0;
    }

    if(m_CompareFunc(node->data,data) == 0)
        return node;

    parentNode = node;

    TreeNode* temp = FindRecu(node->left,data,parentNode);



    if(0 != temp)
        return temp;

    parentNode = node;

    return FindRecu(node->right,data,parentNode);
}

// 删除node节点的左节点（连同它的子节点）
void Tree::RemoveLeft(TreeNode* node)
{
    if(node == 0)
    {
        if(m_pRoot == 0)
            return ;
        else
        {
            ClearRecu(m_pRoot);
            m_pRoot = 0;
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
void Tree::RemoveRight(TreeNode* node)
{
    if(node == 0)
    {
        if(m_pRoot == 0)
            return ;
        else
        {
            ClearRecu(m_pRoot);
            m_pRoot = 0;
            m_nSize = 0;
        }
    }
    else
    {
        ClearRecu(node->right);
        node->right = 0;
    }
}

void Tree::PreOrderTraverse(TreeNodeHandle handle, void *userData, TreeNode *node)
{
    if(node == 0)
        return PreOrderTraverseRecu(handle,userData,m_pRoot);
    return PreOrderTraverseRecu(handle,userData,node);
}

void Tree::MidOrderTraverse(TreeNodeHandle handle, void *userData, TreeNode *node)
{
    if(node == 0)
        return MidOrderTraverseRecu(handle,userData,m_pRoot);
    return MidOrderTraverseRecu(handle,userData,node);
}

void Tree::PostOrderTraverse(TreeNodeHandle handle, void *userData, TreeNode *node)
{
    if(node == 0)
        return PostOrderTraverseRecu(handle,userData,m_pRoot);
    return PostOrderTraverseRecu(handle,userData,node);
}

void Tree::PreOrderTraverseRecu(TreeNodeHandle handle, void *userData, TreeNode *node)
{
    if(node == 0)
        return ;
    handle(userData,node);
    PreOrderTraverseRecu(handle,userData,node->left);
    PreOrderTraverseRecu(handle,userData,node->right);

}

void Tree::MidOrderTraverseRecu(TreeNodeHandle handle, void *userData, TreeNode *node)
{
    if(node == 0)
        return ;

    MidOrderTraverseRecu(handle,userData,node->left);
    handle(userData,node);
    MidOrderTraverseRecu(handle,userData,node->right);

}

void Tree::PostOrderTraverseRecu(TreeNodeHandle handle, void *userData, TreeNode *node)
{
    if(node == 0)
        return ;

    PostOrderTraverseRecu(handle,userData,node->left);
    PostOrderTraverseRecu(handle,userData,node->right);
    handle(userData,node);
}

size_t Tree::Depth(TreeNode *node)
{
    if(node == 0)
        return DepthRecu(m_pRoot);
    else
        return DepthRecu(node);
}

size_t Tree::DepthRecu(TreeNode *node)
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

size_t Tree::Leafs(TreeNode *node)
{
    if(node == 0)
        return LeafsRecu(m_pRoot);
    else
        return LeafsRecu(node);
}

size_t Tree::LeafsRecu(TreeNode *node)
{
    if(node == 0)
        return 0;

    if(node->left == 0 && node->right == 0)
        return 1;
    else
        return LeafsRecu(node->left) + LeafsRecu(node->right);
}
