#include <iostream>
#include <SharedPtr.h>

int main(int argc, char** argv)
{
   SharedPtr<int> ptr1 = MakeShared<int>(52);
   SharedPtr<int> ptr2 = ptr1;

   ptr1.~SharedPtr();
   ptr1.~SharedPtr();
   ptr1.~SharedPtr();
}