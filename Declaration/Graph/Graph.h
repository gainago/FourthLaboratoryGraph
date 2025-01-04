#ifndef GRAPH_H
#define GRAPH_H

#include "GetHashCode.h"
#include "ReturnValue.h"
#include "Dictionary.h"
#include "SharedPtr.h"
#include "WeakPtr.h"
#include "Vertex.h"
#include "Edge.h"

template <typename DataIndex, typename DataVertex, typename DataEdge> class Graph{

private:

    Dictionary<DataIndex, SharedPtr<Vertex<DataVertex, DataEdge> > > dictionaryVertices_;

public:

    Graph(int (*GetHashCodeIndex)(DataIndex const &)) : dictionaryVertices_(GetHashCodeIndex) {}

    void AddVertex(DataIndex const & index, DataVertex const & data)
    {
        SharedPtr<Vertex<DataVertex, DataEdge> > currentPtr = MakeShared<Vertex<DataVertex, DataEdge> >(data);

        dictionaryVertices_.Add(index, currentPtr);
    }

    bool isContaince(DataIndex const & index) const
    {
        return dictionaryVertices_.isContains(index);
    }

    void Remove(DataIndex const & index)
    {
        dictionaryVertices_.Remove(index);
    }

    SharedPtr<Vertex<DataVertex, DataEdge> > Get(DataIndex const & index)
    {
        return (dictionaryVertices_.Get(index));
    }

    SharedPtr<Edge<DataVertex, DataEdge> > Connect(DataIndex const & indexFirst,
                                                    DataIndex const & indexSecond,
                                                    DataEdge const & dataEdge)
    {
        SharedPtr<Vertex<DataVertex, DataEdge> > vertexPtrFirst = dictionaryVertices_.Get(indexFirst);
        SharedPtr<Vertex<DataVertex, DataEdge> > vertexPtrSecond = dictionaryVertices_.Get(indexSecond);

        SharedPtr<Edge<DataVertex, DataEdge> > edgePtr = MakeShared<Edge<DataVertex, DataEdge> >(vertexPtrFirst,
                                                                                                vertexPtrSecond,
                                                                                                dataEdge);
        return edgePtr;
        
    }

    int GetLength() const
    {
        return dictionaryVertices_.GetLength();
    }



};

#endif //GRAPH_H