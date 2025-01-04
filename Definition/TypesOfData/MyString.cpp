#include <iostream>
#include "MyString.h"

    bool MyStringFunction::GetCharMassive(char* arr, int const sizeOfArr) // sizeOfArr is count of chars without '\0'
    {
        bool isReadAllString = 0;

        for(int i = 0; i < sizeOfArr; i++)
        {
            int tmp  = getchar();
            if(tmp == EOF || tmp == int('\n')){
                //arr[i] = '\0'; //correctly realisation
                //return;
                isReadAllString = 1;
                
                for(int j = i; j < sizeOfArr; j++) //but i need that
                {
                    arr[j] = ' ';
                }
                break;
            }
            arr[i] = (char)tmp;
        }
        arr[sizeOfArr] = '\0';

        return isReadAllString;
    }

    MyString::MyString()
    {
        str_ = nullptr;
        length_ = 0;
    }

    MyString::MyString(int const size)
    {
        try{
            this->str_ = new char[size + 1];
        }
        catch (...)
        {
            throw "failed memory allocation";
        }
        this->length_ = size;
        for(int i = 0; i < size; i++)
        {
            str_[i] = ' ';
        }
        str_[size] = '\0';
    }

    MyString::MyString(char ch)
    {
        length_ = 1;
         try{
            this->str_ = new char[length_ + 1];
        }
        catch (...)
        {
            throw "failed memory allocation";
        }
        str_[0] = ch;
        str_[1] = '\0';
    }

    MyString:: MyString(const char* str)
    {
        length_ = this->StrLen(str);
        
        try{
            this->str_ = new char[length_ + 1];
        }
        catch (...)
        {
            throw "failed memory allocation";
        }

        for (int i = 0; i < length_ + 1; i++)
        {
            this->str_[i] = str[i];
        }

        //this->str_[length_ ] = '\0';

    }

    MyString::~MyString()
    {
        delete[] this->str_;
        this->str_ = nullptr;
        this->length_ = 0;
    }

    char* MyString::Seize()
    {
        this-> length_ = 0;
        char *tmp = str_;
        str_ = nullptr;

        return tmp;

    }

    MyString MyString::IntToMyString(int const number)
    {
        MyString tmpMyString;
        int tmpNumber = number;
        bool moreThanNull = 1;

        if(number == 0)
        {
            return MyString("0");
        }

        if(tmpNumber < 0)
        {
            moreThanNull = 0;
            tmpNumber  *= -1;
        }

        while(tmpNumber != 0)
        {
            int remainder = tmpNumber % 10;
            char charToAppend = (char)( 48 + remainder);
            tmpMyString = tmpMyString + charToAppend;
            tmpNumber /= 10;
        }
        

        if(moreThanNull == false)
        {
            tmpMyString = tmpMyString + '-'; 
        }

        tmpMyString.Reverse();

        return tmpMyString;

    }

    void MyString::Reverse()
    {
        for(int i = 0; i < length_ / 2; i++)
        {
            char tmp = str_[i];
            str_[i] = str_[length_ -1 - i];
            str_[length_ -1 -i] = tmp;
        }
    }

    double MyString::MyStringToDouble() const
    {                                            // '0' = 48; '9' = 57
            MyString inputStr(*this);
            
            
            MyString MystrFirstPart;
            MyString MystrSecondPart;
            bool partNumber = 0;

            for(int i = 0; i <= inputStr.GetLength(); i++)
            {
                if((inputStr[i] != '\0' && inputStr[i] != '.') && ((int)inputStr[i] < 48 || (int)inputStr[i] > 57))
                    throw "invalid character";
                if(inputStr[i] == '\0')
                    break;
                if(inputStr[i] == '.'){
                
                    partNumber = 1;
                    continue;
                }
                if(partNumber == 0){
                
                    MystrFirstPart = MystrFirstPart + MyString(inputStr[i]);
                }
                else{
                    MystrSecondPart = MystrSecondPart + MyString(inputStr[i]);
                }

            }
            double firstPart = 0;
            for(int i = 0; i < MystrFirstPart.GetLength(); i++)
            {
                firstPart*=10;
                firstPart +=   ((int)(MystrFirstPart.operator[](i)) - 48);
            }

            double k = 1;
            double secondpart = 0;

            for(int i = 0; i < MystrSecondPart.GetLength(); i++)
            {
                k*=0.1;
                secondpart += ((int)(MystrSecondPart.operator[](i)) - 48) * k;
            }

            return firstPart + secondpart;

            

        
    }

    int MyString::StrLen(const char* symbols) const
    {
        int size = 0;
        if(symbols == nullptr)
            return 0;
        while (symbols[size] != '\0') {
            size++;
        }
        return size;
    }

    void MyString::StrCopy(char *dest, const char *src)
    {
        int i = 0;
        while (src[i] != '\0')
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    void MyString::StrCopy(char *dest, const char *src, int const size)
    {
        int i = 0;
        while(src[i] != '\0' && i < size)
        {
            dest[i] = src[i];
        }
        dest[i] = '\0';
    }

    MyString::MyString(const MyString& other)
    {
        length_ = other.StrLen(other.str_);
        //this->str_ = new char[length_ + 1];
        try{
            this->str_ = new char[length_ + 1];
        }
        catch (...)
        {
            throw "failed memory allocation";
        }

        for (int i = 0; i < length_; i++)
        {
            this->str_[i] = other.str_[i];
        }

        this->str_[length_] = '\0';
    }

    char MyString::Get(int index) const
    {
        if(index >= this->GetLength() || index < 0){
            throw "invalid index";
        }

        return this->str_[index];
    }

    MyString& MyString::operator=(const MyString& other)
    {
        if(this->str_ == other.str_)
            return *this;

        if (this->str_ != nullptr)
        {
            delete[] str_;
        }

        length_ = other.StrLen(other.str_);
        //this->str_ = new char[length_ + 1];
        try{
            this->str_ = new char[length_ + 1];
        }
        catch (...)
        {
            throw "failed memory allocation";
        }

        for (int i = 0; i < length_; i++)
        {
            this->str_[i] = other.str_[i];
        }
        this->str_[length_] = '\0';
        return *this;
    }

    MyString MyString::operator+(const MyString& other) const
    {
        MyString newStr;
        int thisLength = this->StrLen(this->str_);
        int otherLength = other.StrLen(other.str_);

        newStr.length_ = thisLength + otherLength;

        

        try{
            newStr.str_ = new char[thisLength + otherLength + 1];
        }
        catch (...)
        {
            throw "failed memory allocation";
        }

        for (int i = 0; i < thisLength; i++)
        {
            newStr.str_[i] = this->str_[i];
        }

        for (int j = 0; j < otherLength; j++)
        {
            newStr.str_[thisLength + j] = other.str_[j]; // it will not happen
        }

        newStr.str_[thisLength + otherLength] = '\0';

        return newStr;
    }

    std::ostream & operator<<(std::ostream &out, const MyString& myString)
    {
        return out << myString.str_;
    }

    std::istream & operator>>(std::istream &in, MyString& myString)
    {
        char buffer[1001];
        MyStringFunction::GetCharMassive(buffer, 1000);
        //in >> buffer;
        myString.length_ = myString.StrLen(buffer);

        delete[] myString.str_;

        

        try{
            myString.str_ = new char[myString.length_ + 1];
        }
        catch (...)
        {
            throw "failed memory allocation";
        }

        myString.StrCopy(myString.str_, buffer);
        return in;
    }

    int MyString::GetLength() const
    {
        return length_;
    }

    bool MyString::operator==(const MyString& other) const
    {
        if (this->length_ != other.length_)
        {
            return false;
        }

        for (int i = 0; i < this->length_; i++)
        {
            if (this->str_[i] != other.str_[i])
            {
                return false;
            }
        }
        return true;
    }

    bool MyString::operator!=(const MyString& other) const
    {
        return !(this->operator==(other));
    }

    char& MyString::operator [](int index)
    {
        return this->str_[index];
    }

    MyString::MyString(MyString&& other)
    {
        this->length_ = other.length_;
        this->str_ = other.str_;
        other.str_ = nullptr;
        other.length_ = 0;
    }


