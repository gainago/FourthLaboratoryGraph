#include "Abs.h"
#include "Index.h"

int GetHashCodeInt(int const & value)
{
    return MyNamespace::Abs(value);
}


int GetHashCodeIndex(Index const & index)
{
    int hash = 0;

    for(int i = 0; i < index.GetLength(); i++)
    {
        hash+=(int)index.Get(i);
        hash = hash % (int)(1e9 + 7);
    }

    return hash;
}