#ifndef PRINT_ADJACENCY_MATRIX_H
#define PRINT_ADJACENCY_MATRIX_H

#include <iostream>

#include "Dictionary.h"
#include "Graph.h"
#include "InputOutputIndex.h"

template < typename TypeDataVertex, typename TypeDataEdge> 
void PrintAdjacencyMatrix(Graph<TypeDataVertex, TypeDataEdge> const & graph)
{
    typename Graph<TypeDataVertex, TypeDataEdge>::ConstIteratorVertex cIt = graph.ConstBegin();
    typename Graph<TypeDataVertex, TypeDataEdge>::ConstIteratorVertex cItEnd = graph.ConstEnd();

    std::cout << "\t";
    for(/*cIt*/; cIt != cItEnd; ++cIt){
        OutputIndex((*cIt).GetID());
        std::cout << "(" << (*cIt).GetDataVertex() << ")" << "\t";
    }
    std::cout << std::endl;

    typename Graph<TypeDataVertex, TypeDataEdge>::ConstIteratorVertex cItRow = graph.ConstBegin();
    

    for(/*cItRow*/; cItRow != cItEnd; ++cItRow){

        OutputIndex((*cItRow).GetID());
        std::cout << "(" << (*cItRow).GetDataVertex() << ")" << "\t";

        typename Graph<TypeDataVertex, TypeDataEdge>::ConstIteratorVertex cItColumn = graph.ConstBegin();

        for(/*cItColumn*/; cItColumn != cItEnd; ++cItColumn){

            typename Vertex<TypeDataVertex, TypeDataEdge>::ConstIteratorEdge cItEdgeRow = (*cItRow).ConstBegin();
            typename Vertex<TypeDataVertex, TypeDataEdge>::ConstIteratorEdge cItEdgeRowEnd = (*cItRow).ConstEnd();

            bool IsConnected = 0;

            for(/*cItEdgeRow*/; cItEdgeRow != cItEdgeRowEnd; ++cItEdgeRow){
                
                if((*cItEdgeRow).Oriented() == 0){
                    if((*cItRow).GetID() == (*cItEdgeRow).GetStartVertexID()
                            && (*cItColumn).GetID() == (*cItEdgeRow).GetEndVertexID()){
                                //std::cout<< "Yes\t";
                                std::cout << (*cItEdgeRow).GetDataEdge() << "\t";
                                IsConnected = true;
                                break;
                            }
                    
                    if((*cItRow).GetID() == (*cItEdgeRow).GetEndVertexID()
                            && (*cItColumn).GetID() == (*cItEdgeRow).GetStartVertexID()){
                                //std::cout<< "Yes\t";
                                std::cout << (*cItEdgeRow).GetDataEdge() << "\t";
                                IsConnected = true;
                                break;
                            }

                }
                if((*cItEdgeRow).Oriented() == 1){
                    if((*cItEdgeRow).GetStartVertexID() == (*cItRow).GetID()
                            && (*cItEdgeRow).GetEndVertexID() == (*cItColumn).GetID() ){
                        
                        //std::cout<< "Yes\t";
                        std::cout << (*cItEdgeRow).GetDataEdge() << "\t";
                        IsConnected = true;
                        break;
                        
                    }
                }
            }

            if(IsConnected == false){
                std::cout << "No\t";
            }
        }
        std::cout << std::endl;
    }

    

}

#endif //PRINT_ADJECENCY_MATRIX_H