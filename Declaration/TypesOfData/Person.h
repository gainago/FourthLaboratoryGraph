#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include "MyString.h"



typedef MyString PersonID; 


class Person
{
private: 
    PersonID id;
    MyString firstName;
    MyString middleName;
    MyString lastName;
    int bornYear;
    static int const maxLength = 40;    //count of symbols without '\0'

public:
    Person();

    Person(PersonID id, MyString firstName, MyString middleName, MyString lastName, int bornYear);

    Person(Person const & other);

    MyString GetId() const;

    //void SetId();                 // Сеттеры не используются

    MyString GetFirstName() const; 

    //void SetFirstName();

    MyString GetMiddleName() const;

    //void SetMiddleName();

    MyString GetLastName() const;

    //void SetLastName();

    int GetBornYear() const;

    static int GetMaxLength();

    //void SetBornAge();

    friend std::istream &operator>>(std::istream &in, Person &person);

    friend std::ostream &operator<<(std::ostream &out, const Person &person);

    bool operator==(Person man);

    ~Person();
};

#endif