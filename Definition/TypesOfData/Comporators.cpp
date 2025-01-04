#include "Person.h"
#include "MyString.h"

bool cmpInt(int const & first, int const & second)
{
    return first < second;
}

bool cmpIntCheck(int const & first, int const & second)
{
    return !cmpInt(second, first);
}


bool cmpPerson(Person const & perFirst, Person const & perSecond)
{
    MyString strNameFirst = perFirst.GetFirstName(), strNameSecond = perSecond.GetFirstName();
    if(strNameFirst.GetLength() == 0)
        return true;
    if(strNameSecond.GetLength() == 0)
        return false;

    bool returnBool = 0;
    
    char const *tmpNameFirst = strNameFirst.Seize();
    char const *tmpNameSecond = strNameSecond.Seize();
    if((int)(tmpNameFirst[0]) < (int)(tmpNameSecond[0]))
        returnBool = true;
    
    delete tmpNameFirst;
    delete tmpNameSecond;

    return returnBool;
}

bool cmpPersonCheck(Person const & perFirst, Person const & perSecond)
{
    return !(cmpPerson(perSecond, perFirst));        
}

bool cmpPointerPerson(Person * const &  pperFirst, Person * const &  pperSecond)
{
    Person perFirst = *pperFirst;
    Person perSecond = *pperSecond;
        MyString strNameFirst = perFirst.GetFirstName(), strNameSecond = perSecond.GetFirstName();
    if(strNameFirst.GetLength() == 0)
        return true;
    if(strNameSecond.GetLength() == 0)
        return false;

    bool returnBool = 0;

   char const *tmpNameFirst = strNameFirst.Seize();
    char const *tmpNameSecond = strNameSecond.Seize();
    if((int)(tmpNameFirst[0]) < (int)(tmpNameSecond[0]))
        returnBool = true;

    delete tmpNameFirst;
    delete tmpNameSecond;

    return returnBool;

}

bool cmpPointerPersonCheck(Person * const &  pperFirst, Person * const &  pperSecond)
{

    return !(cmpPointerPerson(pperSecond, pperFirst)); // первый меньше либо равен второму, если второй не больше чем первый

}