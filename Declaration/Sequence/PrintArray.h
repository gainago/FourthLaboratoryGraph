#ifndef PRINT_ARRAY_H
#define PRINT_ARRAY_H

#include <iostream>
#include "DynamicArray.h"

template<typename Type>
void PrintArray(DynamicArray<Type> const & array)
{
    for(int i = 0; i < array.GetCapacity(); i++)
    {
        std::cout << array.Get(i) << " ";
    }

    std::cout << std::endl;
}

#endif //PRINT_ARRAY_H