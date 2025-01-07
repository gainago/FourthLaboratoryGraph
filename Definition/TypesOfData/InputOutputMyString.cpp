#include <iostream>
#include "MyString.h"
#include "InputOutputMyString.h"


bool MyStringFunction::GetCharMassive(char* arr, int const sizeOfArr) // sizeOfArr is count of chars without '\0'
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

void OutputMyString(MyString const & string)
{
      std::cout<< string.GetChar();
}

MyString InputMyString()
{
    char buffer[1001];
    MyStringFunction::GetCharMassive(buffer, 1000);
    return MyString(buffer);
}