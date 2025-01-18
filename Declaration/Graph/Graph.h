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
//#include "InputOutputIndex.h"


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

    MyNamespace::ReturnValue<TypeDataEdge> GetValueOfMinimumWay(Index idSourceVertex, Index idDestinationIndex)
    {
        MyNamespace::Pair<Dictionary<IndexCurrentVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge> >, Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> > >
                pairFromFardBellman = this->FordBellmanAlgorithm(idSourceVertex);
        
        bool isExistWay = (pairFromFardBellman.GetSecond()).Get(idDestinationIndex).GetFirst();
        TypeDataEdge travelCost = (pairFromFardBellman.GetSecond()).Get(idDestinationIndex).GetSecond();
        
        
        
        return MyNamespace::ReturnValue<TypeDataEdge>(isExistWay, travelCost);

    }

    Path<TypeDataVertex, TypeDataEdge> GetMinimumWay(Index idSourceVertex, Index idDestinationIndex)
    {
    
        Dictionary<IndexCurrentVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge> > dictionaryAncestor(GetHashCodeIndex);

        dictionaryAncestor = this->FordBellmanAlgorithm(idSourceVertex).GetFirst();

        Path<TypeDataVertex, TypeDataEdge> path;


        //если не содержит значит такого пути нет
        if(!dictionaryAncestor.Contains(idDestinationIndex)){
            return path;
        }

        //распутываем путь с конца к началу
        Index idCurrentVertex = idDestinationIndex;

        while(true){

            path.listVertices_.Prepend(this->GetSharedPointerVertex( idCurrentVertex));

            if(idCurrentVertex == idSourceVertex){
                break;
            }
            else{
                path.listEdges_.Prepend(this->GetSharedPointerEdge( dictionaryAncestor.Get(idCurrentVertex).GetSecond()));
            }

            idCurrentVertex = dictionaryAncestor.Get(idCurrentVertex).GetFirst();



        }

        return path;
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
    typedef Index IndexCurrentVertex;
    typedef Index IndexPreviousVertex;
    typedef Index IndexConnectingEdge;
    MyNamespace::Pair<Dictionary<IndexCurrentVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge> >, Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> > > 
                                                        FordBellmanAlgorithm(Index idSourceVertex)
    {
        //Index - имя вершины, Pair.First() == false булевый параметр означающий вес равный бесконечности(устанавливается в самом начале)
        //TypeDataEdge минимальная сумма весов ребер, от исходной вершины до текущей 
        Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> > dictionaryScales(GetHashCodeIndex);
        //когда алгоритм найдет лучший путь до вершины, имя которое это первый параметр
        //он заменит(или создаст) имя второй вершины, на имя текущей в алгоритме
        Dictionary<IndexCurrentVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge> > dictionaryAncestor(GetHashCodeIndex);

        typename Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > >::ConstIterator cItVertex = dictionaryVertex_.ConstBegin();
        typename Dictionary<ID, SharedPtr< Vertex<TypeDataVertex, TypeDataEdge> > >::ConstIterator cItVertexEnd = dictionaryVertex_.ConstEnd();

        for(/*cIt*/; cItVertex != cItVertexEnd; ++cItVertex){
            dictionaryScales.Add((*cItVertex).GetSecond().Get().GetID(), MyNamespace::Pair<bool, TypeDataEdge>(0, TypeDataEdge()));
        }

        //установили значение исходной вершины
        dictionaryScales.Get(idSourceVertex) = MyNamespace::Pair<bool, TypeDataEdge>(1, TypeDataEdge());

        //теперь пройдемся dictionaryVertices_.GetLength() - 1 раз по всем ребрам, по известной теореме после i-того прохода
        //наше, найденное расстояние от source до какой либо вершины
        //будет не больше такого же расстояния для любого пути содержащего i ребер
        //соответственно после dictionaryVertices_.GetLength() - 1 проходов 
        //наше, найденное расстояние будет не больше расстояния для любого другого пути

        for(int pass = 1; pass < dictionaryVertex_.GetLength(); ++pass){

            typename Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> >::Iterator itScales = dictionaryScales.Begin();
            typename Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> >::Iterator itScalesEnd = dictionaryScales.End();

            // for(/*itScales*/; itScales != itScalesEnd; ++itScales){
            //     OutputIndex( (*itScales).GetFirst()); std::cout << "\t";
            // }

            // std::cout << std::endl;

            // typename Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> >::Iterator itScales2 = dictionaryScales.Begin();

            // for(/*itScales*/; itScales2 != itScalesEnd; ++itScales2){
                
            //     if((*itScales2).GetSecond().GetFirst() == 0){
            //         std::cout << "NO\t";
            //     }
            //     else{
            //         std::cout << (*itScales2).GetSecond().GetSecond() << "\t";
            //     }
            // }

            // std::cout << std::endl;

            

            //теперь пробегаемся по всем ребрам и смотрим, можно ли уменьшить вес текущего пути
            typename Dictionary<ID, SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > >::ConstIterator cIt = dictionaryEdge_.ConstBegin();
            typename Dictionary<ID, SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > >::ConstIterator cItEnd = dictionaryEdge_.ConstEnd();

            for(/*cIt*/; cIt != cItEnd; ++cIt){

                Edge<TypeDataVertex, TypeDataEdge> const & currentEdge = (*cIt).GetSecond().Get();

                Index idStartVertex = currentEdge.GetStartVertexID();
                Index idEndVertex = currentEdge.GetEndVertexID();

                MyNamespace::Pair<bool, TypeDataEdge>& scaleStartVertex = dictionaryScales.Get(idStartVertex);
                MyNamespace::Pair<bool, TypeDataEdge>& scaleEndVertex = dictionaryScales.Get(idEndVertex);

                if(currentEdge.Oriented() == 0){

                    //если пути до обеих вершин не равны бесконечности
                    if(scaleStartVertex.GetFirst() == 1 && scaleEndVertex.GetFirst() == 1){

                        //если нашли лучший путь для второй вершины,
                        //то заменяем ее вес на вес первой вершины + расстояние от первой до второй 
                        if(scaleStartVertex.GetSecond() + currentEdge.GetDataEdge() < scaleEndVertex.GetSecond()){
                            
                            scaleEndVertex.GetSecond() = scaleStartVertex.GetSecond() + currentEdge.GetDataEdge();

                            //и записываем в словарь предков, то что предком для второй вершины является первая вершина

                            if(dictionaryAncestor.Contains(idEndVertex)){

                                dictionaryAncestor.Get(idEndVertex) = MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idStartVertex, currentEdge.GetID());
                            }
                            else{
                                dictionaryAncestor.Add(idEndVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idStartVertex, currentEdge.GetID()));
                            }
                        }

                        //если нашли лучший путь для первой вершины,
                        //то заменяем ее вес на вес второй вершины + расстояние от второй до первой
                        if(scaleEndVertex.GetSecond() + currentEdge.GetDataEdge() < scaleStartVertex.GetSecond()){
                            
                            scaleStartVertex.GetSecond() = scaleEndVertex.GetSecond() + currentEdge.GetDataEdge();

                            //и записываем в словарь предков, то что предком для первой вершины является вторая вершина

                            if(dictionaryAncestor.Contains(idStartVertex)){

                                dictionaryAncestor.Get(idStartVertex) = MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idEndVertex, currentEdge.GetID());
                            }
                            else{
                                dictionaryAncestor.Add(idStartVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idEndVertex, currentEdge.GetID()));
                            }
                        }

                        
                    }

                    //если расстояние до второй вершины бесконечность, а до первой нет  
                    //помним при этом что ребро не ориентированно 
                    if(scaleStartVertex.GetFirst() == 1 && scaleEndVertex.GetFirst() == 0){

                        scaleEndVertex.GetSecond() = scaleStartVertex.GetSecond() + currentEdge.GetDataEdge();

                        //и записываем в словарь предков, то что предком для второй вершины является первая вершина
                        dictionaryAncestor.Add(idEndVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idStartVertex, currentEdge.GetID()));

                        //записываем что расстояние от исходной вершины до текущей не равно бесконечности,
                        // то есть что путь существует
                        scaleEndVertex.GetFirst() = 1;
                    }



                    //если расстояние до первой вершины бесконечность, а до второй расстояние известно  
                    //помним при этом что ребро не ориентированно 
                    if(scaleEndVertex.GetFirst() == 1 && scaleStartVertex.GetFirst() == 0){

                        scaleStartVertex.GetSecond() = scaleEndVertex.GetSecond() + currentEdge.GetDataEdge();

                        //и записываем в словарь предков, то что предком для первой вершины является вторая вершина
                        dictionaryAncestor.Add(idStartVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idEndVertex, currentEdge.GetID()));

                        //записываем что расстояние от исходной вершины до текущей не равно бесконечности,
                        // то есть что путь существует
                        scaleStartVertex.GetFirst() = 1;
                    }

                }
                //если ребро ориентированное, помним, что начало ребра StartVertex а конец ребра это EndVertex
                else{

                    //если расстояние до второй вершины бесконечность, а до первой нет  
                    if(scaleStartVertex.GetFirst() == 1 && scaleEndVertex.GetFirst() == 0){

                        scaleEndVertex.GetSecond() = scaleStartVertex.GetSecond() + currentEdge.GetDataEdge();

                        //и записываем в словарь предков, то что предком для второй вершины является первая вершина
                        dictionaryAncestor.Add(idEndVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idStartVertex, currentEdge.GetID()));

                        //записываем что расстояние от исходной вершины до текущей не равно бесконечности,
                        // то есть что путь существует
                        scaleEndVertex.GetFirst() = 1;
                    }

                    //если расстояние до первой и второй вершин не бесконечность
                    if(scaleStartVertex.GetFirst() == 1 && scaleEndVertex.GetFirst() == 1){

                        //если нашли лучший путь для второй вершины,
                        //то заменяем ее вес на вес первой вершины + расстояние от первой до второй 
                        if(scaleStartVertex.GetSecond() + currentEdge.GetDataEdge() < scaleEndVertex.GetSecond()){
                            
                            scaleEndVertex.GetSecond() = scaleStartVertex.GetSecond() + currentEdge.GetDataEdge();

                            //и записываем в словарь предков, то что предком для второй вершины является первая вершина

                            if(dictionaryAncestor.Contains(idEndVertex)){

                                dictionaryAncestor.Get(idEndVertex) = MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idStartVertex, currentEdge.GetID());
                            }
                            else{
                                dictionaryAncestor.Add(idEndVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge>(idStartVertex, currentEdge.GetID()));
                            }
                        }
                        
                    }
                }



            }
        }

        bool existCycleNegativeLength = 0;

        //еще раз пробегаемся по всем ребрам и смотрим, можно ли уменьшить вес текущего пути
            typename Dictionary<ID, SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > >::ConstIterator cIt = dictionaryEdge_.ConstBegin();
            typename Dictionary<ID, SharedPtr< Edge<TypeDataVertex, TypeDataEdge> > >::ConstIterator cItEnd = dictionaryEdge_.ConstEnd();

        for(/*cIt*/; cIt != cItEnd; ++cIt){

                Edge<TypeDataVertex, TypeDataEdge> const & currentEdge = (*cIt).GetSecond().Get();

                Index idStartVertex = currentEdge.GetStartVertexID();
                Index idEndVertex = currentEdge.GetEndVertexID();

                MyNamespace::Pair<bool, TypeDataEdge>& scaleStartVertex = dictionaryScales.Get(idStartVertex);
                MyNamespace::Pair<bool, TypeDataEdge>& scaleEndVertex = dictionaryScales.Get(idEndVertex);

                if(currentEdge.Oriented() == 0){

                    //если пути до обеих вершин не равны бесконечности
                    if(scaleStartVertex.GetFirst() == 1 && scaleEndVertex.GetFirst() == 1){

                        //если нашли лучший путь для второй вершины,
                        //то заменяем ее вес на вес первой вершины + расстояние от первой до второй 
                        if(scaleStartVertex.GetSecond() + currentEdge.GetDataEdge() < scaleEndVertex.GetSecond()){
                            existCycleNegativeLength = 1;
                        }

                        //если нашли лучший путь для первой вершины,
                        //то заменяем ее вес на вес второй вершины + расстояние от второй до первой
                        if(scaleEndVertex.GetSecond() + currentEdge.GetDataEdge() < scaleStartVertex.GetSecond()){
                            existCycleNegativeLength = 1;
                        }

                        
                    }

                    //если расстояние до второй вершины бесконечность, а до первой нет  
                    //помним при этом что ребро не ориентированно 
                    if(scaleStartVertex.GetFirst() == 1 && scaleEndVertex.GetFirst() == 0){
                        existCycleNegativeLength = 1;
                    }



                    //если расстояние до первой вершины бесконечность, а до второй расстояние известно  
                    //помним при этом что ребро не ориентированно 
                    if(scaleEndVertex.GetFirst() == 1 && scaleStartVertex.GetFirst() == 0){
                        existCycleNegativeLength = 1;
                    }

                }
                //если ребро ориентированное, помним, что начало ребра StartVertex а конец ребра это EndVertex
                else{

                    //если расстояние до второй вершины бесконечность, а до первой нет  
                    if(scaleStartVertex.GetFirst() == 1 && scaleEndVertex.GetFirst() == 0){
                        existCycleNegativeLength = 1;
                    }

                    //если расстояние до первой и второй вершин не бесконечность
                    if(scaleStartVertex.GetFirst() == 1 && scaleEndVertex.GetFirst() == 1){

                        //если нашли лучший путь для второй вершины,
                        //то заменяем ее вес на вес первой вершины + расстояние от первой до второй 
                        if(scaleStartVertex.GetSecond() + currentEdge.GetDataEdge() < scaleEndVertex.GetSecond()){
                            existCycleNegativeLength = 1;
                        }
                    }
                }
        }

        //по теореме если существует путь длины равной количеству вершин,
        //то этот путь проходит хотя бы через какую то вершину дважды,
        //что не имеет смысла если нет цикла отрицательной суммарной длины
        if(existCycleNegativeLength == 1){
            throw "Exist Cycle Negative Length";
        }

        return MyNamespace::Pair<Dictionary<IndexCurrentVertex, MyNamespace::Pair<IndexPreviousVertex, IndexConnectingEdge> >, Dictionary<Index, MyNamespace::Pair<bool, TypeDataEdge> > > (dictionaryAncestor, dictionaryScales);
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