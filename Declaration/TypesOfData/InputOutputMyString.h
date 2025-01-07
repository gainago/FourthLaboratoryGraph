#ifndef INPUT_OUTPUT_MYSTRING_H
#define INPUT_OUTPUT_MYSTRING_H

#include <iostream>
#include "MyString.h"


 namespace MyStringFunction
{
    //sizeOfArr is count of chars without '\0', return isReadAllString
    bool GetCharMassive(char* arr, int const sizeOfArr); 
}

void OutputMyString(MyString const & string);

MyString InputMyString();

#endif //INPUT_OUTPUT_MYSTRING_H