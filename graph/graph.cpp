/*
 * =====================================================================================
 *
 *       Filename:  graph.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月01日 21时56分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "graph.h"

bool DefaultVertexDataCompare(void* v1,void* v2)
{
    if(v1 == v2)
        return true;

    return false;
}

// 顶点的内存必须由图创建
// 这样才能更好地管理内存
// 用户只需要申请即可，释放交给graph进行
Vertex* Graph::CreateVertex()
{
    return new Vertex;
}

Graph::Graph()
{
    m_nEdgeCount = 0;
    m_nVertexCount = 0;
    m_CompareFunc = DefaultVertexDataCompare;
}

Graph::Graph(VertexDataCompareFunc compareFunc)
{
    m_nEdgeCount = 0;
    m_nVertexCount = 0;
    m_CompareFunc = compareFunc;
}

Graph::~Graph()
{

}

Edge* Graph::Insert(Edge *edge)
{
    if(Find(edge) != 0)
        return 0;

    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;
        if(adj == 0)
            continue;

        if(m_CompareFunc(edge->from->data,adj->m_Vertex->data))
        {
            adj->m_EdgeList.Add(edge);
            ++m_nEdgeCount;
            return edge;
        }
    }

    return 0;
}

// 插入一个节点
Vertex* Graph::Insert(Vertex *v)
{
    if(v == 0)
        return 0;

    // 查找该顶点是否已经存在
    Vertex* ret = Find(v->data);

    // 如果已经存在，那么不能再插入
    if(ret != 0)
        return 0;

    // 不存在

    AdjList* adj = new AdjList;
    adj->m_Vertex = v;
    v->adjList = adj;

    m_AdjList.Add(adj);
    ++m_nVertexCount;

    return v;
}

// 根据两个顶点插入一条边
Edge* Graph::Insert(Vertex *from, Vertex *to,int weight)
{
    if(0 == from || 0 == to)
        return 0;

    Vertex* tempFrom = Find(from->data);
    Vertex* tempTo = Find(to->data);

    // 如果该顶点不在图中，那么插入
    if(tempFrom == 0)
    {
        Insert(from);
    }

    // 如果该顶点不在图中，那么插入
    if(tempTo == 0)
    {
        Insert(to);
    }

    // 构造一条边
    Edge* edge = new Edge;
    edge->from = from;
    edge->to = to;
    edge->weight = weight;

    // 插入
    if(Insert(edge)  == 0)
    {
        // 如果插入失败，那么删除刚刚构造的那条边
        delete edge;
        return 0;
    }

    return edge;

}

// 根据顶点的值查找一个顶点
Vertex* Graph::Find(void *data)
{
    ListNode* node = 0;
    for(node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;
        if(adj == 0)
            continue;

        if(m_CompareFunc(adj->m_Vertex->data,data))
            return adj->m_Vertex;
    }

    return 0;
}

// 查找某个顶点是否存在
Vertex* Graph::Find(Vertex *v)
{
    ListNode* node = 0;
    for(node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;
        if(adj == 0)
            continue;

        if(m_CompareFunc(adj->m_Vertex->data,v->data))
            return adj->m_Vertex;
    }

    return 0;
}

Edge* Graph::Find(Edge* edge)
{
    if(edge == 0)
        return 0;

    return Find(edge->from->data,edge->to->data);
}

Edge* Graph::Find(void* from,void* to)
{
    if(from == 0 || to == 0)
        return 0;

    ListNode* node = 0;
    for(node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;
        if(adj == 0)
            continue;

        //  找到该点所在的邻接表
        if(m_CompareFunc(from,adj->m_Vertex->data))
        {
            ListNode* e = 0;

            // 遍历这个点的所有边
            for(e = adj->m_EdgeList.Begin(); e != adj->m_EdgeList.End(); e = e->Next())
            {
                Edge* eg = (Edge*)e->data;
                if(eg == 0)
                    continue;

                if(m_CompareFunc(to,eg->to->data))
                        return eg;
            }
        }
    }

    return 0;
}

Edge* Graph::Find(Vertex* from,Vertex* to)
{
    if(from == 0 || to == 0)
        return 0;
    return Find(from->data,to->data);
}

size_t Graph::EdgeCount()
{
    return m_nEdgeCount;
}

size_t Graph::VertexCount()
{
    return m_nVertexCount;
}

// 删除某一条边
void Graph::Remove(Edge *edge)
{
    if(Find(edge) == 0)
        return;

    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;

        if(adj == 0)
            continue;

        if(m_CompareFunc(edge->from->data,adj->m_Vertex->data) == false)
            continue;

        for(ListNode* e = adj->m_EdgeList.Begin(); e != adj->m_EdgeList.End(); e = e->Next())
        {
            Edge* eg = (Edge*)e->data;

            if(eg == 0)
                continue;

            if(false == m_CompareFunc(eg->to->data,edge->to->data))
                continue;

            adj->m_EdgeList.Remove(e);

            --m_nEdgeCount;

            delete eg;

            break;

        }
    }

}

void Graph::Remove(Vertex *v)
{
    if(0 == v)
        return;

    // 删除所有指向该节点的边
    for(ListNode* node= m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;

        if(adj == 0)
            continue;

        if(m_CompareFunc(v->data,adj->m_Vertex->data))
            continue;

        for(ListNode* e = adj->m_EdgeList.Begin(); e != adj->m_EdgeList.End(); e = e->Next())
        {
            Edge* eg = (Edge*)e->data;
            if(eg == 0)
                continue;

            if(m_CompareFunc(eg->to->data,v->data))
            {
                delete eg;
                adj->m_EdgeList.Remove(e);
                --m_nEdgeCount;
                break;
            }
        }
    }

    // 删除该节点指向其他节点的所有的边
    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;

        if(adj == 0)
            continue;

        if(m_CompareFunc(v->data,adj->m_Vertex->data) == false)
            continue;

        // 找到了该节点

        // 遍历该节点指向其他节点的边
        for(ListNode* e = adj->m_EdgeList.Begin(); e != adj->m_EdgeList.End(); e = e->Next())
        {
            Edge* eg = (Edge*)e->data;

            if(eg == 0)
                continue;

            --m_nEdgeCount;
            // 删除边的内存
            delete eg;
        }

        // 清理这个节点的边列表
        adj->m_EdgeList.Clear();

        // 删除邻接表的内存
        delete adj;

        // 移除该节点
        m_AdjList.Remove(node);

        --m_nVertexCount;

        break;
    }

    // 删除这个节点的内存，因为这个节点的内存是由graph分配的
    delete v;
}

void Graph::TraverseVertex(VertexHandleFunc handle,void* userData)
{
    if(handle == 0)
        return;

    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;

        if(adj == 0)
            continue;

        handle(userData,adj->m_Vertex);
    }
}


void Graph::TraverseEdge(EdgeHandleFunc handle,void* userData)
{
    if(handle == 0)
        return;

    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;

        if(adj == 0)
            continue;

        for(ListNode * e = adj->m_EdgeList.Begin(); e != adj->m_EdgeList.End(); e = e->Next())
        {
            Edge* eg = (Edge*)e->data;
            if(eg == 0)
                continue;
            handle(userData,eg);
        }
    }
}

void Graph::Clear()
{
    while(m_AdjList.Empty() == false)
    {
        ListNode* node = m_AdjList.Begin();
        AdjList* adj = (AdjList*)node->data;
        Remove((Vertex*)adj->m_Vertex);
    }

    m_AdjList.Clear();
}
/*
AdjList* Graph::GetAdjList(Vertex *v)
{
    if(v == 0)
        return 0;

    return v->adjList;
    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;
        if(adj == 0)
            continue;

        if(m_CompareFunc(adj->m_Vertex->data,v->data))
            return adj;
    }
    return 0;
}
*/
bool Graph::IsAdjacent(Vertex *v1, Vertex *v2)
{
    if(Find(v1,v2))
        return true;

    return Find(v2,v1);
}

