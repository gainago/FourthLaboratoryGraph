#include <iostream>
#include <SharedPtr.h>
//#include "UnitTests.h"
#include "InputOutputMyString.h"
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

   Graph<int, int> graph;
   graph.AddVertex("First", 24);
   graph.AddVertex("Second", 24);

   graph.AddVertex("Third", 24);

   graph.AddEdge("First Edge", true, graph.GetSharedPointerVertex("First"), graph.GetSharedPointerVertex("First"), 256);

   PrintAdjacencyMatrix(graph);
}