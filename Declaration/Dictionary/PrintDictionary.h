#ifndef PRINT_DICTIONARY_H
#define PRINT_DICTIONARY_H

#include "Dictionary.h"
#include <iostream>

template< typename TypeKey, typename TypeValue>
void PrintDictionary(Dictionary<TypeKey, TypeValue> & dictionary)
{
    for(auto it = dictionary.Begin(); it != dictionary.End(); ++it)
    {
        std::cout << it.GetArrayIndex()  <<". < " << (*it).GetFirst() << ", " <<  (*it).GetSecond() << ">" << "\n";
    }
    std::cout << std::endl;
}

#endif //PRINT_DICTIONARY_H
