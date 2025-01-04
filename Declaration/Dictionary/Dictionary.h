#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Pair.h"

#include <iostream>

template< typename TypeKey, typename TypeValue> class Dictionary //вся работа с памятью делегирована на array
{
private:
    int (*GetHashCode_)(TypeKey const &);
    double fillFactor_;
    double increaseFactor_;
    DynamicArray<LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> > > array_; //занимает 8 байт на стеке
    int size_;

    bool isNeedRecapacityUp()//если есть вопрос то его с маленькой буквы
    {
        return size_ > fillFactor_*(array_.GetCapacity());
    }

    bool isNeedRecapacityLess() //grow and shrink
    {
        return size_ < fillFactor_*(array_.GetCapacity())/increaseFactor_;
    }

    MyNamespace::Pair<bool, int> isListContains(int numberList, TypeKey const & key) const //можно сразу дать лист и не дергать гет масссива
    {
       int position = 0;
                          
       for(auto it = array_.Get(numberList).ConstBegin(); it != array_.Get(numberList).ConstEnd(); ++it){
            if((*it).GetFirst() == key)
            {
                return MyNamespace::Pair<bool, int>(true, position);
            }
            position++;
       }
        return MyNamespace::Pair<bool, int>(false, 0);
    }

    void Rebuild(int newSize)
    {
        DynamicArray<LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> > > newArray(newSize);
        Iterator it = this->Begin();
        for(;it != this->End(); ++it)
        {
            newArray[GetHashCode_((*it).GetFirst()) % newArray.GetCapacity()].Append(
                MyNamespace::Pair<TypeKey const, TypeValue>((*it).GetFirst(), (*it).GetSecond()));
        }
        
        array_.swap(newArray);
    }

    

public:
    //   итератор не очищает память после выполнения операций втавки удаления становятся непригодными для использования
    class Iterator{ 
        friend class Dictionary<TypeKey, TypeValue>;
    private:

        DynamicArray<LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> > >& basedArray_;
        int arrayIndex_;
        typename LinkedList<MyNamespace::Pair< const TypeKey, TypeValue> >::Iterator listIterator_; // раз в массиве хранятся листы
                                                                                             // и не получилось найти хотя бы один элемент
                                                                                             //то значение true этого поля означает 
                                                                                             //что это уже конец словаря
        int isItEndIterator_; // это поле нужно чтобы при размере словаря итераторы работали нормально
        
        //сделать bool
    public:

        Iterator(DynamicArray<LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> > > & basedArray) 
            :   basedArray_(basedArray), arrayIndex_(0), listIterator_(nullptr) 
            {
                for(; arrayIndex_ < basedArray_.GetCapacity(); ++arrayIndex_){// size == 0

                    listIterator_ = basedArray_[arrayIndex_].Begin();

                    if(listIterator_ != basedArray_[arrayIndex_].End()){
                        isItEndIterator_ = 0;
                        return;
                    }
                }

                isItEndIterator_ = 1;
               
            }
        Iterator(Iterator const & other) : basedArray_(other.basedArray_), arrayIndex_(other.arrayIndex_)
                                        , listIterator_(other.listIterator_), isItEndIterator_(other.isItEndIterator_)
        {}

        Iterator& operator++()
        {
            if(isItEndIterator_){
                throw "invalid index";
            }

            if(listIterator_ != (basedArray_[arrayIndex_]).End())
            {
                ++listIterator_;

                if(listIterator_ != (basedArray_[arrayIndex_]).End()){
                    return *this;
                }
            }

            ++arrayIndex_;

            for(; arrayIndex_ < basedArray_.GetCapacity(); arrayIndex_++) //переписать while
            {
                listIterator_ = (basedArray_[arrayIndex_]).Begin();
                if(listIterator_ != (basedArray_[arrayIndex_]).End()){
                    return *this;
                }
            }

            isItEndIterator_ = 1;
            return *this;

        }

        MyNamespace::Pair< const TypeKey, TypeValue>& operator*()
        {
            if(isItEndIterator_){
                throw "invalid index";
            }

            return (*listIterator_);

        }

        int GetArrayIndex() const
        {
            return arrayIndex_;
        }

        bool operator==(Iterator const & other)
        {
            if(this->arrayIndex_ == other.arrayIndex_ && (&(this->basedArray_) == (&other.basedArray_))
                && this->isItEndIterator_ == other.isItEndIterator_ && this->listIterator_ == other.listIterator_){
                
                return true;
            } 

            return false;
        }

        bool operator!=(Iterator const & other)
        {
            return !(*this == other);
        }
        
    };

    Iterator Begin(){
        return Iterator(array_);
    }
    Iterator End() { 
        Iterator it(array_);
        it.listIterator_ = typename LinkedList<MyNamespace::Pair< const TypeKey, TypeValue> >::Iterator(nullptr);
        it.arrayIndex_ = array_.GetCapacity();
        it.isItEndIterator_ = 1;
        return it;
    }

    Dictionary(int (*GetHashCode)(TypeKey const &), double fillFactor = 0.7, double increaseFactor = 2, int capacity = 0) : GetHashCode_(GetHashCode)
        , fillFactor_(fillFactor), increaseFactor_(increaseFactor), array_(capacity), size_(0) 
        {
            if(increaseFactor <= 1 || fillFactor >= 1 || fillFactor_ <= 0  || capacity < 0 || GetHashCode == nullptr){
                throw "invalid parameters";
            }
        }


    ~Dictionary() {}

    void Add(TypeKey const key, TypeValue value)
    {
        if(array_.GetCapacity() == 0){
            array_.ReCapacity(1);
        }

        if(isContains(key)){
            throw "the element with same key have already existed";
        }

        array_[GetHashCode_(key) % array_.GetCapacity()].Append(MyNamespace::Pair<TypeKey const, TypeValue>(key, value));
        ++size_;

        if(isNeedRecapacityUp()){
            if((double)array_.GetCapacity() > (double)__INT_MAX__/increaseFactor_){
                throw " can not increase dictionary";
            }
            Rebuild(array_.GetCapacity() * increaseFactor_);
        }
    }

    void Remove(TypeKey const & key)
    {
        if(array_.GetCapacity() == 0){
            throw "invalid size";
        }

        if(!isContains(key)){
            throw "the dictionary do not contain this value";
        }

        array_[GetHashCode_(key) % array_.GetCapacity()]
            .Remove(isListContains(GetHashCode_(key) % array_.GetCapacity(), key).GetSecond());
        --size_;

        if(isNeedRecapacityLess()){
            
            Rebuild(array_.GetCapacity() / increaseFactor_);
        }

    }

    bool isContains(TypeKey const & key)const
    {
        if(array_.GetCapacity() == 0){
            return false;
        }
        return (isListContains(GetHashCode_(key) % array_.GetCapacity(), key)).GetFirst();
    }

    TypeValue& Get(TypeKey const key)
    {
        if(array_.GetCapacity() == 0){
            throw "invalid size";
        }

        if(!isContains(key)){
            throw "the dictionary do not contain this value";
        }

        return ((array_[GetHashCode_(key) % array_.GetCapacity()])
                    .Get(isListContains(GetHashCode_(key) % array_.GetCapacity(), key).GetSecond()))
                        .GetSecond();
            
    }

    int GetLength() const
    {
        return size_;
    }

    int GetCapacity() const
    {
        return array_.GetCapacity();
    }

    void Erase(Iterator& it)
    {
        if(it == End()){
            throw "invalid position of iterator";
        }
        it.basedArray_[it.arrayIndex_].Erase(it.listIterator_);
        size_--;
    }
};
// i j k плохие названия для переменных, потому что когда их много мы теряемся где мы находимся

#endif //DICTIONARY_H