void Graph::BFS(VertexHandleFunc handle, void *userData)
{
    if(m_AdjList.Size() == 0)
        return;

    Queue Q;
    ListNode* node = m_AdjList.Begin();
    AdjList* adj = (AdjList*)node->data;

    Q.EnQueue(adj);

    while(Q.Empty() == false)
    {
        adj = (AdjList*)Q.DeQueue();
        if(adj == 0)
            continue;

        if(adj->m_Vertex->visit_flag == false)
        {
            handle(userData,adj->m_Vertex);
            adj->m_Vertex->visit_flag = true;
        }

        for(node = adj->m_EdgeList.Begin(); node != adj->m_EdgeList.End(); node = node->Next())
        {
            Edge* eg = (Edge*)node->data;
            if(eg == 0)
                continue;

            AdjList* vertexAdj = eg->to->adjList;

            if(vertexAdj->m_Vertex->visit_flag == true)
                continue;

            Q.EnQueue(vertexAdj);
        }
    }

    ClearVisitFlag();
}

void Graph::DFS(VertexHandleFunc handle, void *userData)
{
    if(m_AdjList.Size() == 0  || handle == 0)
        return;

    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node =node->Next())
    {
        AdjList* adj = (AdjList*)node->data;
        if(adj == 0 || adj->m_Vertex->visit_flag == true)
            continue;

        DFSRecu(adj,handle,userData);
    }

    ClearVisitFlag();
}

