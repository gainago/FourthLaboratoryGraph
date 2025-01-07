#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Pair.h"


template< typename TypeKey, typename TypeValue> class Dictionary 
{
private:
    int (*GetHashCode_)(TypeKey const &);
    double fillFactor_;
    double increaseFactor_;
    DynamicArray<LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> > > array_; //занимает 8 байт на стеке
    int size_;

    bool NeedRecapacityUp()
    {
        return size_ > fillFactor_*(array_.GetCapacity());
    }

    bool NeedRecapacityLess() 
    {
        return size_ < fillFactor_*(array_.GetCapacity())/increaseFactor_;
    }
    
    //не выйдет возвращать итератор для Remove потому что функция констентная
    MyNamespace::Pair<bool, int> GetPositionInList(int numberList, TypeKey const & key) const
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

    class Iterator{ 
        friend class Dictionary<TypeKey, TypeValue>;
    private:

        DynamicArray<LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> > >& basedArray_;
        int arrayIndex_;

        // раз в массиве хранятся листы
        // и не получилось найти хотя бы один элемент
        //то значение true этого поля означает 
        //что это уже конец словаря
        typename LinkedList<MyNamespace::Pair< const TypeKey, TypeValue> >::Iterator listIterator_; 


        // это поле нужно чтобы при размере словаря итераторы работали нормально, принимет два значения
        bool isItEndIterator_;  
        
        
        
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
            //это и есть условие того что это не конец

            for(; arrayIndex_ < basedArray_.GetCapacity(); arrayIndex_++) // можно переписать while, но мне кажется что так лучше
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


        class ConstIterator{ 
        friend class Dictionary<TypeKey, TypeValue>;
    private:

        DynamicArray<LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> > > const & basedArray_;
        int arrayIndex_;

        // раз в массиве хранятся листы
        // и не получилось найти хотя бы один элемент
        //то значение true этого поля означает 
        //что это уже конец словаря
        typename LinkedList<MyNamespace::Pair< const TypeKey, TypeValue> >::ConstIterator constListIterator_; 


        // это поле нужно чтобы при размере словаря итераторы работали нормально, принимет два значения
        bool isItEndIterator_;  
        
        
        
    public:

        ConstIterator(DynamicArray<LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> > >  const & basedArray) 
            :   basedArray_(basedArray), arrayIndex_(0), constListIterator_(nullptr) 
            {
                for(; arrayIndex_ < basedArray_.GetCapacity(); ++arrayIndex_){// size == 0

                    constListIterator_ = (basedArray_.Get(arrayIndex_)).ConstBegin();

                    if(constListIterator_ != (basedArray_.Get(arrayIndex_)).ConstEnd()){
                        isItEndIterator_ = 0;
                        return;
                    }
                }

                isItEndIterator_ = 1;
               
            }
        ConstIterator(ConstIterator const & other) : basedArray_(other.basedArray_), arrayIndex_(other.arrayIndex_)
                                        , constListIterator_(other.constListIterator_), isItEndIterator_(other.isItEndIterator_)
        {}

        ConstIterator& operator++()
        {
            if(isItEndIterator_){
                throw "invalid index";
            }

            if(constListIterator_ != (basedArray_.Get(arrayIndex_)).ConstEnd())
            {
                ++constListIterator_;

                if(constListIterator_ != (basedArray_.Get(arrayIndex_)).ConstEnd()){
                    return *this;
                }
            }

            ++arrayIndex_;
            //это и есть условие того что это не конец

            for(; arrayIndex_ < basedArray_.GetCapacity(); arrayIndex_++) // можно переписать while, но мне кажется что так лучше
            {
                constListIterator_ = (basedArray_.Get(arrayIndex_)).ConstBegin();
                if(constListIterator_ != (basedArray_.Get(arrayIndex_)).ConstEnd()){
                    return *this;
                }
            }

            isItEndIterator_ = 1;
            return *this;

        }

        MyNamespace::Pair< const TypeKey, TypeValue> const & operator*() const
        {
            if(isItEndIterator_){
                throw "invalid index";
            }

            return (*constListIterator_);

        }

        int GetArrayIndex() const
        {
            return arrayIndex_;
        }

        bool operator==(ConstIterator const & other) const
        {
            if(this->arrayIndex_ == other.arrayIndex_ && (&(this->basedArray_) == (&other.basedArray_))
                && this->isItEndIterator_ == other.isItEndIterator_ && this->constListIterator_ == other.constListIterator_){
                
                return true;
            } 

            return false;
        }

        bool operator!=(ConstIterator const & other) const
        {
            return !(*this == other);
        }
        
    };

    ConstIterator ConstBegin() const{
        return ConstIterator(array_);
    }
    ConstIterator ConstEnd() const { 
        ConstIterator it(array_);
        it.constListIterator_ = typename LinkedList<MyNamespace::Pair< const TypeKey, TypeValue> >::ConstIterator(nullptr);
        it.arrayIndex_ = array_.GetCapacity();
        it.isItEndIterator_ = 1;
        return it;
    }
    

    Dictionary(int (*GetHashCode)(TypeKey const &), double fillFactor = 0.7, double increaseFactor = 2, int capacity = 0) : GetHashCode_(GetHashCode)
        , fillFactor_(fillFactor), increaseFactor_(increaseFactor), array_(capacity), size_(0) 
        {
            if(increaseFactor <= 1 || fillFactor > 1 || fillFactor_ <= 0  || capacity < 0 || GetHashCode == nullptr){
                throw "invalid parameters";
            }
        }

    void Add(TypeKey const & key, TypeValue const & value)
    {
        if(array_.GetCapacity() == 0){
            array_.ReCapacity(1);
        }

        if(Contains(key)){
            throw "the element with same key have already existed";
        }

        array_[GetHashCode_(key) % array_.GetCapacity()].Append(MyNamespace::Pair<TypeKey const, TypeValue>(key, value));
        ++size_;

        if(NeedRecapacityUp()){
            if((double)array_.GetCapacity() > (double)__INT_MAX__/increaseFactor_){
                throw " can not increase dictionary";
            }
            Rebuild(array_.GetCapacity() * increaseFactor_ + 1);
        }
        
    }

    void Remove(TypeKey const & key)
    {
        if(array_.GetCapacity() == 0){
            throw " Dictionary is empty";
        }

        typename LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> >::Iterator it = array_[GetHashCode_(key) % array_.GetCapacity()].Begin();
        typename LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> >::Iterator itEnd = array_[GetHashCode_(key) % array_.GetCapacity()].End();
        for(/*it*/; it != itEnd; ++it){
            if((*it).GetFirst() == key){
                array_[GetHashCode_(key) % array_.GetCapacity()].Erase(it);
                --size_;
                if(NeedRecapacityLess()){
            
                    Rebuild(array_.GetCapacity() / increaseFactor_);
                }   
                return;
            }
        }
        throw "There is no element with this value";
        
        //array_[GetHashCode_(key) % array_.GetCapacity()]
           // .Remove(isListContains(GetHashCode_(key) % array_.GetCapacity(), key).GetSecond());//второй и третий раз
        

        
    }

    bool Contains(TypeKey const & key )const 
    {
        if(array_.GetCapacity() == 0){
            return false;
        }
        return (GetPositionInList(GetHashCode_(key) % array_.GetCapacity(), key)).GetFirst();
    }

    TypeValue& Get(TypeKey const key)
    {
        typename LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> >::Iterator it = array_[GetHashCode_(key) % array_.GetCapacity()].Begin();
        typename LinkedList<MyNamespace::Pair<TypeKey const, TypeValue> >::Iterator itEnd = array_[GetHashCode_(key) % array_.GetCapacity()].End();
        
        for(/*it*/; it != itEnd; ++it){
            if((*it).GetFirst() == key){
                return (*it).GetSecond();
            }
        }

        throw "Dictionary is not contains element with this value";
        

        //return ((array_[GetHashCode_(key) % array_.GetCapacity()])
        //            .Get(isListContains(GetHashCode_(key) % array_.GetCapacity(), key).GetSecond()))
        //                .GetSecond();//разбить с сохранением промежуточных значений  
    }

    int GetLength() const
    {
        return size_;
    }

    int GetCapacity() const //функция не нужна, никакого смысла в ней нет
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


#endif //DICTIONARY_H