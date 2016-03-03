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
#include "../stack/stack.h"

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

private:
    // 访问标志，用于DFS或者BFS访问
    bool visit_flag;

private:
    Vertex()
    {
        data = 0;
        color = invalid_color;
        visit_flag = false;
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

    static Vertex* CreateVertex();

    size_t VertexCount();
    size_t EdgeCount();

    Edge* Insert(Vertex* from,Vertex* to,int weight = 0);
    Vertex* Insert(Vertex* v);

    void Remove(Vertex* v);
    void Remove(Edge* edge);

    void TraverseVertex(VertexHandleFunc handle,void* userData);
    void TraverseEdge(EdgeHandleFunc handle,void* userData);

    AdjList* GetAdjList(Vertex* v);

    bool IsAdjacent(Vertex* v1,Vertex* v2);

    Vertex* Find(void* data);
    Vertex* Find(Vertex* v);
    Edge* Find(Edge* edge);
    Edge* Find(void* from,void* to);
    Edge* Find(Vertex* from,Vertex* to);

    void Clear();

    void BFS(VertexHandleFunc handle,void* userData);
    void DFS(VertexHandleFunc handle,void* userData);

    void TopologicalSort(List& ls);

    void HasRing();
private:

    void DFSRecu(AdjList* adj,VertexHandleFunc handle,void* userData);

    void ClearVisitFlag();

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
