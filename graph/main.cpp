/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月01日 21时56分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */



#include "graph.h"

void Print(void* userData,Vertex* v)
{
    cout << (long)v->data << " ";
}

void PrintEdge(void* userData,Edge* edge)
{
    cout << (long)edge->from->data << "------>" << (long)edge->to->data << " ";
}

void testGraph()
{
    Graph g;

    Vertex* v1 = Graph::CreateVertex();
    v1->data = (void*)1;

    Vertex* v2 = Graph::CreateVertex();
    v2->data = (void*)2;

    Vertex* v3 = Graph::CreateVertex();
    v3->data = (void*)3;

    Vertex* v4 = Graph::CreateVertex();
    v4->data = (void*)4;

    Vertex* v5 = Graph::CreateVertex();
    v5->data = (void*)5;

    Edge* e1 = g.Insert(v1,v2);
    Edge* e2 = g.Insert(v1,v5);
    Edge* e3 = g.Insert(v2,v3);
    Edge* e4 = g.Insert(v2,v4);
    Edge* e5 = g.Insert(v3,v4);
    Edge* e6 = g.Insert(v5,v4);

    g.BFS(Print,0);
    cout << endl;
    g.TraverseVertex(Print,0);
    cout << endl;
    g.TraverseEdge(PrintEdge,0);
    cout << endl;

    cout << "Vertex=" << g.VertexCount() << endl;
    cout << "Edge=" << g.EdgeCount() << endl;

    g.Remove(v1);
    g.TraverseVertex(Print,0);
    cout << endl;
    g.Remove(e5);
    cout << "Vertex=" << g.VertexCount() << endl;
    cout << "Edge=" << g.EdgeCount() << endl;
    g.TraverseEdge(PrintEdge,0);
    cout << endl;

    g.Remove(v2);
    g.TraverseVertex(Print,0);
    cout << endl;
    g.TraverseEdge(PrintEdge,0);
    cout << endl;

    g.Remove(v3);
    g.TraverseVertex(Print,0);
    cout << endl;
    g.TraverseEdge(PrintEdge,0);
    cout << endl;

    g.Remove(v4);
    g.TraverseVertex(Print,0);
    cout << endl;
    g.TraverseEdge(PrintEdge,0);
    cout << endl;


    g.Clear();
}

void testGraphBFS()
{
    Graph g;

    Vertex* v1 = Graph::CreateVertex();
    v1->data = (void*)1;

    Vertex* v2 = Graph::CreateVertex();
    v2->data = (void*)2;

    Vertex* v3 = Graph::CreateVertex();
    v3->data = (void*)3;

    Vertex* v4 = Graph::CreateVertex();
    v4->data = (void*)4;

    Vertex* v5 = Graph::CreateVertex();
    v5->data = (void*)5;

    Vertex* v6 = Graph::CreateVertex();
    v6->data = (void*)6;

    Edge* e1 = g.Insert(v1,v2);
    Edge* e2 = g.Insert(v1,v4);
    Edge* e3 = g.Insert(v1,v5);
    Edge* e4 = g.Insert(v2,v3);
    Edge* e5 = g.Insert(v3,v4);
    Edge* e6 = g.Insert(v1,v6);

    g.BFS(Print,0);
    cout <<endl;
    cout << "DFS:" << endl;
    g.DFS(Print,0);

    List ls;
    g.TopologicalSort(ls);

    cout << endl;
}

int main()
{
    testGraphBFS();

    return 0;
}
