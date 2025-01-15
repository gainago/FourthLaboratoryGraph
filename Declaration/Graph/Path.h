#ifndef PATH_H
#define PATH_H

#include "Edge.h"
#include "DynamicArray.h"

template <typename TypeDataVertex, typename TypeDataEdge> class Path{
private:

    DynamicArray<Edge < TypeDataVertex, TypeDataEdge> > arrayPath_;

public:

        Path() : arrayPath_() {}

        DynamicArray<Edge < TypeDataVertex, TypeDataEdge> > GetPath()
        {
            return arrayPath_;
        } 
};

#endif //PATH_H