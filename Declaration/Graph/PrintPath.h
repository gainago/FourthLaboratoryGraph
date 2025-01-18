#ifndef PRINT_PATH_H
#define PRINT_PATH_H

#include "Path.h"
#include <iostream>
#include "InputOutputIndex.h"

template < typename TypeDataVertex, typename TypeDataEdge> 
void PrintPath(Path<TypeDataVertex, TypeDataEdge> & path)
{
    typename LinkedList<SharedPtr<Vertex<TypeDataVertex, TypeDataEdge> > >::Iterator it = path.listVertices_.Begin();
    typename LinkedList<SharedPtr<Vertex<TypeDataVertex, TypeDataEdge> > >::Iterator itEnd = path.listVertices_.End();

    for(/*it*/; it != itEnd; ++it){
        OutputIndex((*it).Get().GetID());
        std::cout << "\t";
    }

    std::cout << std::endl;
}


#endif //PRINT_PATH_H