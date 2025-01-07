
#include <cassert>

#include "Graph.h"
#include "MyString.h"

#include "PrintArray.h"
#include "PrintAdjacencyMatrix.h"

void TestGraphConstructor()
{
    Graph<int, int, int> graph(GetHashCodeInt);
    assert(graph.GetLength() == 0);

    Graph<MyString, int, double> graph2(GetHashCodeMyString);
    assert(graph.GetLength() == 0);
}

void TestGraphAddVertex()
{
    {
        Graph<int, int, int> graph(GetHashCodeInt);

        graph.AddVertex(0, 8800555);
        assert(graph.GetLength() == 1);

        graph.AddVertex(1, -9088);
        assert(graph.GetLength() == 2);

        graph.AddVertex(133232, 0);
        assert(graph.GetLength() == 3);

        assert(graph.Get(0).Get().GetData() == 8800555);

        assert(graph.Get(1).Get().GetData() == -9088);

        assert(graph.Get(133232).Get().GetData() == -0);

        try{
            assert(graph.Get(-1234).Get().GetData() == -0); // we have not added vertex with this index
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }
        
    }
    {
        Graph<MyString, int, double> graph(GetHashCodeMyString);
        
        graph.AddVertex("First Vertex", 444);
        assert(graph.GetLength() == 1);

        graph.AddVertex("Second DADR 0030430//posod", 1234);
        assert(graph.GetLength() == 2);

        graph.AddVertex("", 444);
        assert(graph.GetLength() == 3);

        assert(graph.Get("First Vertex").Get().GetData() == 444);

        assert(graph.Get("Second DADR 0030430//posod").Get().GetData() == 1234);

        assert(graph.Get("").Get().GetData() == 444);

        try{
            graph.Get("Third"); // we have not added vertex with this index
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }

    }
}

void TestGraphRemoveVertex()
{
    {
        Graph<int, int, int> graph(GetHashCodeInt);

        graph.AddVertex(0, 8800555);

        graph.AddVertex(1, -9088);

        graph.AddVertex(133232, 0);

        graph.Remove(0);
        assert(graph.GetLength() == 2);

        graph.Remove(133232);
        assert(graph.GetLength() == 1);

        try{
            graph.Remove(999); //we had not vertex with that index
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }

        try{
            graph.Remove(0); //we have already removed this vertex
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }


    }
    {
        Graph<MyString, int, double> graph(GetHashCodeMyString);

        graph.AddVertex("First", 8800555);

        graph.AddVertex("Second", -9088);

        graph.AddVertex("Third Vertex", 0);

        graph.Remove("First");
        assert(graph.GetLength() == 2);

        graph.Remove("Second");
        assert(graph.GetLength() == 1);

        try{
            graph.Remove("Hello World"); //we had not vertex with that index
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }

        try{
            graph.Remove("Second"); //we have already removed this vertex
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }

        graph.AddVertex("Third", 223);

        try{
            graph.AddVertex("Third", 8800555); //we already have vertex with this key
            assert(0); // we should get exeption
        }
        catch(...)
        {

        }
    }
}

void TestPrintGraph()
{
    {
        Graph<MyString, int, double> graph(GetHashCodeMyString);

        graph.AddVertex("First", 8800555);

        graph.AddVertex("Second", -9088);

        graph.AddVertex("Third Vertex", 0);

        PrintAdjacencyMatrix(graph);

        
    }
}