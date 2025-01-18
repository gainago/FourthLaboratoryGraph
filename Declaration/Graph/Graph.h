#ifndef GRAPH_H
#define GRAPH_H

#include "Index.h"
#include "Dictionary.h"
#include "Edge.h"
#include "Vertex.h"
#include "Path.h"
#include "ReturnValue.h"
#include "LinkedList.h"
//#include "iostream"


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

    //возвращает вершины между начальной и конечной включая их
    //не возвращает ребра между вершинами потому что ребра его интересуют только в контексте связности
    MyNamespace::ReturnValue< Path<TypeDataVertex, TypeDataEdge> > BreadthFirstSearch(ID idVertexStart, ID idVertexEnd) // ищет какой-нибудь путь между двумя вершинами
    {
        Dictionary<ID, bool> dictionaryVisitedVertices(GetHashCodeIndex);

        //key = ID vertex destination, value = ID vertex previous destination; it helps us take a path
        Dictionary<ID, ID> dictionaryPreviousVertex(GetHashCodeIndex); 
        LinkedList<ID> queue;

        if(idVertexStart == idVertexEnd){
            Path<TypeDataVertex, TypeDataEdge> path;
            path.listVertices_.Append(this->GetSharedPointerVertex(idVertexStart));
            return MyNamespace::ReturnValue< Path<TypeDataVertex, TypeDataEdge> >(1, path);
        }

        this->GetSharedPointerVertex(idVertexStart); // check that vertices are exists
        this->GetSharedPointerVertex(idVertexEnd);
        

        queue.Prepend(idVertexStart);
        dictionaryVisitedVertices.Add(idVertexStart, 1);

        while(queue.GetLength() > 0){
            ID idCurrentVertex = queue.Get(0);
            queue.Remove(0);

            if(idCurrentVertex == idVertexEnd){
                break;
            }

            LinkedList<SharedPtr<Vertex<TypeDataVertex, TypeDataEdge> > > listAdjacentVertices;

            listAdjacentVertices = this->GetAdjacentVertices(idCurrentVertex);

            typename LinkedList<SharedPtr<Vertex<TypeDataVertex, TypeDataEdge> > >::Iterator itAdjacentVertices = listAdjacentVertices.Begin();
            typename LinkedList<SharedPtr<Vertex<TypeDataVertex, TypeDataEdge> > >::Iterator itAdjacentVerticesEnd = listAdjacentVertices.End();

            for(/*itAdjacentVertices*/; itAdjacentVertices != itAdjacentVerticesEnd; ++itAdjacentVertices){
                
                ID idCurrentAdjacentVertex = (*itAdjacentVertices).Get().GetID();
                if(!dictionaryVisitedVertices.Contains(idCurrentAdjacentVertex)){
                    queue.Append(idCurrentAdjacentVertex);
                    dictionaryVisitedVertices.Add(idCurrentAdjacentVertex, 1);
                    dictionaryPreviousVertex.Add(idCurrentAdjacentVertex, idCurrentVertex);

                }

            }

        }

        if(!dictionaryPreviousVertex.Contains(idVertexEnd)){
            return MyNamespace::ReturnValue< Path<TypeDataVertex, TypeDataEdge> >(0, Path<TypeDataVertex, TypeDataEdge>());
        }

        ID idPreviousVertex = idVertexEnd;

        Path<TypeDataVertex, TypeDataEdge> path;

        while(true){

            path.listVertices_.Prepend(this->GetSharedPointerVertex(idPreviousVertex));

            if(idPreviousVertex == idVertexStart){
                break;
            }

            idPreviousVertex = dictionaryPreviousVertex.Get(idPreviousVertex);

            
        }

        return MyNamespace::ReturnValue< Path<TypeDataVertex, TypeDataEdge> >(1, path);



    }


    //возвращает пару из словаря, позволяющего получить наилучший путь, и словаря показывающего наименьшую стоимость пути
    //вычисление проводится относительно вершины с индексом idSourceVertex
    //не защищен от переполнения TypeDataEdge в пользу минимальных требований в данному типу
    //Обратите внимание что при наличии циклов, суммарно отрицательного веса, 
    //или (что то же самое) при наличии неориентированных ребер отрицательного веса, алгоритм бросит исключение
    MyNamespace::Pair<Dictionary<Index, Index>, Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> > > 
                                                        FordBellmanAlgorithm(Index idSourceVertex)
    {
        //Index - имя вершины, Pair.First() == false булевый параметр означающий вес равный бесконечности(устанавливается в самом начале)
        //TypeDataEdge минимальная сумма весов ребер, от исходной вершины до текущей 
        Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> > dictionaryScales(GetHashCodeIndex);
        //когда алгоритм найдет лучший путь до вершины, имя которое это первый параметр
        //он заменит(или создаст) имя второй вершины, на имя текущей в алгоритме
        Dictionary<Index, Index> dictionaryAncestor(GetHashCodeIndex);

        typename Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > >::ConstIterator cIt = dictionaryVertex_.ConstBegin();
        typename Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > >::ConstIterator cItEnd = dictionaryVertex_.ConstEnd();

        for(/*cIt*/; cIt != cItEnd; ++cIt){
            dictionaryScales.Add((*cIt).GetID(), MyNamespace::Pair<bool, TypeDataEdge>(0, TypeDataEdge()));
        }

        //установили значение исходной вершины
        dictionaryScales.Get(idSourceVertex) = MyNamespace::Pair<bool, TypeDataEdge>(1, TypeDataEdge());

        //теперь пройдемся dictionaryVertices_.GetLength() - 1 раз по всем ребрам, по известной теореме после i-того прохода
        //наше, найденное расстояние от source до какой либо вершины
        //будет не больше такого же расстояния для любого пути содержащего i ребер
        //соответственно после dictionaryVertices_.GetLength() - 1 проходов 
        //наше, найденное расстояние будет не больше расстояния для любого другого пути

        for(int pass = 1; pass < dictionaryVertex_.GetLength(); ++pass){

            //теперь пробегаемся по всем ребрам и смотрим, можно ли уменьшить вес текущего пути
            typename Dictionary<ID, SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > >::ConstIterator cIt = dictionaryEdge_.ConstBegin();
            typename Dictionary<ID, SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > >::ConstIterator cItEnd = dictionaryEdge_.ConstEnd();

            for(/*cIt*/; cIt != cItEnd; ++cIt){

                Edge<TypeDataVertex, TypeDataEdge> const & currentEdge = (*cIt).Get();

                Index idStartVertex = currentEdge.GetStartVertexID();
                Index idEndVertex = currentEdge.GetEndVertexID();

                MyNamespace::Pair<bool, TypeDataEdge>& scaleStartVertex = dictionaryScales.Get(idStartVertex);
                MyNamespace::Pair<bool, TypeDataEdge>& scaleEndVertex = dictionaryScales.Get(idEndVertex);

                if(currentEdge.Oriented() == 0){

                    //если пути до обеих вершин не равны бесконечности
                    if(dictionaryScales.Get(idStartVertex).GetFirst() == 1 &&){

                    }

                }



            }
        }

    }

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

            if((*itEdge).Oriented() == 0){
                if((*itEdge).GetStartVertexID() == idVertexFirst && (*itEdge).GetEndVertexID() == idVertexSecond){

                    listEdges.Append(this->GetSharedPointerEdge((*itEdge).GetID()));
                    //std::cout << MyString(((*itEdge).GetID()).GetChar()) << std::endl;
                    continue;
                }

                if((*itEdge).GetStartVertexID() == idVertexSecond && (*itEdge).GetEndVertexID() == idVertexFirst){

                    listEdges.Append(this->GetSharedPointerEdge((*itEdge).GetID()));
                    continue;
                }
            }
            else {
                if((*itEdge).GetStartVertexID() == idVertexFirst && (*itEdge).GetEndVertexID() == idVertexSecond){

                    listEdges.Append(this->GetSharedPointerEdge((*itEdge).GetID()));
                    continue;
                }
            }

        }

        return listEdges;

    }
