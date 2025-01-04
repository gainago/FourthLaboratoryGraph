#ifndef COMPORATORS_H
#define COMPORATORS_H

#include "Person.h"

bool cmpInt(int const & first, int const & second); //First less than second

bool cmpPerson(Person const & perFirst, Person const & perSecond);

bool cmpPointerPerson(Person* const & perFirst, Person *const  & perSecond);

//-----------------------------------------------------------------------------

bool cmpIntCheck(int const & first, int const & second); // First less or equal than second

bool cmpPersonCheck(Person const & perFirst, Person const & perSecond);

bool cmpPointerPersonCheck(Person* const & perFirst, Person *const  & perSecond);

#endif //COMPORATORS_H