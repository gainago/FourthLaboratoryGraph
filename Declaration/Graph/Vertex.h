#ifndef VERTEX_H
#define VERTEX_H

#include "Dictionary.h"
#include "SharedPtr.h"
#include "GetHashCode.h"

template <typename TypeNameVertex, typename TypeDataVertex, typename TypeDataEdge> class Edge;


template <typename TypeNameVertex, typename TypeDataVertex, typename TypeDataEdge> class Vertex{

private:
    TypeNameVertex name_;
    TypeDataVertex data_;
    Dictionary<int, SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > > dictionaryEdges_;

public:

    Vertex(TypeNameVertex const & name, TypeDataVertex const & data = TypeDataVertex()) : name_(name),
                                                                                    data_(data),
                                                                                    dictionaryEdges_(GetHashCodeInt) {}

    TypeDataVertex& GetData() {return data_;}
    TypeDataVertex GetData() const {return data_;}

    TypeNameVertex& GetName() {return name_;}
    TypeNameVertex GetName() const {return name_;}

    void SetData(TypeDataVertex const & data)
    {
        data_ = data;
    }

    void SetName(TypeNameVertex const & name)
    {
        name_ = name;
    }

    int GetCountOfIncidentalEdges() const {return dictionaryEdges_.GetLength();}

    typename Dictionary<int, SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::Iterator BeginIteratorOfIncidentalEdges()
    {
        return dictionaryEdges_.Begin();
    }

    typename Dictionary<int, SharedPtr< Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::Iterator EndIteratorOfIncidentalEdges()
    {
        return dictionaryEdges_.End();
    }

    class IteratorEdge{
    private:
        typename Dictionary<int, SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::Iterator it_;

    public:

        IteratorEdge(typename Dictionary<int, SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::Iterator it) : it_(it) {}

        IteratorEdge(IteratorEdge const & other) : it_(other.it_) {}

        void operator++()
        {
            ++it_;
        }

        bool operator==(IteratorEdge const & other)
        {
            return this->it_ == other.it_;
        }

        bool operator!=(IteratorEdge const & other)
        {
            return !((*this) == other);
        }

        void operator=(IteratorEdge const & other)
        {
            this->it_ == other.it_;
        }

        MyNamespace::Pair< const int, SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > > & operator*()
        {
            return (*it_);
        }



    };

    IteratorEdge Begin()
    {
        return IteratorEdge(dictionaryEdges_.Begin());
    }

    IteratorEdge End()
    {
        return IteratorEdge(dictionaryEdges_.End());
    }


    class ConstIteratorEdge{
    private:
        typename Dictionary<int, SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::ConstIterator it_;

    public:

        ConstIteratorEdge(typename Dictionary<int, SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > >::ConstIterator it) : it_(it) {}

        ConstIteratorEdge(ConstIteratorEdge const & other) : it_(other.it_) {}

        void operator++()
        {
            ++it_;
        }

        bool operator==(ConstIteratorEdge const & other) const
        {
            return this->it_ == other.it_;
        }

        bool operator!=(ConstIteratorEdge const & other) const
        {
            return !((*this) == other);
        }

        void operator=(ConstIteratorEdge const & other) const
        {
            this->it_ == other.it_;
        }

        MyNamespace::Pair< const int, SharedPtr<Edge<TypeNameVertex, TypeDataVertex, TypeDataEdge> > > const & operator*() const
        {
            return (*it_);
        }
    };

    ConstIteratorEdge ConstBegin() const
    {
        return ConstIteratorEdge(dictionaryEdges_.ConstBegin());
    }

    ConstIteratorEdge ConstEnd() const
    {
        return ConstIteratorEdge(dictionaryEdges_.ConstEnd());
    }

    
};

#endif //VERTEX_H