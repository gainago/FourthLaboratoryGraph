#include <time.h>
#include <cstdlib>
#include <unordered_map>
#include "DynamicArray.h"
#include "Dictionary.h"

void SetRandomIntMyDictionary(int const size, Dictionary<int, int>& dictionary)
{
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        int tmpValue = rand();
        if(dictionary.isContains(tmpValue)){
            i--;
            continue;
        }

        dictionary.Add(tmpValue, tmpValue);
    }
}

void SetRandomIntUnorderedMap(int const size, std::unordered_map<int, int>& map)
{
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        int tmpValue = rand();
        if(map.contains(tmpValue)){
            i--;
            continue;
        }

        map[tmpValue] = tmpValue;
    }
}
