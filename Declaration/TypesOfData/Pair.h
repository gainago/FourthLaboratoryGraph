#ifndef PAIR_H
#define PAIR_H

namespace MyNamespace
{
    template <typename TypeFirst, typename TypeSecond> class Pair
    {
    private:
        TypeFirst first_;
        TypeSecond second_;
    public:
        // no way make pair without sending arguments
        Pair(TypeFirst const & first = TypeFirst(), TypeSecond const & second = TypeSecond()) : first_(first), second_(second) {} 

        Pair(Pair<TypeFirst, TypeSecond> const & otherPair) : first_(otherPair.GetFirst()), second_(otherPair.GetSecond()) {}

        void operator=(Pair<TypeFirst, TypeSecond> const & other)
        {
            SetFirst(other.GetFirst());
            SetSecond(other.GetSecond());
        }

        TypeFirst const & GetFirst() const
        {
            return first_;
        }

        TypeFirst & GetFirst()
        {
            return first_;
        }

        TypeSecond const & GetSecond() const
        {
            return second_;
        }

        TypeSecond & GetSecond() 
        {
            return second_;
        }

        void SetFirst(TypeFirst otherFirst)
        {
            first_ = otherFirst;
        }

        void SetSecond(TypeSecond otherSecond)
        {
            second_ = otherSecond;
        }

        bool operator==(Pair<TypeFirst, TypeSecond> const & other) ///!=
        {
            return (this->first_ == other.first_) && (this->second_ == other.second_);
        }
    
    };
}

#endif //PAIR_H