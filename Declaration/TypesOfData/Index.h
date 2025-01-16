#ifndef INDEX_H
#define INDEX_H

// length_ of string is count of symbols without a '\0'



class Index
{
private:

    char* str_{nullptr};
    int length_{0};
    static void StrCopy(char *dest, const char* src); // do not control size of dest
    static void StrCopy(char *dest, const char *src, int const size);
public:

    Index();

    Index(int const size);

    Index(char);

    Index(const char* str);

    Index(const Index& other);

    Index(Index&& other);

    ~Index();

    char const * GetChar() const;

    int StrLen(const char* symbols) const;
    
    void Reverse();

    Index& operator=(const Index& other);

    int GetLength() const;

    char Get(int index) const;

    bool operator==(const Index& other) const;

    bool operator!=(const Index& other) const;

    char& operator [](int index);
};

#endif // INDEX_H
