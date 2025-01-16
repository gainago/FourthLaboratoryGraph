#ifndef VERTEX_H
#define VERTEX_H

#include "Dictionary.h"
#include "SharedPtr.h"
#include "GetHashCode.h"
#include "Index.h"
#include "Edge.h"

// TypeDataVertex должнысодержать дружественный метод oparator<< (выводится на экран)

template <typename TypeDataVertex, typename TypeDataEdge> class Vertex{
//нам нужно различать два ребра с одинаковыми характеристиками(между одними и теми же вершинами, с одинаковыми значениями)
typedef Index ID;

private:

    ID thisID_;
    TypeDataVertex dataVertex_;
    //храним не копию а указатель для того чтобы данные можно было менять из графа, без обращения к двум вершинам и т.д.
    Dictionary<ID, SharedPtr<Edge<TypeDataVertex, TypeDataEdge> > > dictionaryEdges_;
public:

    Vertex(ID thisID, TypeDataVertex dataVertex = TypeDataVertex()) : thisID_(thisID), dataVertex_(dataVertex),
        dictionaryEdges_(GetHashCodeIndex)
    {}
    //запретил чтобы не создавалось ситуаций когда три вершины имеют одно и то же ребро
    Vertex(Vertex<TypeDataVertex, TypeDataEdge> const & other) = delete;

    ID & GetID()
    {
        return thisID_;
    }

    ID const & GetID() const
    {
        return thisID_;
    }

    TypeDataVertex & GetDataVertex()
    {
        return dataVertex_;
    }

    TypeDataVertex const & GetDataVertex() const
    {
        return dataVertex_;
    }

    bool Contains(ID idEdge) const
    {
        return dictionaryEdges_.Contains(idEdge);
    }

    void AddEdge(SharedPtr<Edge<TypeDataVertex, TypeDataEdge> > edge)
    {
        dictionaryEdges_.Add((edge.Get()).GetID(), edge);
    }

    void RemoveEdge(SharedPtr<Edge<TypeDataVertex, TypeDataEdge> > edge)
    {
        dictionaryEdges_.Remove((edge.Get()).GetID());
    }

    void RemoveEdge(ID edgeID)
    {
        dictionaryEdges_.Remove(edgeID);
    }

    Edge<TypeDataVertex, TypeDataEdge> & GetEdge(ID edgeID)
    {
        return (dictionaryEdges_.Get(edgeID)).Get();
    }

    Edge<TypeDataVertex, TypeDataEdge> const & GetEdge(ID edgeID) const
    {
        return (dictionaryEdges_.Get(edgeID)).Get();
    }

    class IteratorEdge{
    private:
        typename Dictionary<ID, SharedPtr<Edge<TypeDataVertex, TypeDataEdge> > >::Iterator it_;
    public:
        IteratorEdge(typename Dictionary<ID, SharedPtr<Edge<TypeDataVertex, TypeDataEdge> > >::Iterator it) : it_(it) {}
        IteratorEdge(IteratorEdge const & other) : it_(other.it_) {}

        void operator++() 
        {
            ++it_;
        }
        Edge<TypeDataVertex, TypeDataEdge> & operator*() 
        {
            return ((*it_).GetSecond()).Get();
        }

        bool operator==(IteratorEdge const & other) const
        {
            return other.it_ == this->it_;
        }

        bool operator!=(IteratorEdge const & other) const
        {
            return !(*this == other);
        } 
        
    };

    IteratorEdge Begin()
    {
        return dictionaryEdges_.Begin();
    }

    IteratorEdge End()
    {
        return dictionaryEdges_.End();
    }

    class ConstIteratorEdge{
    private:
        typename Dictionary<ID, SharedPtr<Edge<TypeDataVertex, TypeDataEdge> > >::ConstIterator it_;
    public:
        ConstIteratorEdge(typename Dictionary<ID, SharedPtr<Edge<TypeDataVertex, TypeDataEdge> > >::ConstIterator it) : it_(it) {}
        ConstIteratorEdge(ConstIteratorEdge const & other) : it_(other.it_) {}

        void operator++() 
        {
            ++it_;
        }
        Edge<TypeDataVertex, TypeDataEdge> const & operator*() const
        {
            return ((*it_).GetSecond()).Get();
        }

        bool operator==(ConstIteratorEdge const & other) const
        {
            return other.it_ == this->it_;
        }

        bool operator!=(ConstIteratorEdge const & other) const
        {
            return !(*this == other);
        } 
        
    };

    ConstIteratorEdge ConstBegin() const
    {
        return dictionaryEdges_.ConstBegin();
    }

    ConstIteratorEdge ConstEnd() const
    {
        return dictionaryEdges_.ConstEnd();
    }

};

#endif //VERTEX_H