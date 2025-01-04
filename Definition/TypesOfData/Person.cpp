#include <iostream>
#include <limits>
#include "Person.h"
#include "MyString.h"



    Person::Person() : id(maxLength), firstName(maxLength), middleName(maxLength), lastName(maxLength), bornYear(2005) {}

    Person::Person(PersonID id, MyString firstName, MyString middleName, MyString lastName, int birthAge)
    {
        if(id.GetLength() > maxLength || firstName.GetLength() > maxLength || middleName.GetLength() > maxLength)
            throw "length string more than MLENGTH";
        this->id = id;
        this->firstName = firstName;
        this->middleName = middleName;
        this->lastName = lastName;
        bornYear = birthAge;
    }

    Person::Person(const Person &person)
    {
        this->id = person.id;
        this->firstName = person.firstName;
        this->middleName = person.middleName;
        this->lastName = person.lastName;
    }

    MyString Person::GetId() const
    {
        return this->id;
    }

    MyString Person::GetFirstName() const 
    {
        return this->firstName;
    }

    MyString Person::GetMiddleName() const 
    {
        return this->middleName;
    }

    MyString Person::GetLastName() const
    {
        return this->lastName;
    }

    int Person::GetBornYear() const
    {
        return this->bornYear;
    }

    int Person::GetMaxLength()
    {
        return maxLength;
    }

     std::istream & operator>>(std::istream &in, Person &person)
    {
        char buffer[Person::GetMaxLength() + 1];
        bool isReadAllString = 0;

        std::cout << "Enter first name( max " << Person::GetMaxLength() << " symbols) :" << std::endl;

        isReadAllString = MyStringFunction::GetCharMassive(buffer, Person::GetMaxLength());
        if(!isReadAllString)
            in.ignore(std::numeric_limits<int>::max(), '\n');
        isReadAllString = 0;

        MyString tmpStringFirstName(buffer);
        person.firstName = tmpStringFirstName;


        std::cout << "Enter middle name( max " << Person::GetMaxLength() << " symbols) :" << std::endl;
        //in >> person.middleName;
        isReadAllString = MyStringFunction::GetCharMassive(buffer, Person::GetMaxLength());
        if(!isReadAllString)                                            // if read not all string than cut input
            in.ignore(std::numeric_limits<int>::max(), '\n');
        isReadAllString = 0;
        MyString tmpStringMiddleName(buffer);
        person.middleName = tmpStringMiddleName;

        std::cout << "Enter last name( max " << Person::GetMaxLength() << " symbols) :" << std::endl;
        //in >> person.lastName;
        isReadAllString = MyStringFunction::GetCharMassive(buffer, Person::GetMaxLength());
        if(!isReadAllString)
            in.ignore(std::numeric_limits<int>::max(), '\n');
        isReadAllString = 0;
        MyString tmpStringLastName(buffer);
        person.lastName = tmpStringLastName;

        std::cout << "Enter id( max " << Person::GetMaxLength() << " symbols) :" << std::endl;

        isReadAllString = MyStringFunction::GetCharMassive(buffer, Person::GetMaxLength());
        if(!isReadAllString)
            in.ignore(std::numeric_limits<int>::max(), '\n');
        isReadAllString = 0;

        MyString tmpStringId(buffer);
        person.id = tmpStringId;
        //in >> person.id;

        std::cout << "Enter born year" << std::endl;
        int tmpBornYear = 0;
        in >> tmpBornYear;                          //if user will enter trash it would his problem
        person.bornYear = tmpBornYear;
        return in;
    }

    std::ostream & operator<<(std::ostream &out, const Person &person)
    {
        //return out << "Person id:" << person.id << "firstName: " << person.firstName << "middleName: " << person.middleName << "lastName: " << person.lastName << "bornYear: " << person.bornYear << std::endl;
        return out <<std::endl << person.id <<std::endl << person.firstName <<std::endl << person.middleName << std::endl << person.lastName << std::endl << person.bornYear << std::endl;
    }

    bool Person::operator==(Person man)
    {
        return ((id == man.GetId()) && (middleName == man.GetMiddleName()) && (firstName == man.GetFirstName()) &&
            (lastName == man.GetLastName()));
    }

    Person::~Person()
    {
        id.~MyString();
        firstName.~MyString();
        middleName.~MyString();
        lastName.~MyString();
    }

