#ifndef EDGE_H
#define EDGE_H

#include "SharedPtr.h"
#include "WeakPtr.h"
#include "Dictionary.h"
#include "Vertex.h"

template<typename TypeNameVertex, typename TypeDataVertex, typename TypeDataEdge> class Edge{

private:

    TypeDataEdge data_;
    bool isOriented_;
    WeakPtr< Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > vertexStart_;
    WeakPtr< Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > vertexEnd_;

public:

    Edge(SharedPtr< Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > vertexStart,
         SharedPtr< Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > vertexEnd,
         TypeDataEdge data = TypeDataEdge(),
         bool isOriented = 0) : data_(data),
                            isOriented_(Oriented),
                            vertexStart_(vertexStart),
                            vertexEnd_(vertexEnd)
    {}

    TypeDataEdge& GetData() {return data_;}
    TypeDataEdge GetData() const {return data_;}
    
    void SetData(TypeDataEdge const & data){
        data_ = data;
    }

    bool Oriented() const
    {
        return isOriented_;
    }

    WeakPtr< Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > GetVertexStart() {return vertexStart_;}
    WeakPtr< Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > GetVertexEnd() {return vertexEnd_;}

};


#endif //EDGE_H