#ifndef EDGE_H
#define EDGE_H

#include "SharedPtr.h"
#include "WeakPtr.h"
#include "Dictionary.h"
#include "Vertex.h"

template< typename DataVertex, typename DataEdge> class Edge{

private:

    DataEdge data_;

    WeakPtr< Vertex<DataVertex, DataEdge> > vertexFirst_;
    WeakPtr< Vertex<DataVertex, DataEdge> > vertexSecond_;

public:

    Edge(SharedPtr< Vertex<DataVertex, DataEdge> > vertexFirst,
         SharedPtr< Vertex<DataVertex, DataEdge> > vertexSecond,
         DataEdge data = DataEdge()) : data_(data),
                                    vertexFirst_(vertexFirst),
                                    vertexSecond_(vertexSecond)
    {}

    DataEdge& GetData() {return data_;}
    DataEdge GetData() const {return data_;}
    
    void SetData(DataEdge const & data){
        data_ = data;
    }

    WeakPtr< Vertex<DataVertex, DataEdge> > GetFirstVertex() {return vertexFirst_;}
    WeakPtr< Vertex<DataVertex, DataEdge> > GetSecondVertex() {return vertexSecond_;}

};


#endif //EDGE_H