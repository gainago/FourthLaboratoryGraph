#ifndef SHARED_PTR_H
#define SHARED_PTR_H

template <typename Type>
class WeakPtr;

template <typename Type> class SharedPtr{
private:
    
    class Counters{
    private:

        unsigned int CountShared_{0};
        unsigned int CountWeak_{0};
    public:

        unsigned int GetCountShared()  const noexcept
        {
            return CountShared_;
        }

        unsigned int GetCountWeak()  const noexcept
        {
            return CountWeak_;
        }

        void IncreaseCountShared() noexcept
        {
            CountShared_++;
        }

        void IncreaseCountWeak() noexcept
        {
            CountWeak_++;
        }

        void DecreaseCountShared() noexcept
        {
            CountShared_--;
        }

        void DecreaseCountWeak() noexcept
        {
            CountWeak_--;
        };
        Counters() : CountShared_(0), CountWeak_(0) {}


    };

    Counters *Counters_;
    Type* Data_;
private:

    friend class WeakPtr<Type>; 

    template <typename Type2, typename ... Arg> //должен быть одинаковый тип вместо Type2 жаль что это сделать не получилось
    friend SharedPtr<Type2> MakeShared(Arg ... arg);

    template <typename ... Args>
    SharedPtr(Args ... args)
    {
        Data_ = new Type(args...);
        Counters_ = new Counters;
        Counters_->IncreaseCountShared();
    }

private: //Destructors

    void DeleteData_() noexcept//избыточное выносение
    {
        delete Data_;
    }

    void DeleteCounters_() noexcept
    {
        delete Counters_;
    }

    void DeleteSharedPtr()
    {
        if(Counters_ == nullptr || Data_ == nullptr){                                    
            return;
        }
        Counters_->DecreaseCountShared();
        if(Counters_->GetCountShared() == 0)
        {
            DeleteData_();
            Data_ = nullptr;
        }
        if(Counters_->GetCountShared() == 0 && Counters_->GetCountWeak() == 0)
        {
            DeleteCounters_();
            Counters_ = nullptr;
        }

        Counters_ = nullptr;
        Data_ = nullptr;
    }

    SharedPtr(Type* Data, Counters* CountersPtr)
    {
        Data_ = Data;
        Counters_ = CountersPtr;
        Counters_->IncreaseCountShared();
    }

public:

    

    SharedPtr(SharedPtr<Type> const & Other)
    {
        this->Counters_ = Other.Counters_;
        this->Data_ = Other.Data_;
        if(Other.Counters_ != nullptr)
            this->Counters_->IncreaseCountShared();
    }

    SharedPtr(SharedPtr<Type> && Other)
    {
        this->Counters_ = Other.Counters_;
        this->Data_ = Other.Data_;
        Other.Counters_ = nullptr;
        Other.Data_ = nullptr;
    }

    SharedPtr()
    {
        Counters_ = nullptr;
        Data_ = nullptr;
    }

    ~SharedPtr()
    {
        DeleteSharedPtr();
    }
    
   

    void Reset(SharedPtr<Type> const & Other) noexcept
    {
        this->operator=(Other);
    }

    void Swap(SharedPtr<Type> & Other) noexcept
    {
        Counters* CurrentCounters = Other.Counters_;
        Type* CurrentData = Other.Data_;
        Other.Counters_ = this->Counters_;
        Other.Data_ = this->Data_;
        this->Counters_ = CurrentCounters;
        this->Data_ = CurrentData;
    }

    Type& Get()
    {
        if(Data_ == nullptr)
            throw "nullptr";
        return *Data_ ;
    }

    Type const & Get() const
    {
        if(Data_ == nullptr)
            throw "nullptr";
        return *Data_ ;
    }

    int Use_count() const noexcept
    {
        if(Counters_ == nullptr)
            return 0;
        return Counters_->GetCountShared();
    }

    SharedPtr<Type> operator=(SharedPtr<Type> const & Other) // НЕ КОПИПАСТИТЬ а выносить в отдельные функции
    {
        if(this->Data_ == Other.Data_)
            return *this;
        DeleteSharedPtr();
        this->Counters_ = Other.Counters_;
        this->Data_ = Other.Data_;
        if(this->Counters_ == nullptr || this->Data_ == nullptr)
            return *this;
        this->Counters_->IncreaseCountShared();
        return *this;
    }
    
    bool operator==(SharedPtr<Type> const & Pointer) const noexcept
    {
        
        return (this->Counters_ == Pointer.Counters_);

    }

    Type& operator*() 
    {

        return this->Get();
    }

    Type* operator->() 
    {
        if(Counters_ == nullptr)
            throw "nullptr";
        return Data_;
    }

};

template <typename Type, typename ... Arg>
SharedPtr<Type> MakeShared(Arg ... arg)
{
    
    return SharedPtr<Type>(arg...);
}
#endif
