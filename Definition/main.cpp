#include <iostream>
#include <SharedPtr.h>
//#include "UnitTests.h"
#include "InputOutputIndex.h"
#include "Graph.h"
#include "Vertex.h"
#include "PrintAdjacencyMatrix.h"

Vertex<int, int>& GetVertex()
{
   static Vertex<int, int> v1("ABOBA", 12);
   return v1;
}

int main(int argc, char** argv)
{
   // TestGraphConstructor();
   // TestGraphAddVertex();
   // TestGraphRemoveVertex();
   // TestPrintGraph();
   // Vertex<int, int> & vertexRef = GetVertex();
   // OutputMyString( vertexRef.GetID());

   Graph<MyString, int> graph;
   graph.AddVertex("First", "Gosha");
   graph.AddVertex("Second", "Telyak");

   graph.AddVertex("Third", "Gorbat");

   graph.AddEdge("First Edge", true, "First", "First", 256);

   graph.AddVertex("Fourth", "Vlada");

   graph.AddEdge("Bad Edge", 0,"Second","First", 68);

   PrintAdjacencyMatrix(graph);
}