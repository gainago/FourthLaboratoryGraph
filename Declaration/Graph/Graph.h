#ifndef GRAPH_H
#define GRAPH_H

#include "Index.h"
#include "Dictionary.h"
#include "Edge.h"
#include "Vertex.h"
#include "Path.h"
#include "ReturnValue.h"
#include "LinkedList.h"


//TypeDataVertex, TypeDataEdge
template < typename TypeDataVertex, typename TypeDataEdge> class Graph{
    // нам нужно отличать каждую вершину и каждое ребро друг от друга, к примеру для алгоритмов нахождения расстояние
    typedef Index ID;

private:
    Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > > dictionaryVertex_;
    Dictionary<ID, SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > > dictionaryEdge_;

public:
    Graph() : dictionaryVertex_(GetHashCodeIndex), dictionaryEdge_(GetHashCodeIndex) {}

    void AddVertex(ID idVertex, TypeDataVertex dataVertex = TypeDataVertex())
    {
        SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > pointer = MakeShared<Vertex<TypeDataVertex, TypeDataEdge> >(idVertex, dataVertex);
        dictionaryVertex_.Add(idVertex, pointer);
    }

    SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > GetSharedPointerVertex(ID idVertex)
    {
        return dictionaryVertex_.Get(idVertex);
    }

    SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > const & GetSharedPointerVertex(ID idVertex) const
    {
        return dictionaryVertex_.Get(idVertex);
    }

    void AddEdge(ID nameEdge, bool isOriented,
                    ID idVertexStart,
                    ID idVertexEnd, 
                    TypeDataEdge dataEdge = TypeDataEdge())
    {
        
        SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > pVertexBegin = this->GetSharedPointerVertex(idVertexStart);
        SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > pVertexEnd = this->GetSharedPointerVertex(idVertexEnd);

        SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > pEdge = 
            MakeShared<Edge<TypeDataVertex, TypeDataEdge> >(nameEdge, idVertexStart, idVertexEnd, isOriented, dataEdge);
        dictionaryEdge_.Add(nameEdge, pEdge);

        Vertex<TypeDataVertex, TypeDataEdge> & vertexBegin = pVertexBegin.Get();
        Vertex<TypeDataVertex, TypeDataEdge> & vertexEnd = pVertexEnd.Get();

        vertexBegin.AddEdge(pEdge);

        if(idVertexStart != idVertexEnd){
            vertexEnd.AddEdge(pEdge);
        }

    }

    SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > GetSharedPointerEdge(ID idEdge)
    {   
            return dictionaryEdge_.Get(idEdge);  
    }

    SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > const & GetSharedPointerEdge(ID idEdge) const
    {
            return dictionaryEdge_.Get(idEdge);  
    }

    void RemoveEdge(ID const & idEdge)
    {
        SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > pEdgeToRemove = dictionaryEdge_.Get(idEdge);
        ID idStartVertex = pEdgeToRemove.Get().GetStartVertexID();//получили имена вершин котрые содержат это ребро
        ID idEndVertex = pEdgeToRemove.Get().GetEndVertexID();

        SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > pVertexStart = GetSharedPointerVertex(idStartVertex);
        SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > pVertexEnd = GetSharedPointerVertex(idEndVertex);

        Vertex<TypeDataVertex, TypeDataEdge> & vertexStart = pVertexStart.Get();
        Vertex<TypeDataVertex, TypeDataEdge> & vertexEnd = pVertexEnd.Get();

        vertexStart.RemoveEdge(idEdge);

        if(vertexEnd.Contains(idEdge)){//случай наличия петли
            vertexEnd.RemoveEdge(idEdge);
        }

        dictionaryEdge_.Remove(idEdge);
    }

    void RemoveVertex(ID const & idVertex)
    {
        SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > pVertex = GetSharedPointerVertex(idVertex);
        Vertex<TypeDataVertex, TypeDataEdge> & vertexToDelete = pVertex.Get();

        typename Vertex<TypeDataVertex, TypeDataEdge>::IteratorEdge itEdge = vertexToDelete.Begin();
        typename Vertex<TypeDataVertex, TypeDataEdge>::IteratorEdge itEdgeEnd = vertexToDelete.End();

        while(itEdge != itEdgeEnd){             //удаление по итератору у меня не поддерживается
            RemoveEdge((*itEdge).GetID());
            itEdge = vertexToDelete.Begin();
            itEdgeEnd = vertexToDelete.End();
        }

        dictionaryVertex_.Remove(idVertex);
    }
    
    int GetCountOfVertices() const
    {
        return dictionaryVertex_.GetLength();
    }

    int GetCountOfEdges() const
    {
        return dictionaryEdge_.GetLength();
    }
    // Path<TypeDataVertex, TypeDataEdge> BreadthFirstSearch(ID idVertexStart, ID idVertexEnd)
    // {

    // }

    class IteratorVertex{
    private:
        typename Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > >::Iterator it_;
    public:
        IteratorVertex(typename Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > >::Iterator it) 
            : it_(it) {}
        IteratorVertex(IteratorVertex const & other) : it_(other.it_) {}

        void operator++()
        {
            ++it_;
        }

        Vertex<TypeDataVertex, TypeDataEdge> & operator*()
        {
            return ((*it_).GetSecond()).Get();
        }

        bool operator==(IteratorVertex const & other) const
        {
            return this->it_ == other.it_;
        }

        bool operator!=(IteratorVertex const & other) const
        {
            return !(*this == other);
        }

    };

    IteratorVertex Begin()
    {
        return dictionaryVertex_.Begin();
    }

    IteratorVertex End()
    {
        return dictionaryVertex_.End();
    }

    class ConstIteratorVertex{
    private:
        typename Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > >::ConstIterator it_;
    public:
        ConstIteratorVertex(typename Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > >::ConstIterator it) 
            : it_(it) {}
        ConstIteratorVertex(ConstIteratorVertex const & other) : it_(other.it_) {}

        void operator++()
        {
            ++it_;
        }

        Vertex<TypeDataVertex, TypeDataEdge> const & operator*() const
        {
            return ((*it_).GetSecond()).Get();
        }

        bool operator==(ConstIteratorVertex const & other) const
        {
            return this->it_ == other.it_;
        }

        bool operator!=(ConstIteratorVertex const & other) const
        {
            return !(*this == other);
        }

    };

    ConstIteratorVertex ConstBegin() const
    {
        return dictionaryVertex_.ConstBegin();
    }

    ConstIteratorVertex ConstEnd() const
    {
        return dictionaryVertex_.ConstEnd();
    }

//private:
    public:

    LinkedList<SharedPtr<Edge< TypeDataVertex, TypeDataEdge> > >
                                                GetEdgesBetweenAdjacentVertices(ID const & idVertexFirst, ID const & idVertexSecond)
    {
        SharedPtr<Vertex< TypeDataVertex, TypeDataEdge> > pVertexFirst;
        SharedPtr<Vertex< TypeDataVertex, TypeDataEdge> > pVertexSecond;

        LinkedList<SharedPtr<Edge< TypeDataVertex, TypeDataEdge> > > listEdges;

        try{

            pVertexFirst = this->GetSharedPointerVertex(idVertexFirst);
            pVertexSecond = this->GetSharedPointerVertex(idVertexSecond);

        }
        catch(char const *)
        {
            return listEdges;
        }

        typename Vertex<TypeDataVertex, TypeDataEdge>::IteratorEdge itEdge = pVertexFirst.Get().Begin();// помним что Vertex копировать нельзя
        typename Vertex<TypeDataVertex, TypeDataEdge>::IteratorEdge itEdgeEnd = pVertexFirst.Get().End();

        for(/*itEdge*/; itEdge != itEdgeEnd; ++itEdge){

            if(*(itEdge).Oriented() == 0){
                if(*(itEdge).GetStartVertexID() == idVertexFirst && *(itEdge).GetEndVertexID() == idVertexSecond){

                    listEdges.Append(this->GetSharedPointerEdge(*(itEdge).GetID()));
                    continue;
                }

                if(*(itEdge).GetStartVertexID() == idVertexSecond && *(itEdge).GetEndVertexID() == idVertexFirst){

                    listEdges.Append(this->GetSharedPointerEdge(*(itEdge).GetID()));
                    continue;
                }
            }
            else {
                if(*(itEdge).GetStartVertexID() == idVertexFirst && *(itEdge).GetEndVertexID() == idVertexSecond){

                    listEdges.Append(this->GetSharedPointerEdge(*(itEdge).GetID()));
                    continue;
                }
            }

        }

        return listEdges;

    }


};


#endif //GRAPH_H