//если соединен с собой то вернет в том числе и себя
    LinkedList<SharedPtr<Vertex<TypeDataVertex, TypeDataEdge> > > GetAdjacentVertices(ID const & idVertex)
    {
        SharedPtr<Vertex< TypeDataVertex, TypeDataEdge> > pVertex;

        LinkedList<SharedPtr<Vertex< TypeDataVertex, TypeDataEdge> > > listVertices;

        try{

            pVertex = this->GetSharedPointerVertex(idVertex);

        }
        catch(char const *)
        {
            return listVertices;
        }

        typename Vertex<TypeDataVertex, TypeDataEdge>::IteratorEdge itEdge = pVertex.Get().Begin();// помним что Vertex копировать нельзя
        typename Vertex<TypeDataVertex, TypeDataEdge>::IteratorEdge itEdgeEnd = pVertex.Get().End();

        ID currentAdjacentVertex;
        

        for(/*itEdge*/; itEdge != itEdgeEnd; ++itEdge){

            bool foundPossibleVertex = 0;

            if((*itEdge).Oriented() == 0){
                if((*itEdge).GetStartVertexID() == idVertex && (*itEdge).GetEndVertexID() == idVertex){

                    currentAdjacentVertex = (*itEdge).GetStartVertexID();
                    foundPossibleVertex = 1;
                    //listVertices.Append(this->GetSharedPointerEdge((*itEdge).GetID()));
                    //std::cout << MyString(((*itEdge).GetID()).GetChar()) << std::endl;
                   
                }

                if((*itEdge).GetStartVertexID() == idVertex && (*itEdge).GetEndVertexID() != idVertex){
                    currentAdjacentVertex = (*itEdge).GetEndVertexID();
                    foundPossibleVertex = 1;
                    
                }

                if((*itEdge).GetStartVertexID() != idVertex && (*itEdge).GetEndVertexID() == idVertex){
                    currentAdjacentVertex = (*itEdge).GetStartVertexID();
                    foundPossibleVertex = 1;
                    
                }
            }
            else {
                if((*itEdge).GetStartVertexID() == idVertex){

                    currentAdjacentVertex = (*itEdge).GetEndVertexID();
                    foundPossibleVertex = 1;
                }
            }

            //пробежимся по листу чтобы проверить добавили ли мы уже указатель на текущую вершину
            //(вдруг есть два ребра между одними и теми же вершинами)
            if(foundPossibleVertex == 1){

                bool needAppend = 1;

                typename LinkedList<SharedPtr<Vertex< TypeDataVertex, TypeDataEdge> > >::Iterator it = listVertices.Begin();
                typename LinkedList<SharedPtr<Vertex< TypeDataVertex, TypeDataEdge> > >::Iterator itEnd = listVertices.End();

                for(/*it*/; it != itEnd; ++it){
                    
                    if((*it).Get().GetID() == currentAdjacentVertex){
                        needAppend = 0;
                        break;
                    }
                }
                if(needAppend){
                    listVertices.Append(this->GetSharedPointerVertex(currentAdjacentVertex));
                }

            }

        }

        return listVertices;

    }

    SharedPtr<Edge< TypeDataVertex, TypeDataEdge> > 
                                FindMininumEdge(LinkedList<SharedPtr<Edge< TypeDataVertex, TypeDataEdge> > >& listEdges)
    {

        if(listEdges.GetLength() == 0){
            throw "There are no edges";
        }

        typename LinkedList<SharedPtr<Edge< TypeDataVertex, TypeDataEdge> > >::Iterator it = listEdges.Begin();
        typename LinkedList<SharedPtr<Edge< TypeDataVertex, TypeDataEdge> > >::Iterator itEnd = listEdges.End();

        SharedPtr<Edge< TypeDataVertex, TypeDataEdge> > pMinimumEdge = *it;

        for(/*it*/; it != itEnd; ++it){
            if((*it).Get().GetDataEdge() < pMinimumEdge.Get().GetDataEdge()){
                pMinimumEdge = (*it);
            }
        }

        return pMinimumEdge;


    }
};


#endif //GRAPH_H