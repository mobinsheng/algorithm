/*
 * =====================================================================================
 *
 *       Filename:  graph.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月01日 21时55分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "../list/list.h"
#include "../queue/queue.h"
//#include "../stack/stack.h"

struct Vertex;
struct Edge;
class Graph;
struct AdjList;

typedef bool (*VertexDataCompareFunc)(void* v1,void* v2);
typedef void (*VertexHandleFunc)(void* userData,Vertex* v);
typedef void (*EdgeHandleFunc)(void* userData,Edge* edge);

struct Vertex
{
    friend class Edge;
    friend class Graph;
    friend class AdjList;

    enum
    {
        invalid_color,
        white,
        gray,
        black
    };
    void* data;
    int color;

    // 该顶点所属的邻接表
    AdjList* adjList;
private:
    // 访问标志，用于DFS或者BFS访问
    bool visit_flag;

private:
    Vertex()
    {
        data = 0;
        color = invalid_color;
        visit_flag = false;
        adjList = 0;
    }
};

struct Edge
{
    friend class Vertex;
    friend class Graph;
    friend class AdjList;
    ~Edge()
    {
    }
    Vertex* from;
    Vertex* to;
    // 是否为有向边
    bool direction;
    // 边的权重
    int weight;
private:
    Edge()
    {
        direction = true;
        weight = 0;
        from = 0;
        to = 0;
    }
};

// 一个连接表就表示一个顶点和它的边
struct AdjList
{
    AdjList()
    {
        m_Vertex = 0;
    }

    // 顶点
    Vertex *m_Vertex;
    // 该顶点的边
    List m_EdgeList;

};

class Graph
{
public:
    Graph();
    Graph(VertexDataCompareFunc compareFunc);
    ~Graph();

    // 创建一个顶点
    static Vertex* CreateVertex();

    // 返回顶点的数量
    size_t VertexCount();
    // 返回边的数量
    size_t EdgeCount();

    // 插入一条边
    Edge* Insert(Vertex* from,Vertex* to,int weight = 0);

    // 插入一个顶点
    Vertex* Insert(Vertex* v);

    // 移除一个顶点（并删除和它有关联的所有边）
    void Remove(Vertex* v);

    // 删除一条边
    void Remove(Edge* edge);

    // 遍历顶点
    void TraverseVertex(VertexHandleFunc handle,void* userData);

    // 遍历边
    void TraverseEdge(EdgeHandleFunc handle,void* userData);

    // 判断两个顶点是否相连
    bool IsAdjacent(Vertex* v1,Vertex* v2);

    // 查找顶点
    Vertex* Find(void* data);
    Vertex* Find(Vertex* v);

    // 查找边
    Edge* Find(Edge* edge);
    Edge* Find(void* from,void* to);
    Edge* Find(Vertex* from,Vertex* to);

    // 清理正个图
    void Clear();

    // 广度优先遍历
    void BFS(VertexHandleFunc handle,void* userData);

    // 深度优先遍历
    void DFS(VertexHandleFunc handle,void* userData);

    // 拓扑排序
    void TopologicalSort(List& ls);

    // 判断图是否有环
    bool HasRing();
private:

    // 递归的判断图是否有环
    bool HasRingRecu(AdjList* adjBase,AdjList* adj);

    // 递归的进行深度优先遍历
    void DFSRecu(AdjList* adj,VertexHandleFunc handle,void* userData);

    // 清除正个图所有顶点的访问标志
    void ClearVisitFlag();

    // 插入一条边
    Edge* Insert(Edge* edge);

    VertexDataCompareFunc m_CompareFunc;
    /*
     * m_AdjList中每个节点的data存放着AdjList
     * 而AdjList的m_EdgeList的每个节点的data存放着Edge
     */
    List m_AdjList;
    size_t m_nVertexCount;
    size_t m_nEdgeCount;
};

#endif
