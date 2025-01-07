#ifndef WEAK_PTR_H
#define WEAK_PTR_H

#include "SharedPtr.h"

template<typename Type>
class WeakPtr{
private:
    typename SharedPtr<Type>::Counters* Counters_;
    Type* Data_;

    void DeleteWeakPtr()
    {
        if(Data_ == nullptr && Counters_ == nullptr)
            return;
        Counters_->DecreaseCountWeak();
        if(Counters_->GetCountShared() == 0 && Counters_->GetCountWeak() == 0)
        {
            delete Counters_;
            Counters_ = nullptr;
        }
    }

public:

    WeakPtr() = delete;
    WeakPtr(SharedPtr<Type> & Pointer)
    {
        Data_ = Pointer.Data_;
        Counters_ = Pointer.Counters_;
        Pointer.Counters_->IncreaseCountWeak();
    }

    WeakPtr(WeakPtr<Type> && Other)
    {
        this->Data_ = Other.Data_;
        this->Counters_ = Other.Counters_;
        Other.Counters_ = nullptr;
        Other.Counters_ = nullptr;
    }

    ~WeakPtr()
    {
        DeleteWeakPtr(); 
    }

    void Reset() //можно добится утечки памяти 
                    // если дважды вызвать что произойдет ошибка памяти
    {
        if(Counters_ == nullptr)
            return;
        Counters_->DecreaseCountWeak();
        Counters_ = nullptr;
        Data_ = nullptr;
    }

    void Swap(WeakPtr<Type> & Other) noexcept
    {
        typename SharedPtr<Type>::Counters //продолжение строки без отступа усложняет чтение
            *CurrentCounters = this->Counters_;
        Type* CurrentData = this->Data_;

        this->Data_ = Other.Data_;
        this->Counters_ = Other.Counters_;

        Other.Data_ = CurrentData;
        Other.Counters_ = CurrentCounters;

    }

    int CountWeak() const noexcept
    {

        return Counters_->GetCountWeak();
    }

    bool IsAlive() const // if expired? true: false
    {
        if(Counters_->GetCountShared() == 0) // return Gounters->GetCountShared() == 0
            return false;
        return true;
    }

    SharedPtr<Type> lock()
    {
        if(!this->IsAlive())
            throw "object has beed deleted";
        
        return SharedPtr<Type>(Data_, Counters_);
    }

    SharedPtr<Type> const lock() const
    {
        if(!this->IsAlive())
            throw "object has beed deleted";
        
        return SharedPtr<Type>(Data_, Counters_);
    }

};

#endif