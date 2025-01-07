#ifndef EDGE_H
#define EDGE_H

#include "Dictionary.h"
#include "MyString.h"

template <typename TypeDataVertex, typename TypeDataEdge> class Edge{
    typedef MyString ID;
private:

    ID thisID_;
    ID startVertexID_;
    ID endVertexID_;
    bool isOriented_;
    TypeDataEdge dataEdge_;
public:
//конструктор копирования в Edge позволителен, поскольку он не содерит никаких указателей,
// хотя тогда у вершины и ребра отличающийся интерфейс, но не думаю что это плохо 
    Edge(ID thisID, ID startVertexID, ID endVertexID, bool isOriented, TypeDataEdge dataEdge = TypeDataEdge()) : 
        thisID_(thisID), startVertexID_(startVertexID), endVertexID_(endVertexID), isOriented_(isOriented), dataEdge_(dataEdge)
    {}

    ID & GetID()
    {
        return thisID_;
    }

    ID const & GetID() const
    {
        return thisID_;
    }

    ID & GetStartVertexID()
    {
        return startVertexID_;
    }

    ID const & GetStartVertexID() const
    {
        return startVertexID_;
    } 

    ID & GetEndVertexID()
    {
        return endVertexID_;
    }

    ID const & GetEndVertexID() const
    {
        return endVertexID_;
    }

    bool & Oriented()
    {
        return isOriented_;
    }

    bool const & Oriented() const
    {
        return isOriented_;
    }

    TypeDataEdge & GetDataEdge()
    {
        return dataEdge_;
    }

    TypeDataEdge const & GetDataEdge() const
    {
        return dataEdge_;
    }



};


#endif //EDG_H