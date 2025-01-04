#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
// length_ of string is count of symbols without a '\0'

namespace MyStringFunction
{
    // sizeOfArr is count of chars without '\0', return isReadAllString
    bool GetCharMassive(char* arr, int const sizeOfArr); 
}


class MyString
{
private:

    char* str_{nullptr};
    int length_{0};
    static void StrCopy(char *dest, const char* src); // do not control size of dest
    static void StrCopy(char *dest, const char *src, int const size);
public:
    MyString();

    MyString(char);

    MyString(int const size); 

    MyString(const char* str);

    ~MyString();

    char* Seize();

    int StrLen(const char* symbols) const;

    static MyString IntToMyString(int const);
    
    void Reverse();

    double MyStringToDouble() const;

    MyString(const MyString& other);

    MyString& operator=(const MyString& other);

    MyString operator+(const MyString& other) const;

    friend std::ostream &operator<<(std::ostream &out, const MyString& myString);

    friend std::istream &operator>>(std::istream &in, MyString& myString);

    int GetLength() const;

    char Get(int index) const;

    bool operator==(const MyString& other) const;

    bool operator!=(const MyString& other) const;

    char& operator [](int index);

    MyString(MyString&& other);
};
//std::ostream &operator<<(std::ostream &out, const MyString& myString);
//std::istream &operator>>(std::istream &in, MyString& myString);
#endif
