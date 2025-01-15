#ifndef INPUT_OUTPUT_MYSTRING_H
#define INPUT_OUTPUT_MYSTRING_H

#include <iostream>
#include "Index.h"


 namespace IndexFunction
{
    //sizeOfArr is count of chars without '\0', return isReadAllString
    bool GetCharMassive(char* arr, int const sizeOfArr); 
}

void OutputIndex(Index const & index);

Index InputIndex();

#endif //INPUT_OUTPUT_MYSTRING_H