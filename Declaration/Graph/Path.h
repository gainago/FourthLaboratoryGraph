#ifndef PATH_H
#define PATH_H

#include "Edge.h"
#include "Vertex.h"
#include "LinkedList.h"

//путь начинается и заканчивается вершиной, то есть длинна listVertices_.GetLength() = listEdges_.GetLength() + 1 
template <typename TypeDataVertex, typename TypeDataEdge> class Path{
public:

    LinkedList<SharedPtr<Edge<TypeDataVertex, TypeDataEdge> > > listEdges_; //нуу спорно что это надо
    LinkedList<SharedPtr<Vertex<TypeDataVertex, TypeDataEdge> > > listVertices_;

public:

        Path() : listVertices_() {}

        DynamicArray<Edge < TypeDataVertex, TypeDataEdge> > GetPath()
        {
            return listVertices_;
        } 
};

#endif //PATH_H