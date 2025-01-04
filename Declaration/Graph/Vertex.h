#ifndef VERTEX_H
#define VERTEX_H

#include "Dictionary.h"
#include "SharedPtr.h"
#include "GetHashCode.h"

template <typename DataVertex, typename DataEdge> class Edge;


template <typename DataVertex, typename DataEdge> class Vertex{

private:
    DataVertex data_;
    Dictionary<int, SharedPtr<Edge<DataVertex, DataEdge> > > dictionaryEdges_;

public:

    Vertex(DataVertex data = DataVertex()) : data_(data), dictionaryEdges_(GetHashCodeInt) {}

    DataVertex& GetData() {return data_;}
    DataVertex GetData() const {return data_;}
    void SetData(DataVertex const & data)
    {
        data_ = data;
    }

    int GetCountOfIncidentalEdges() const {return dictionaryEdges_.GetLength();}

    typename Dictionary<int, SharedPtr<Edge<DataVertex, DataEdge> > >::Iterator BeginIteratorOfIncidentalEdges()
    {
        return dictionaryEdges_.Begin();
    }

    typename Dictionary<int, SharedPtr< Edge< DataVertex, DataEdge> > >::Iterator EndIteratorOfIncidentalEdges()
    {
        return dictionaryEdges_.End();
    }

    
};

#endif //VERTEX_H