void Graph::DFSRecu(AdjList* adj,VertexHandleFunc handle, void *userData)
{
    if(adj == 0 || handle == 0)
        return;

    if(adj->m_Vertex->visit_flag == true)
        return;
    else
    {
        handle(userData,adj->m_Vertex);
        adj->m_Vertex->visit_flag = true;
    }

    for(ListNode* node = adj->m_EdgeList.Begin(); node != adj->m_EdgeList.End(); node = node->Next())
    {
        Edge* eg = (Edge*)node->data;
        AdjList* vertexAdj = eg->to->adjList;
        if(vertexAdj == 0)
            continue;
        if(vertexAdj->m_Vertex->visit_flag == true)
            continue;
        DFSRecu(vertexAdj,handle,userData);
    }

}

void HelpInsert(void* userData,Vertex* v)
{
    if(userData == 0)
        return ;
    List* ls = (List*)userData;

    ls->Add(v->data);
}

void Graph::TopologicalSort(List &ls)
{
    DFS(HelpInsert,(void*)&ls);
}

bool Graph::HasRing()
{
    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        ClearVisitFlag();

        AdjList* adj = (AdjList*)node->data;

        if(adj->m_EdgeList.Size() == 0)
            continue;

        adj->m_Vertex->visit_flag = true;

        for(ListNode* e = adj->m_EdgeList.Begin(); e != adj->m_EdgeList.End(); e = e->Next())
        {
            Edge* eg = (Edge*)e->data;
            if(HasRingRecu(adj,eg->to->adjList))
                return true;

        }
    }

    ClearVisitFlag();

    return false;
}

bool Graph::HasRingRecu(AdjList *adjBase, AdjList *adj)
{
    if(adjBase == adj || adj->m_Vertex->visit_flag == true)
        return true;

    if(adj->m_EdgeList.Size() == 0)
        return false;

    adj->m_Vertex->visit_flag = true;

    Edge* eg = (Edge*)adj->m_EdgeList.Begin()->data;

    return HasRingRecu(adjBase,eg->to->adjList);

}

void Graph::ClearVisitFlag()
{
    for(ListNode* node = m_AdjList.Begin(); node != m_AdjList.End(); node = node->Next())
    {
        AdjList* adj = (AdjList*)node->data;
        if(adj == 0)
            continue;
        adj->m_Vertex->visit_flag = false;
    }
}
