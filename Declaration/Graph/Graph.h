#ifndef GRAPH_H
#define GRAPH_H

#include "GetHashCode.h"
#include "ReturnValue.h"
#include "Dictionary.h"
#include "SharedPtr.h"
#include "WeakPtr.h"
#include "Vertex.h"
#include "Edge.h"

template <typename TypeNameVertex, typename TypeDataVertex, typename TypeDataEdge> class Graph{

private:

    Dictionary<TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > > dictionaryVertices_;

public:

    Graph(int (*GetHashCodeIndex)(TypeNameVertex const &)) : dictionaryVertices_(GetHashCodeIndex) {}

    void AddVertex(TypeNameVertex const & name, TypeDataVertex const & data)
    {
        SharedPtr<Vertex<TypeNameVertex , TypeDataVertex, TypeDataEdge> > currentPtr = MakeShared<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> >(name, data);

        dictionaryVertices_.Add(name, currentPtr);
    }

    bool Containce(TypeNameVertex const & name) const
    {
        return dictionaryVertices_.Contains(name);
    }

    void Remove(TypeNameVertex const & name)
    {
        dictionaryVertices_.Remove(name);
    }

    SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > Get(TypeNameVertex const & name)
    {
        return (dictionaryVertices_.Get(name));
    }

    SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > const Get(TypeNameVertex const & name) const
    {
        return (dictionaryVertices_.Get(name));
    }

    SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > Connect( TypeNameVertex const & nameFirst,
                                                                            TypeNameVertex const & nameSecond,
                                                                            TypeDataEdge const & dataEdge)
    {
        SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > vertexPtrFirst = dictionaryVertices_.Get(nameFirst);
        SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > vertexPtrSecond = dictionaryVertices_.Get(nameSecond);

        SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > edgePtr = MakeShared<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> >(vertexPtrFirst,
                                                                                                vertexPtrSecond,
                                                                                                dataEdge);
        return edgePtr;
        
    }

    int GetLength() const
    {
        return dictionaryVertices_.GetLength();
    }

    DynamicArray<TypeNameVertex> GetNamesVertices() const
    {
        DynamicArray<TypeNameVertex> returnArray(dictionaryVertices_.GetLength());
        typename Dictionary<TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::ConstIterator it = dictionaryVertices_.ConstBegin();
        typename Dictionary<TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::ConstIterator itEnd = dictionaryVertices_.ConstEnd();

        for(int position = 0; it != itEnd; ++it, position++){
            returnArray[position] = (*it).GetFirst();
        }

        return returnArray;

    }

    class IteratorVertex{
    private:

        typename Dictionary<TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::Iterator it_;
    public:

        IteratorVertex(typename Dictionary<TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::Iterator it) :
            it_(it) {}

        IteratorVertex(IteratorVertex const & it) :
            it_(it.it_) {}
        
        void operator=(IteratorVertex const & other)
        {
            this->it_ = other.it_;
        }

        void operator++()
        {
            ++it_;
        }

        bool operator==(IteratorVertex const & other)
        {
            return this->it_ == other.it_;
        }

        bool operator!=(IteratorVertex const & other)
        {
            return !((*this) == other);
        }

        typename MyNamespace::Pair< const TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > > operator*()
        {
            return *it_;
        }
    };

    IteratorVertex Begin()
    {
        return IteratorVertex(dictionaryVertices_.Begin());
    }

    IteratorVertex End()
    {
        return IteratorVertex(dictionaryVertices_.End());
    }



    class ConstIteratorVertex{
    private:

        typename Dictionary<TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::ConstIterator it_;
    public:

        ConstIteratorVertex(typename Dictionary<TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::ConstIterator it) :
            it_(it) {}

        ConstIteratorVertex(ConstIteratorVertex const & it) :
            it_(it.it_) {}
        
        void operator=(ConstIteratorVertex const & other) const
        {
            this->it_ = other.it_;
        }

        void operator++() 
        {
            ++it_;
        }

        bool operator==(ConstIteratorVertex const & other) const
        {
            return this->it_ == other.it_;
        }

        bool operator!=(ConstIteratorVertex const & other) const
        {
            return !((*this) == other);
        }

        MyNamespace::Pair< const TypeNameVertex, SharedPtr<Vertex<TypeNameVertex, TypeDataVertex, TypeDataEdge> > > const & operator*() const
        {
            return (*it_);
        }
    };

    ConstIteratorVertex ConstBegin() const
    {
        return ConstIteratorVertex(dictionaryVertices_.ConstBegin());
    }

    ConstIteratorVertex ConstEnd() const
    {
        return ConstIteratorVertex(dictionaryVertices_.ConstEnd());
    }

};

#endif //GRAPH_H