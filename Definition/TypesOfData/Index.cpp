#include <iostream>
#include "Index.h"

    Index::Index()
    {
        this->length_ = 0;
        this->str_ = nullptr;
    }

    Index::Index(int const size)
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

    Index::Index(char ch)
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

    Index::Index(const char* str)
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

    Index::~Index()
    {
        delete[] this->str_;
        this->str_ = nullptr;
        this->length_ = 0;
    }

    char const * Index::GetChar() const
    {
        return str_;
    }

    void Index::Reverse()
    {
        for(int i = 0; i < length_ / 2; i++)
        {
            char tmp = str_[i];
            str_[i] = str_[length_ -1 - i];
            str_[length_ -1 -i] = tmp;
        }
    }

    int Index::StrLen(const char* symbols) const
    {
        int size = 0;
        if(symbols == nullptr)
            return 0;
        while (symbols[size] != '\0') {
            size++;
        }
        return size;
    }

    void Index::StrCopy(char *dest, const char *src)
    {
        int i = 0;
        while (src[i] != '\0')
        {
            /*if(dest[i] == '\0'){ // так нельзя потому что dest may be garbage
                throw "size of dest can not be more than size of source";
            }*/
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    void Index::StrCopy(char *dest, const char *src, int const size)
    {
        int i = 0;
        while(src[i] != '\0' && i < size)
        {
            dest[i] = src[i];
        }
        dest[i] = '\0';
    }

    Index::Index(const Index& other)
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

    char Index::Get(int index) const
    {
        if(index >= this->GetLength() || index < 0){
            throw "invalid index";
        }

        return this->str_[index];
    }

    Index& Index::operator=(const Index& other)
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

    int Index::GetLength() const
    {
        return length_;
    }

    bool Index::operator==(const Index& other) const
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

    bool Index::operator!=(const Index& other) const
    {
        return !(this->operator==(other));
    }

    char& Index::operator [](int index)
    {
        return this->str_[index];
    }

    Index::Index(Index&& other)
    {
        this->length_ = other.length_;
        this->str_ = other.str_;
        other.str_ = nullptr;
        other.length_ = 0;
    }


