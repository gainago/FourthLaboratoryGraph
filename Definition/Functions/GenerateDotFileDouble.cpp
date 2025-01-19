#include <fstream>

#include "Graph.h"
#include "MyString.h"

void GenerateDOTFileDouble(Graph<double, double> const & graph, MyString graphName, Path<double, double> const & path = Path<double, double>())
{
    std::ofstream out;


    MyString fileName;

    fileName = MyString("../") + graphName + ".dot";
    out.open(fileName.Seize());
    if(!out.is_open()){
        throw "could not oped file";
    }

    //out << "digraph HelloWorld {\n";
    out << "digraph "; out << graphName.Seize(); out << " {\n";

    typename Graph<double, double>::ConstIteratorVertex cItVertex = graph.ConstBeginVertex();
    typename Graph<double, double>::ConstIteratorVertex cItVertexEnd = graph.ConstEndVertex();

    for(/*cItVertex*/; cItVertex != cItVertexEnd; ++cItVertex){

        MyString name((*cItVertex).GetID().GetChar());
        Index idCurrentVertex = (*cItVertex).GetID();

        bool doesNeedColor = 0;
        
        typename LinkedList<SharedPtr<Vertex<double, double> > >::ConstIterator cItVertexPath = path.listVertices_.ConstBegin();
        typename LinkedList<SharedPtr<Vertex<double, double> > >::ConstIterator cItVertexPathEnd = path.listVertices_.ConstEnd(); 

        for(/*cItVertexPath*/; cItVertexPath != cItVertexPathEnd; ++cItVertexPath){

            if((*cItVertexPath).Get().GetID() == idCurrentVertex){
                doesNeedColor = 1;
                break;
            }
        }

        name = MyString("\"") + name;
        name = name + MyString("\"");

        if(doesNeedColor == 1){
            name = name + MyString("[color=red]");
        }

        name = name + MyString(";");

        out << name.Seize() << "\n";


    }

    typename Graph<double, double>::ConstIteratorEdge cItEdge = graph.ConstBeginEdge();
    typename Graph<double, double>::ConstIteratorEdge cItEdgeEnd = graph.ConstEndEdge();

    for(/*cItEdge*/; cItEdge != cItEdgeEnd; ++cItEdge){

        

        Index idCurrentEdge = (*cItEdge).GetID();
        Index idStartVertex = (*cItEdge).GetStartVertexID();
        Index idEndVertex = (*cItEdge).GetEndVertexID();

        if((*cItEdge).Oriented() == 1){

            MyString stringToWrite;

            stringToWrite = MyString("\"") + MyString(idStartVertex.GetChar()) + MyString("\"") + MyString(" -> ");
            stringToWrite = stringToWrite + MyString("\"") + MyString(idEndVertex.GetChar()) + MyString("\"");


            bool doesNeedColor = 0;
            
            typename LinkedList<SharedPtr<Edge<double, double> > >::ConstIterator cItEdgePath = path.listEdges_.ConstBegin();
            typename LinkedList<SharedPtr<Edge<double, double> > >::ConstIterator cItEdgePathEnd = path.listEdges_.ConstEnd(); 

            for(/*cItVertexPath*/; cItEdgePath != cItEdgePathEnd; ++cItEdgePath){

                if((*cItEdgePath).Get().GetID() == idCurrentEdge){
                    doesNeedColor = 1;
                    break;
                }
            }

            if(doesNeedColor == 1){
                stringToWrite = stringToWrite + MyString("[color=red]");
            }

            stringToWrite = stringToWrite + MyString("[label=");

            out << stringToWrite.GetChar() << (*cItEdge).GetDataEdge() << "];\n";
        }
        //если он не ориентированный, то нужно представить его как два ориентированных
        if((*cItEdge).Oriented() == 0){

            MyString stringToWriteFirstOrientedEdge;// from Start to End

            stringToWriteFirstOrientedEdge = MyString("\"") + MyString(idStartVertex.GetChar()) + MyString("\"") + MyString(" -> ");
            stringToWriteFirstOrientedEdge = stringToWriteFirstOrientedEdge + MyString("\"") + MyString(idEndVertex.GetChar()) + MyString("\"");

            MyString stringToWriteSecondOrientedEdge;// from End to Start

            stringToWriteSecondOrientedEdge = MyString("\"") + MyString(idEndVertex.GetChar()) + MyString("\"") + MyString(" -> ");
            stringToWriteSecondOrientedEdge = stringToWriteSecondOrientedEdge + MyString("\"") + MyString(idStartVertex.GetChar()) + MyString("\"");

            bool doesNeedColorFirst = 0;
            bool doesNeedColorSecond = 0;

            typename LinkedList<SharedPtr<Vertex<double, double> > >::ConstIterator cItVertexPath = path.listVertices_.ConstBegin();
            typename LinkedList<SharedPtr<Vertex<double, double> > >::ConstIterator cItVertexPathNext = path.listVertices_.ConstBegin();
            typename LinkedList<SharedPtr<Vertex<double, double> > >::ConstIterator cItVErtexPathEnd = path.listVertices_.ConstEnd(); 

            if(cItVertexPathNext != cItVErtexPathEnd){
                ++cItVertexPathNext;
            }

            while(cItVertexPathNext != cItVErtexPathEnd){

                if((*cItVertexPath).Get().GetID() == idStartVertex && (*cItVertexPathNext).Get().GetID() == idEndVertex ){

                    doesNeedColorFirst = 1;
                }

                if((*cItVertexPath).Get().GetID() == idEndVertex && (*cItVertexPathNext).Get().GetID() == idStartVertex ){
                    
                    doesNeedColorSecond = 1;
                }

                ++cItVertexPathNext;
                ++cItVertexPath;
            }

            if(doesNeedColorFirst == 1){

                stringToWriteFirstOrientedEdge = stringToWriteFirstOrientedEdge + MyString("[color=red]");
            }

            if(doesNeedColorSecond == 1){

                stringToWriteSecondOrientedEdge = stringToWriteSecondOrientedEdge + MyString("[color=red]");
            }

            stringToWriteFirstOrientedEdge = stringToWriteFirstOrientedEdge + MyString("[label=");

            out << stringToWriteFirstOrientedEdge.GetChar() << (*cItEdge).GetDataEdge() << "];\n";


            stringToWriteSecondOrientedEdge = stringToWriteSecondOrientedEdge + MyString("[label=");

            out << stringToWriteSecondOrientedEdge.GetChar() << (*cItEdge).GetDataEdge() << "];\n";


        }

    }

    out << "}";
}