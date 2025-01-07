#ifndef RETURN_VALUE_H
#define RETURN_VALUE_H

#include "Pair.h"

namespace MyNamespace
{

    template< typename Value>
    class ReturnValue{
    private:

        MyNamespace::Pair<bool, Value> returnValue_;
    public:

        ReturnValue(bool isOk, Value const & value) : returnValue_(isOk, value) {}

        bool IsCorrect() const
        {
            return returnValue_.GetFirst();
        }

        Value const & GetValue() const
        {
            return returnValue_.GetSecond();
        }

    };

}



#endif  //RETURN_VALUE_H