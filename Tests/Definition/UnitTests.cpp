
#include <cassert>

#include "Graph.h"
#include "MyString.h"

#include "PrintArray.h"
#include "PrintAdjacencyMatrix.h"

#include "ReturnValue.h"
#include "PrintPath.h"

#include "GenerateDotFileDouble.h"

void TestGraphConstructor()
{
//built-in data types
    {
    Graph<int, int> graph;

    assert(graph.GetCountOfVertices() == 0);
    assert(graph.GetCountOfEdges() == 0);

    }

//custom data types
    {
    Graph<MyString, Index> graph;
    assert(graph.GetCountOfVertices() == 0);
    assert(graph.GetCountOfEdges() == 0);
    }
}

void TestGraphAddVertex()
{
//built-in data types
    {
        Graph<int, int> graph;

    // enter value
        graph.AddVertex("First Vertex ID", 8'800'555); 
        assert(graph.GetCountOfVertices() == 1);

        graph.AddVertex("Second Vertex ID", -9'088);
        assert(graph.GetCountOfVertices() == 2);

        graph.AddVertex("Third Vertex ID", 0);
        assert(graph.GetCountOfVertices() == 3);

    //check value
        assert(graph.GetSharedPointerVertex("First Vertex ID").Get().GetDataVertex() == 8'800'555);

        assert(graph.GetSharedPointerVertex("Second Vertex ID").Get().GetDataVertex() == -9'088);

        assert(graph.GetSharedPointerVertex("Third Vertex ID").Get().GetDataVertex() == -0);

        try{
            graph.GetSharedPointerVertex("2").Get().GetDataVertex(); // we have not added vertex with this index
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }

        try{
            graph.AddVertex("First Vertex ID", 0); //we can not add two vertices with same value
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }

        assert(graph.GetCountOfEdges() == 0); // we have not added edges
        
    }

//custom data types
    {
        Graph<MyString, double> graph;

    //enter value    
        graph.AddVertex("First Vertex ID", "Gosha");
        assert(graph.GetCountOfVertices() == 1);

        graph.AddVertex("Second Vertex ID", "Sasha");
        assert(graph.GetCountOfVertices() == 2);

        graph.AddVertex("", "Petya");
        assert(graph.GetCountOfVertices() == 3);

    //check value
        assert(graph.GetSharedPointerVertex("First Vertex ID").Get().GetDataVertex() == "Gosha");

        assert(graph.GetSharedPointerVertex("Second Vertex ID").Get().GetDataVertex() == "Sasha");

        assert(graph.GetSharedPointerVertex("").Get().GetDataVertex() == "Petya");

        try{
            graph.GetSharedPointerVertex("Third Vertex"); // we have not added vertex with this index
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }

        try{ 
            graph.AddVertex("", "Vasya"); // we already have vertex with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }

        

        assert(graph.GetCountOfEdges() == 0); // we have not added edges

    }
}

void TestGraphAddEdge()
{
//built-in data types
    {
        Graph<int, int> graph;
            // first parametr is ID
        graph.AddVertex("First Vertex ID", 8'800'555); 
        graph.AddVertex("Second Vertex ID", -9'088);
        graph.AddVertex("Third Vertex ID", 0);

    // enter value
        graph.AddEdge("First Edge ID", 0, "First Vertex ID", "Second Vertex ID", 200'000);
            //id: "First Edge ID", notOriented, idVertexStart: "First Vertex ID", idVertexEnd: "Second Vertex ID", value 200'000
        assert(graph.GetCountOfEdges() == 1);
        
        graph.AddEdge("Second Edge ID", 0, "Second Vertex ID", "Third Vertex ID", -300);
        assert(graph.GetCountOfEdges() == 2);

        graph.AddEdge("Third Edge ID", 1, "Third Vertex ID", "Third Vertex ID", 100'500); //oriented edge into itself
        assert(graph.GetCountOfEdges() == 3);

    //check value
        assert(graph.GetSharedPointerEdge("First Edge ID").Get().GetDataEdge() == 200'000);
        assert(graph.GetSharedPointerEdge("First Edge ID").Get().Oriented() == 0);

        assert(graph.GetSharedPointerEdge("Second Edge ID").Get().GetDataEdge() == -300);
        assert(graph.GetSharedPointerEdge("Second Edge ID").Get().Oriented() == 0);

        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().GetDataEdge() == 100'500);
        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().Oriented() == 1);

    //check Index connected Vertices
        assert(graph.GetSharedPointerEdge("First Edge ID").Get().GetStartVertexID() == "First Vertex ID");
        assert(graph.GetSharedPointerEdge("First Edge ID").Get().GetEndVertexID() == "Second Vertex ID");
        
        assert(graph.GetSharedPointerEdge("Second Edge ID").Get().GetStartVertexID() == "Second Vertex ID");
        assert(graph.GetSharedPointerEdge("Second Edge ID").Get().GetEndVertexID() == "Third Vertex ID");
        
        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().GetStartVertexID() == "Third Vertex ID");
        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().GetEndVertexID() == "Third Vertex ID");            

        try{
            graph.GetSharedPointerEdge("Fourth Edge ID"); // we have not added edge with this index
            assert(0); // we should get exeption if we find non-existent edge
        }
        catch(...){}
        

        try{ 
            graph.AddEdge("First Edge ID", 0, "Third Vertex ID", "Second Vertex ID", 2); // we already have edge with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }
        
    }

//custom data types
    {
        Graph<MyString, MyString> graph;

        graph.AddVertex("First Vertex ID", "First Vertex Data"); 
        graph.AddVertex("Second Vertex ID", "Second Vertex Data");
        graph.AddVertex("Third Vertex ID", "Third Vertex Data");

    // enter value
        graph.AddEdge("First Edge ID", 0, "First Vertex ID", "Second Vertex ID", "First Edge Data");
            //id: "First Edge ID", notOriented, 
            //idVertexStart: "First Vertex ID", idVertexEnd: "Second Vertex ID", value "First Edge Data"

        assert(graph.GetCountOfEdges() == 1);
        
        graph.AddEdge("Second Edge ID", 0, "Second Vertex ID", "Third Vertex ID", "Second Edge Data");
        assert(graph.GetCountOfEdges() == 2);

        graph.AddEdge("Third Edge ID", 1, "Third Vertex ID", "Third Vertex ID", "Third Edge Data"); //oriented edge into itself
        assert(graph.GetCountOfEdges() == 3);

    //check value
        assert(graph.GetSharedPointerEdge("First Edge ID").Get().GetDataEdge() == "First Edge Data");
        assert(graph.GetSharedPointerEdge("First Edge ID").Get().Oriented() == 0);

        assert(graph.GetSharedPointerEdge("Second Edge ID").Get().GetDataEdge() == "Second Edge Data");
        assert(graph.GetSharedPointerEdge("Second Edge ID").Get().Oriented() == 0);

        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().GetDataEdge() == "Third Edge Data");
        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().Oriented() == 1);

    //check Index connected Vertices
        assert(graph.GetSharedPointerEdge("First Edge ID").Get().GetStartVertexID() == "First Vertex ID");
        assert(graph.GetSharedPointerEdge("First Edge ID").Get().GetEndVertexID() == "Second Vertex ID");
        
        assert(graph.GetSharedPointerEdge("Second Edge ID").Get().GetStartVertexID() == "Second Vertex ID");
        assert(graph.GetSharedPointerEdge("Second Edge ID").Get().GetEndVertexID() == "Third Vertex ID");
        
        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().GetStartVertexID() == "Third Vertex ID");
        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().GetEndVertexID() == "Third Vertex ID");            

        try{
            graph.GetSharedPointerEdge("Fourth Edge ID"); // we have not added edge with this index
            assert(0); // we should get exeption if we find non-existent edge
        }
        catch(...)
        {}

        try{ 
            graph.AddEdge("First Edge ID", 0, "Third Edge ID", "Second Vertex ID", "A_BOB_US"); // we already have edge with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {
            
        }
        
    }
}

void TestGraphRemoveEdge()
{
//built-in data types
    {
        Graph<int, int> graph;
    
        graph.AddVertex("First Vertex ID", 8'800'555); 
        graph.AddVertex("Second Vertex ID", -9'088);
        graph.AddVertex("Third Vertex ID", 0);

        graph.AddEdge("First Edge ID", 0, "First Vertex ID", "Second Vertex ID", 200'000);
            //id: "First Edge ID", notOriented, idVertexStart: "First Vertex ID", idVertexEnd: "Second Vertex ID", value 200'000        
        graph.AddEdge("Second Edge ID", 0, "Second Vertex ID", "Third Vertex ID", -300);
        graph.AddEdge("Third Edge ID", 1, "Third Vertex ID", "Third Vertex ID", 100'500); //oriented edge into itself

        assert(graph.GetCountOfEdges() == 3);
    //remove edges

        graph.RemoveEdge("First Edge ID");
        assert(graph.GetCountOfEdges() == 2);
        try{
            graph.GetSharedPointerEdge("First Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption if we find non-existent edge
        }
        catch(...)
        {}
        try{ 
            graph.RemoveEdge("First Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {}

        graph.RemoveEdge("Second Edge ID");
        assert(graph.GetCountOfEdges() == 1);
        try{
            graph.GetSharedPointerEdge("Second Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption if we find non-existent edge
        }
        catch(...)
        {}
        try{ 
            graph.RemoveEdge("Second Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {}

        graph.RemoveEdge("Third Edge ID");
        assert(graph.GetCountOfEdges() == 0);
        try{
            graph.GetSharedPointerEdge("Third Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption if we find non-existent edge
        }
        catch(...)
        {}
        try{ 
            graph.RemoveEdge("Third Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {}
        
    }

//custom data types
   {
        Graph<MyString, MyString> graph;
    
        graph.AddVertex("First Vertex ID", "First Vertex Data"); 
        graph.AddVertex("Second Vertex ID", "Second Vertex Data");
        graph.AddVertex("Third Vertex ID", "Third Vertex Data");

        graph.AddEdge("First Edge ID", 0, "First Vertex ID", "Second Vertex ID", "First Edge Data");
            //id: "First Edge ID", notOriented, idVertexStart: "First Vertex ID", idVertexEnd: "Second Vertex ID", value "First Edge Data"       
        graph.AddEdge("Second Edge ID", 0, "Second Vertex ID", "Third Vertex ID", "Second Edge Data");
        graph.AddEdge("Third Edge ID", 1, "Third Vertex ID", "Third Vertex ID", "Third Edge Data"); //oriented edge into itself

        assert(graph.GetCountOfEdges() == 3);
    //remove edges

        graph.RemoveEdge("First Edge ID");
        assert(graph.GetCountOfEdges() == 2);
        try{
            graph.GetSharedPointerEdge("First Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption if we find non-existent edge
        }
        catch(...)
        {}
        try{ 
            graph.RemoveEdge("First Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {}

        graph.RemoveEdge("Second Edge ID");
        assert(graph.GetCountOfEdges() == 1);
        try{
            graph.GetSharedPointerEdge("Second Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption if we find non-existent edge
        }
        catch(...)
        {}
        try{ 
            graph.RemoveEdge("Second Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {}

        graph.RemoveEdge("Third Edge ID");
        assert(graph.GetCountOfEdges() == 0);
        try{
            graph.GetSharedPointerEdge("Third Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption if we find non-existent edge
        }
        catch(...)
        {}
        try{ 
            graph.RemoveEdge("Third Edge ID"); //we have already removed edge with this ID
            assert(0); // we should get exeption
        }
        catch(...)
        {}
        
    }
}

void TestGraphRemoveVertex()
{
//built-in data types
    {
        Graph<int, int> graph;

        graph.AddVertex("First Vertex ID", 8'800'555);
        graph.AddVertex("Second Vertex ID", -9'088);
        graph.AddVertex("Third Vertex ID", 0);

    //remove vertices

        try{
            graph.RemoveVertex(""); // we have not vertex with this id
            assert(0);
        }
        catch(...){}

        graph.RemoveVertex("First Vertex ID");
        assert(graph.GetCountOfVertices() == 2);
        try{
            graph.RemoveVertex("First Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerVertex("First Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}

        graph.RemoveVertex("Second Vertex ID");
        assert(graph.GetCountOfVertices() == 1);
        try{
            graph.RemoveVertex("Second Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerVertex("Second Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}

        graph.RemoveVertex("Third Vertex ID");
        assert(graph.GetCountOfVertices() == 0);
        try{
            graph.RemoveVertex("Third Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerVertex("Third Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}
        
    }

//custom data types //it is not Copy-Paste because something may be wrong with delete vertex with custom data :)
    {
        Graph<MyString, MyString> graph;

        graph.AddVertex("", "First Vertex Data");
        graph.AddVertex("Second Vertex ID", "Second Vertex Data");
        graph.AddVertex("Third Vertex ID", "Third Vertex Data");

    //remove vertices

        try{
            graph.RemoveVertex("0"); // we have not vertex with this id
            assert(0);
        }
        catch(...){}

        graph.RemoveVertex("");
        assert(graph.GetCountOfVertices() == 2);
        try{
            graph.RemoveVertex(""); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerVertex(""); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}

        graph.RemoveVertex("Second Vertex ID");
        assert(graph.GetCountOfVertices() == 1);
        try{
            graph.RemoveVertex("Second Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerVertex("Second Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}

        graph.RemoveVertex("Third Vertex ID");
        assert(graph.GetCountOfVertices() == 0);
        try{
            graph.RemoveVertex("Third Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerVertex("Third Vertex ID"); // we have already removed vertex with this id
            assert(0);
        }
        catch(...){}        
    }

    
}

void TestGraphRemoveVertexWithAdjacentEdges()
{
//built-in data types
    {
        Graph<int, int> graph;
    
        graph.AddVertex("First Vertex ID", 8'800'555); 
        graph.AddVertex("Second Vertex ID", -9'088);
        graph.AddVertex("Third Vertex ID", 0);

        graph.AddEdge("First Edge ID", 0, "First Vertex ID", "Second Vertex ID", 200'000);
            //id: "First Edge ID", notOriented, idVertexStart: "First Vertex ID", idVertexEnd: "Second Vertex ID", value 200'000        
        graph.AddEdge("Second Edge ID", 0, "First Vertex ID", "Third Vertex ID", -300);
        graph.AddEdge("Third Edge ID", 1, "Third Vertex ID", "Third Vertex ID", 100'500);
        graph.AddEdge("Fourth Edge ID", 0, "First Vertex ID", "First Vertex ID", 200'000);

        //there are two edges from "First Vertex" to another vertices, and one edge from "First Vertex" to "First Vertex"
        assert(graph.GetCountOfEdges() == 4);

        graph.RemoveVertex("First Vertex ID");

        assert(graph.GetCountOfEdges() == 1);//only one edge, from "Third Vertex ID" to "Third Vertex ID" exists

        try{
            graph.GetSharedPointerEdge("First Edge ID"); // should get exeption, because we can not have edge without source vertex
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerEdge("Second Edge ID"); // should get exeption, because we can not have edge without source vertex
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerEdge("Fourth Edge ID"); // should get exeption, because we can not have edge without source vertex
            assert(0);
        }
        catch(...){}

        //check that other edges and vertices had not deleted
        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().GetDataEdge() == 100'500);
        assert(graph.GetSharedPointerVertex("Second Vertex ID").Get().GetDataVertex() == -9'088);
        assert(graph.GetSharedPointerVertex("Third Vertex ID").Get().GetDataVertex() == 0);


    }

    {
        Graph<int, int> graph;

        graph.AddVertex("First Vertex ID", 1);
        graph.AddVertex("Second Vertex ID", 1);

        for(int i = 0; i < 10; ++i){

            Index currentEdgeIndex((MyString::IntToMyString(i)).GetChar());
            graph.AddEdge(currentEdgeIndex, 1, "First Vertex ID", "First Vertex ID", (333232 + i)/333);
        }

        assert(graph.GetCountOfEdges() == 10);

        for(int i = 10; i < 20; ++i){

            Index currentEdgeIndex((MyString::IntToMyString(i)).GetChar());
            graph.AddEdge(currentEdgeIndex, i%2, "Second Vertex ID", "Second Vertex ID", (333232 + i)/333);
        }

        assert(graph.GetCountOfEdges() == 20);

        graph.RemoveVertex("First Vertex ID");

        assert(graph.GetCountOfEdges() == 10);
        assert(graph.GetCountOfVertices() == 1);

        graph.RemoveVertex("Second Vertex ID");

        assert(graph.GetCountOfEdges() == 0);
        assert(graph.GetCountOfVertices() == 0);


    }
//custom data types
    {
        Graph<MyString, MyString> graph;
    
        graph.AddVertex("First Vertex ID", "First Vertex Data"); 
        graph.AddVertex("Second Vertex ID", "Second Vertex Data");
        graph.AddVertex("Third Vertex ID", "Third Vertex Data");

        graph.AddEdge("First Edge ID", 0, "First Vertex ID", "Second Vertex ID", "First Edge Data");
            //id: "First Edge ID", notOriented, idVertexStart: "First Vertex ID", idVertexEnd: "Second Vertex ID", value 200'000        
        graph.AddEdge("Second Edge ID", 0, "First Vertex ID", "Third Vertex ID", "Second Edge Data");
        graph.AddEdge("Third Edge ID", 1, "Third Vertex ID", "Third Vertex ID", "Third Edge Data");
        graph.AddEdge("Fourth Edge ID", 0, "First Vertex ID", "First Vertex ID", "Fourth Edge Data");

        //there are two edges from "First Vertex" to another vertices, and one edge from "First Vertex" to "First Vertex"
        assert(graph.GetCountOfEdges() == 4);

        graph.RemoveVertex("First Vertex ID");

        assert(graph.GetCountOfEdges() == 1);//only one edge, from "Third Vertex ID" to "Third Vertex ID" exists

        try{
            graph.GetSharedPointerEdge("First Edge ID"); // should get exeption, because we can not have edge without source vertex
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerEdge("Second Edge ID"); // should get exeption, because we can not have edge without source vertex
            assert(0);
        }
        catch(...){}
        try{
            graph.GetSharedPointerEdge("Fourth Edge ID"); // should get exeption, because we can not have edge without source vertex
            assert(0);
        }
        catch(...){}

        //check that other edges and vertices had not deleted
        assert(graph.GetSharedPointerEdge("Third Edge ID").Get().GetDataEdge() == "Third Edge Data");
        assert(graph.GetSharedPointerVertex("Second Vertex ID").Get().GetDataVertex() == "Second Vertex Data");
        assert(graph.GetSharedPointerVertex("Third Vertex ID").Get().GetDataVertex() == "Third Vertex Data");


    }

    {
        Graph<MyString, MyString> graph;

        graph.AddVertex("First Vertex ID", "First Vertex Data");
        graph.AddVertex("Second Vertex ID", "Second Vertex Data");

        for(int i = 0; i < 10; ++i){

            Index currentEdgeIndex((MyString::IntToMyString(i)).GetChar());
            graph.AddEdge(currentEdgeIndex, 1, "First Vertex ID", "First Vertex ID", MyString::IntToMyString((333232 + i)/333));
        }

        assert(graph.GetCountOfEdges() == 10);

        for(int i = 10; i < 20; ++i){

            Index currentEdgeIndex((MyString::IntToMyString(i)).GetChar());
            graph.AddEdge(currentEdgeIndex, i%2, "Second Vertex ID", "Second Vertex ID", MyString::IntToMyString((333232 + i)/333));
        }

        assert(graph.GetCountOfEdges() == 20);

        graph.RemoveVertex("First Vertex ID");

        assert(graph.GetCountOfEdges() == 10);
        assert(graph.GetCountOfVertices() == 1);

        graph.RemoveVertex("Second Vertex ID");

        assert(graph.GetCountOfEdges() == 0);
        assert(graph.GetCountOfVertices() == 0);


    }
}

void TestGraphGetEdgesBetweenAdjacentVertices()
{
//built-in data types
    {
        Graph<int, int> graph;
    
        graph.AddVertex("First Vertex ID", 8'800'555); 
        graph.AddVertex("Second Vertex ID", -9'088);
        graph.AddVertex("Third Vertex ID", 0);

        graph.AddEdge("First Edge ID", 0, "First Vertex ID", "Second Vertex ID", 200'000);
            //id: "First Edge ID", notOriented, idVertexStart: "First Vertex ID", idVertexEnd: "Second Vertex ID", value 200'000        
        graph.AddEdge("Second Edge ID", 0, "First Vertex ID", "Third Vertex ID", -300);
        graph.AddEdge("Third Edge ID", 1, "Third Vertex ID", "Third Vertex ID", 100'500);
        graph.AddEdge("Fourth Edge ID", 0, "First Vertex ID", "First Vertex ID", 200'000);
        graph.AddEdge("Fifth Edge ID", 1, "First Vertex ID", "Second Vertex ID", 987'654'321);
        graph.AddEdge("Sixth Edge ID", 1, "Second Vertex ID", "First Vertex ID", +300);

        //"First Edge": not-oriented edge from "First Vertex" to "Second Vertex"
        //"Second Edge": not-oriented edge from "First Vertex" to "Third Vertex"
        //"Third Edge": oriented edge from "Third Vertex" to "Third Vertex"
        //"Fourth Edge": not-oriented edge from "First Vertex" to "First Vertex"
        //"Fifth Edge": oriented edge from "First Vertex" to "Second Vertex"
        //"Sixth Edge": oriented edge from "Second Vertex" to "First Vertex"

        //when i call GetEdgesBetweenAdjacentVertices("First Vertex", "Second Vertex")
        //graph should receive: "First Edge", "Fifth Edge".
        
        LinkedList<SharedPtr<Edge< int, int> > > listEdgesFirstSecond = graph.GetEdgesBetweenAdjacentVertices("First Vertex ID", "Second Vertex ID");
        assert(listEdgesFirstSecond.GetLength() == 2);

        assert((listEdgesFirstSecond.Get(0)).Get().GetID() == "First Edge ID" 
                || (listEdgesFirstSecond.Get(0)).Get().GetID() == "Fifth Edge ID");

        assert((listEdgesFirstSecond.Get(1)).Get().GetID() == "First Edge ID" 
                || (listEdgesFirstSecond.Get(1)).Get().GetID() == "Fifth Edge ID");
        
        assert( (listEdgesFirstSecond.Get(0)).Get().GetID() != (listEdgesFirstSecond.Get(1)).Get().GetID() );


        //when i call GetEdgesBetweenAdjacentVertices("First Vertex", "First Vertex")
        //graph should receive: "Fourth Edge".

        LinkedList<SharedPtr<Edge< int, int> > > listEdgesFirstFirst = graph.GetEdgesBetweenAdjacentVertices("First Vertex ID", "First Vertex ID");
        assert(listEdgesFirstFirst.GetLength() == 1);

        assert((listEdgesFirstFirst.Get(0)).Get().GetID() == "Fourth Edge ID");


        //when i call GetEdgesBetweenAdjacentVertices("Second Vertex", "Second Vertex")
        //graph should receive: .

        LinkedList<SharedPtr<Edge< int, int> > > listEdgesSecondSecond = graph.GetEdgesBetweenAdjacentVertices("Second Vertex ID", "Second Vertex ID");
        assert(listEdgesSecondSecond.GetLength() == 0);


    }
}

void TestGraphGetAdjacentVertices()
{
//built-in data types
    {
        Graph<int, int> graph;
    
        graph.AddVertex("First Vertex ID", 8'800'555); 
        graph.AddVertex("Second Vertex ID", -9'088);
        graph.AddVertex("Third Vertex ID", 0);

        graph.AddEdge("First Edge ID", 0, "First Vertex ID", "Second Vertex ID", 200'000);
            //id: "First Edge ID", notOriented, idVertexStart: "First Vertex ID", idVertexEnd: "Second Vertex ID", value 200'000        
        graph.AddEdge("Second Edge ID", 0, "First Vertex ID", "Third Vertex ID", -300);
        graph.AddEdge("Third Edge ID", 1, "Third Vertex ID", "Third Vertex ID", 100'500);
        graph.AddEdge("Fourth Edge ID", 0, "First Vertex ID", "First Vertex ID", 200'000);
        graph.AddEdge("Fifth Edge ID", 1, "First Vertex ID", "Second Vertex ID", 987'654'321);
        graph.AddEdge("Sixth Edge ID", 1, "Second Vertex ID", "First Vertex ID", +300);

        //"First Edge": not-oriented edge from "First Vertex" to "Second Vertex"
        //"Second Edge": not-oriented edge from "First Vertex" to "Third Vertex"
        //"Third Edge": oriented edge from "Third Vertex" to "Third Vertex"
        //"Fourth Edge": not-oriented edge from "First Vertex" to "First Vertex"
        //"Fifth Edge": oriented edge from "First Vertex" to "Second Vertex"
        //"Sixth Edge": oriented edge from "Second Vertex" to "First Vertex"

        //when i call GetAdjacentVertices("First Vertex")
        //graph should receive: "First Vertex ID", "Second Vertex ID", "Third Vertex ID".
        
        LinkedList<SharedPtr<Vertex<int, int> > > listFirst = graph.GetAdjacentVertices("First Vertex ID");

        assert(listFirst.GetLength() == 3);


        //when i call GetAdjacentVertices("Second Vertex")
        //graph should receive: "First Vertex ID".
        
        LinkedList<SharedPtr<Vertex<int, int> > > listSecond = graph.GetAdjacentVertices("Second Vertex ID");

        assert(listSecond.GetLength() == 1);

        assert(listSecond.Get(0).Get().GetID() == "First Vertex ID");


        //when i call GetAdjacentVertices("Third Vertex")
        //graph should receive: "First Vertex ID", "Third Vertex ID".
        
        LinkedList<SharedPtr<Vertex<int, int> > > listThird = graph.GetAdjacentVertices("Third Vertex ID");

        assert(listThird.GetLength() == 2);

        assert((listThird.Get(0).Get().GetID() == "First Vertex ID") 
                || (listThird.Get(1).Get().GetID() == "First Vertex ID"));

        assert((listThird.Get(0).Get().GetID() == "Third Vertex ID") 
                || (listThird.Get(1).Get().GetID() == "Third Vertex ID"));

        assert(listThird.Get(0).Get().GetID() != listThird.Get(1).Get().GetID());


        graph.AddVertex("Fourth Vertex ID", 999);

        LinkedList<SharedPtr<Vertex<int, int> > > listFourth = graph.GetAdjacentVertices("Fourth Vertex ID");

        assert(listFourth.GetLength() == 0);
                
        


    }

    {
        Graph<int, int> graph;

        graph.AddVertex("First Vertex ID", 1);
        graph.AddVertex("Second Vertex ID", 1);

        for(int i = 0; i < 10; ++i){

            Index currentEdgeIndex((MyString::IntToMyString(i)).GetChar());
            graph.AddEdge(currentEdgeIndex, 1, "First Vertex ID", "First Vertex ID", (333232 + i)/333);
        }

        assert(graph.GetCountOfEdges() == 10);

        for(int i = 10; i < 20; ++i){

            Index currentEdgeIndex((MyString::IntToMyString(i)).GetChar());
            graph.AddEdge(currentEdgeIndex, i%2, "Second Vertex ID", "Second Vertex ID", (333232 + i)/333);
        }

        LinkedList<SharedPtr<Vertex<int, int> > > listSecond = graph.GetAdjacentVertices("Second Vertex ID");

        assert(listSecond.GetLength() == 1);


    }
}

void TestGraphFindMininumEdge()
{
    {
        Graph<int, int> graph;

        graph.AddVertex("First Vertex ID", 1);
        graph.AddVertex("Second Vertex ID", 1);

        for(int i = 0; i < 10; ++i){

            Index currentEdgeIndex((MyString::IntToMyString(i)).GetChar());
            graph.AddEdge(currentEdgeIndex, 1, "First Vertex ID", "First Vertex ID", i);
        }


        for(int i = 10; i < 20; ++i){

            Index currentEdgeIndex((MyString::IntToMyString(i)).GetChar());
            graph.AddEdge(currentEdgeIndex, i%2, "Second Vertex ID", "Second Vertex ID", i);
        }

        LinkedList<SharedPtr<Edge<int, int> > > listEdgesFirst = graph.GetEdgesBetweenAdjacentVertices("First Vertex ID", "First Vertex ID");
        SharedPtr<Edge<int, int> > pMinimumEdgeFirst = graph.FindMininumEdge(listEdgesFirst);

        assert(pMinimumEdgeFirst.Get().GetDataEdge() == 0);


        LinkedList<SharedPtr<Edge<int, int> > > listEdgesSecond = graph.GetEdgesBetweenAdjacentVertices("Second Vertex ID", "Second Vertex ID");
        SharedPtr<Edge<int, int> > pMinimumEdgeSecond = graph.FindMininumEdge(listEdgesSecond);

        assert(pMinimumEdgeSecond.Get().GetDataEdge() == 10);



        


    }
}

//BFS finds path with minimum count of Edges  !!(It is do not minimizes summary of TypeEdgeData)!!
void TestGraphBreadthFirstSearch() 
{
    {
        Graph<int, int> graph;

        graph.AddVertex("First Vertex ID", 1);
        graph.AddVertex("Second Vertex ID", 2);
        graph.AddVertex("Third Vertex ID", 3);
        graph.AddVertex("Fourth Vertex ID", 4);
        graph.AddVertex("Fifth Vertex ID", 5);
        graph.AddVertex("Zero Vertex ID", 0);
        graph.AddVertex("Sixth Vertex ID", 6);
        graph.AddVertex("Seventh Vertex ID", 6);
        graph.AddVertex("Eighth Vertex ID", 6);
        graph.AddVertex("Ninth Vertex ID", 6);
        graph.AddVertex("Tenth Vertex ID", 6);

        graph.AddEdge("First Edge ID", 0, "Zero Vertex ID", "Second Vertex ID", 1);
        graph.AddEdge("Second Edge ID", 0, "Zero Vertex ID", "First Vertex ID", 2);
        graph.AddEdge("Third Edge ID", 0, "Second Vertex ID", "Fourth Vertex ID", 3);
        graph.AddEdge("Fourth Edge ID", 0, "First Vertex ID", "Fifth Vertex ID", 4) ;
        graph.AddEdge("Fifth Edge ID", 0, "First Vertex ID", "Third Vertex ID", 5);
        graph.AddEdge("Sixth Edge ID", 0, "Fourth Vertex ID", "Sixth Vertex ID", 5);
        graph.AddEdge("Seventh Edge ID", 0, "Fifth Vertex ID", "Ninth Vertex ID", 5);
        graph.AddEdge("Eighth Edge ID", 0, "Seventh Vertex ID", "Eighth Vertex ID", 5);
        graph.AddEdge("Ninth Edge ID", 0, "Fifth Vertex ID", "Seventh Vertex ID", 5);
        graph.AddEdge("Tenth Edge ID", 0, "Ninth Vertex ID", "Eighth Vertex ID", 5);

        

        MyNamespace::ReturnValue<Path<int, int> > returnValueTenthTenth = graph.BreadthFirstSearch("Tenth Vertex ID", "Tenth Vertex ID");

        assert(returnValueTenthTenth.IsCorrect());
        assert(returnValueTenthTenth.GetValue().listVertices_.GetLength() == 1);
        assert(returnValueTenthTenth.GetValue().listEdges_.GetLength() == 0);
        //------------------------------------

        MyNamespace::ReturnValue<Path<int, int> > returnValueZeroSixth = graph.BreadthFirstSearch("Zero Vertex ID", "Sixth Vertex ID");

        assert(returnValueZeroSixth.IsCorrect());
        assert(returnValueZeroSixth.GetValue().listVertices_.GetLength() == 4);
        assert(returnValueZeroSixth.GetValue().listEdges_.GetLength() == 3);

        //PrintPath<int, int>(returnValue.GetValue());
        //------------------------------------

        MyNamespace::ReturnValue<Path<int, int> > returnValueFourthFirst = graph.BreadthFirstSearch("Fourth Vertex ID", "First Vertex ID");

        assert(returnValueFourthFirst.IsCorrect());
        assert(returnValueFourthFirst.GetValue().listVertices_.GetLength() == 4);
        assert(returnValueFourthFirst.GetValue().listEdges_.GetLength() == 3);

        //Add oriented Vertex from "Fourth Vertex ID" to "First Vertex ID"
        graph.AddEdge("Eleventh Edge ID", 1, "Fourth Vertex ID", "First Vertex ID", 0);
        MyNamespace::ReturnValue<Path<int, int> > returnValueFourthFirst2 = graph.BreadthFirstSearch("Fourth Vertex ID", "First Vertex ID");

        assert(returnValueFourthFirst2.IsCorrect());
        assert(returnValueFourthFirst2.GetValue().listVertices_.GetLength() == 2); // because now we have less way
        assert(returnValueFourthFirst2.GetValue().listEdges_.GetLength() == 1);
        //------------------------------------

        MyNamespace::ReturnValue<Path<int, int> > returnValueFirstFourth = graph.BreadthFirstSearch("First Vertex ID", "Fourth Vertex ID");

        assert(returnValueFirstFourth.IsCorrect());

        //this way contains four vertices because Eleventh Edge is oriented end search can not go through this
        assert(returnValueFirstFourth.GetValue().listVertices_.GetLength() == 4);
        assert(returnValueFirstFourth.GetValue().listEdges_.GetLength() == 3);

        try{
            MyNamespace::ReturnValue<Path<int, int> > returnValueTvelvethFourth 
                        = graph.BreadthFirstSearch("Tvelveth Vertex ID", "Fourth Vertex ID");// there are no Vertex with id "Tvelveth Vertex ID"
            assert(0);
        }
        catch(...) {}

    }
}

//тестируется верное нахождение стоимости пути, алгоритм воссоздания самого пути применялся такой же как в BFS
void TestFordBellmanAlgorithm()
{
    {
        
        Graph<int, int> graph;

        graph.AddVertex("First", 1);
        graph.AddVertex("Second", 2);
        graph.AddVertex("Third", 3);
        graph.AddVertex("Fourth", 4);
        graph.AddVertex("Fifth", 5);
        graph.AddVertex("Zero", 0);

        graph.AddEdge("First Edge ID", 0, "Zero", "Second", 1);
        graph.AddEdge("Second Edge ID", 0, "Zero", "First", 2);
        graph.AddEdge("Third Edge ID", 0, "Second", "Fourth", 3);
        graph.AddEdge("Fourth Edge ID", 0, "First", "Fifth", 4) ;
        graph.AddEdge("Fifth Edge ID", 0, "First", "Third", 5);
        

        MyNamespace::ReturnValue<int> returnValueWaySecondZero = graph.GetValueOfMinimumWay("Second", "Zero");

        Path<int, int> pathSecondZero = graph.GetMinimumWay("Second", "Zero");

        assert(returnValueWaySecondZero.GetValue() == 1);

        assert(pathSecondZero.listEdges_.GetLength() == 1);

        assert(pathSecondZero.listVertices_.GetLength() == 2);

        //добавляется ориентированное ребро через которое путь быстрее
        graph.AddEdge("Sixth Edge ID", 1, "Fourth", "First", -1);

        MyNamespace::ReturnValue<int> returnValueWaySecondFirst = graph.GetValueOfMinimumWay("Second", "First");

        assert(returnValueWaySecondFirst.GetValue() == 2);

        //проверка что не пойдет против ориентации ребра
        MyNamespace::ReturnValue<int> returnValueWayThirdFourth = graph.GetValueOfMinimumWay("Third", "Fourth");

        assert(returnValueWayThirdFourth.GetValue() == 11);

        //добавлен цикл отрицательного веса
        graph.AddEdge("Seventh Edge ID", 1, "Second", "Fifth", -1);
        graph.AddEdge("Eighth Edge ID", 1, "Fifth", "Second", -1);

        try{
            //поскольку есть цикл отрицательного веса функция должна выбрасить исключение
            MyNamespace::ReturnValue<int> returnValueWayThirdFourth = graph.GetValueOfMinimumWay("Third", "Fourth");
            assert(0);
        }
        catch(...) {}

    }

    
}

void TestGenerateDOTFileDouble()
{
    // {
    //      Graph<double, double> graph;

    //     graph.AddVertex("First", 1);
    //     graph.AddVertex("Second", 2);
    //     graph.AddVertex("Third", 3);
    //     graph.AddVertex("Fourth", 4);
    //     graph.AddVertex("Fifth", 5);
    //     graph.AddVertex("Zero", 0);

    //     graph.AddEdge("First Edge ID", 0, "Zero", "Second", 1);
    //     graph.AddEdge("Second Edge ID", 0, "Zero", "First", 2);
    //     graph.AddEdge("Third Edge ID", 0, "Second", "Fourth", 3);
    //     graph.AddEdge("Fourth Edge ID", 0, "First", "Fifth", 4) ;
    //     graph.AddEdge("Fifth Edge ID", 0, "First", "Third", 5);

    //     GenerateDOTFileDouble(graph, MyString("TestAutomaticallyGenerated"));
    // }

    {
        
        Graph<double, double> graph;

        graph.AddVertex("First", 1.4);
        graph.AddVertex("Second", 2.8);
        graph.AddVertex("Third", 3.2);
        graph.AddVertex("Fourth", 4.4);
        graph.AddVertex("Fifth", 5.1);
        graph.AddVertex("Zero", -0.234);

        graph.AddEdge("First Edge ID", 0, "Zero", "Second", 1);
        graph.AddEdge("Second Edge ID", 0, "Zero", "First", 2);
        graph.AddEdge("Third Edge ID", 0, "Second", "Fourth", 3);
        graph.AddEdge("Fourth Edge ID", 0, "First", "Fifth", 4) ;
        graph.AddEdge("Fifth Edge ID", 0, "First", "Third", 5);
        

        MyNamespace::ReturnValue<double> returnValueWaySecondZero = graph.GetValueOfMinimumWay("Second", "Zero");

        Path<double, double> pathSecondZero = graph.GetMinimumWay("Second", "Zero");

        GenerateDOTFileDouble(graph, MyString("PringBellmanAlgorithm"), pathSecondZero);
        

        // //добавляется ориентированное ребро через которое путь быстрее
        // graph.AddEdge("Sixth Edge ID", 1, "Fourth", "First", -1);

        // MyNamespace::ReturnValue<int> returnValueWaySecondFirst = graph.GetValueOfMinimumWay("Second", "First");

        // assert(returnValueWaySecondFirst.GetValue() == 2);

        // //проверка что не пойдет против ориентации ребра
        // MyNamespace::ReturnValue<int> returnValueWayThirdFourth = graph.GetValueOfMinimumWay("Third", "Fourth");

        // assert(returnValueWayThirdFourth.GetValue() == 11);

        // //добавлен цикл отрицательного веса
        // graph.AddEdge("Seventh Edge ID", 1, "Second", "Fifth", -1);
        // graph.AddEdge("Eighth Edge ID", 1, "Fifth", "Second", -1);

        // try{
        //     //поскольку есть цикл отрицательного веса функция должна выбрасить исключение
        //     MyNamespace::ReturnValue<int> returnValueWayThirdFourth = graph.GetValueOfMinimumWay("Third", "Fourth");
        //     assert(0);
        // }
        // catch(...) {}

    }
}