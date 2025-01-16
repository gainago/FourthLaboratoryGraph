#include <iostream>
#include <SharedPtr.h>
#include "UnitTests.h"
#include "InputOutputIndex.h"
#include "Graph.h"
#include "Vertex.h"
#include "PrintAdjacencyMatrix.h"

int main(int argc, char** argv)
{
   TestGraphConstructor();
    TestGraphAddVertex();
   TestGraphAddEdge();
    TestGraphRemoveEdge();
   TestGraphRemoveVertex();
   TestGraphRemoveVertexWithAdjacentEdges();
}