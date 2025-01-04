#ifndef PRINT_LIST_H
#define PRINT_LIST_H

#include <iostream>
#include "LinkedList.h"

template<typename Type>
void PrintList(LinkedList<Type> const & list) 
{
    for(int i = 0; i < list.GetLength(); i++)
    {
        std::cout << list.Get(i) << " ";
    }

    std::cout << std::endl;
}

#endif //PRINT_LIST_H