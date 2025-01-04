#ifndef SET_RANDOM_INT_H
#define SET_RANDOM_INT_H

#include "DynamicArray.h"
#include "Dictionary.h"
#include <unordered_map>

void SetRandomIntMyDictionary(int const size, Dictionary<int, int>& dictionary);

void SetRandomIntUnorderedMap(int const size, std::unordered_map<int, int>& map);

#endif //SET_RANDOM_INT_H