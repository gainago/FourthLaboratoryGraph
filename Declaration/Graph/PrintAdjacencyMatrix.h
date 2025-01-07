#ifndef PRINT_ADJACENCY_MATRIX_H
#define PRINT_ADJACENCY_MATRIX_H

#include <iostream>

#include "Dictionary.h"
#include "Graph.h"

template <typename TypeNameVertex, typename TypeDataVertex, typename TypeDataEdge> 
void PrintAdjacencyMatrix(Graph<TypeNameVertex, TypeDataVertex, TypeDataEdge> const & graph)
{
    typename Graph<TypeNameVertex, TypeDataVertex, TypeDataEdge>::ConstIteratorVertex it = graph.ConstBegin();
    typename Graph<TypeNameVertex, TypeDataVertex, TypeDataEdge>::ConstIteratorVertex itEnd = graph.ConstEnd();

    std::cout << std::endl << "\t";

    for(/*it*/; it != itEnd; ++it){
        std::cout << (*it).GetFirst() << "\t";
    }

    typename Graph<TypeNameVertex, TypeDataVertex, TypeDataEdge>::ConstIteratorVertex itRows = graph.ConstBegin();
    typename Graph<TypeNameVertex, TypeDataVertex, TypeDataEdge>::ConstIteratorVertex itColumns = graph.ConstBegin();

    for(/*itRows*/; itRows != itEnd; ++itRows){

        for(/*itColumns*/; itColumns != itEnd; ++itColumns){

            SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > const currentPointerColumnVertex = (*itColumns).GetSecond();
            
            typename Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge>::ConstIteratorEdge itEdge = (currentPointerColumnVertex.Get()).ConstBegin();
            typename Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge>::ConstIteratorEdge itEdgeEnd = (currentPointerColumnVertex.Get()).ConstEnd();
            
            for(/*itEdge*/; itEdge != itEdgeEnd; ++itEdge){
                
                WeakPtr< Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > const vertexStart;
                WeakPtr< Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > const vertexEnd;
            }
        }

    }

    std::cout << std::endl;
}

#endif //PRINT_ADJECENCY_MATRIX_H