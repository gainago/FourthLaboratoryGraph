#include <iostream>
#include "MyString.h"
#include "InputOutputIndex.h"


bool IndexFunction::GetCharMassive(char* arr, int const sizeOfArr) // sizeOfArr is count of chars without '\0'
    {
        bool isReadAllString = 0;

        int tmp  = getchar();
        while(tmp == (int)' ' && tmp != EOF && tmp != int('\n') ){
            tmp = getchar();
        }

        for(int i = 0; i < sizeOfArr; i++)
        {
            
            if(tmp == EOF || tmp == int('\n')){
                arr[i] = '\0'; //correctly realisation
                return 1;
                /*isReadAllString = 1;
                
                for(int j = i; j < sizeOfArr; j++) //but i need that
                {
                    arr[j] = ' ';
                }
                break;*/
            }
            arr[i] = (char)tmp;

            tmp = getchar();
        }
        arr[sizeOfArr] = '\0';

        return isReadAllString;
    }

void OutputIndex(Index const & index)
{
      std::cout<< index.GetChar();
}

Index InputMyString()
{
    char buffer[1001];
    MyStringFunction::GetCharMassive(buffer, 1000);
    return Index(buffer);
}