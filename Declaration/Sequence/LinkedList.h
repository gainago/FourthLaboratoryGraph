#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T> class LinkedList
{
private:
    int size_;
    class Node
    {
    public:
        Node* pPriv_;
        Node* pNext_;
        T data_;

        Node(T const & data = T(), Node* pPriv = nullptr, Node* pNext = nullptr) : data_(data),
                                                                                     pPriv_(pPriv), pNext_(pNext)
        {}
    };

    Node* head_;
    Node* tail_;

public:

    class Iterator{ // итератор не заботится о памяти на которую указывает
        private:
        friend class LinkedList<T>;

        Node* currentNode_;
        public:

            Iterator(Node* head = nullptr) : currentNode_(head) {}

            Iterator(Iterator const & other) : currentNode_(other.currentNode_) {}

            Iterator& operator++()     //prefix increment
            {
                if(currentNode_ == nullptr){
                    throw "indev out of range";
                }

                currentNode_ = currentNode_->pNext_;
                return *this; 
            }

            Iterator& operator--()     //prefix increment
            {
                if(currentNode_ == nullptr){
                    throw "indev out of range";
                }

                currentNode_ = currentNode_->pPriv_;
                return *this; 
            }

            bool operator==(LinkedList<T>::Iterator const & other)
            {
                return this->currentNode_ == other.currentNode_;
            }

            bool operator!=(LinkedList<T>::Iterator const & other)
            {
                return !(this->currentNode_ == other.currentNode_);
            }

            void operator=(Iterator const & other)
            {
                currentNode_ = other.currentNode_;
            }

            T& operator*()
            {
                if(currentNode_ == nullptr){
                    throw "invalid index";
                }

                return currentNode_->data_;
            }
        private:
            void Erase(Node*& head, Node*& tail, int& size)
            {
                if(head == nullptr || tail == nullptr){
                    throw "invalid fill of structure";
                }
                if(currentNode_ == nullptr){
                    throw "invalid index";
                }
                Node* nodeToDelete = currentNode_;

                currentNode_ = currentNode_->pNext_;

                if(nodeToDelete == head){
                    if(tail == head){// if only one element
                        tail = nullptr;
                        head = nullptr;
                        delete nodeToDelete;
                        size--;
                        return;
                    }               //there are elements more than two
                    head = head->pNext_;
                    head->pPriv_ = nullptr;
                    delete nodeToDelete;
                    size--;
                    return;
                }

                if(nodeToDelete == tail){
                    tail->pPriv_->pNext_ = nullptr;
                    tail = tail->pPriv_;
                    delete nodeToDelete;
                    size--;
                    return;
                }
                if(nodeToDelete->pPriv_ != nullptr){
                    nodeToDelete->pPriv_->pNext_ = nodeToDelete->pNext_;
                }
                if(nodeToDelete->pNext_ != nullptr){
                    nodeToDelete->pNext_->pPriv_ = nodeToDelete->pPriv_;
                }
                delete nodeToDelete;
                size--;
            }

    };

    class ConstIterator{
        private:

        Node* currentNode_;
        public:

            ConstIterator(Node* head = nullptr) : currentNode_(head) {}

            ConstIterator(ConstIterator const & other) : currentNode_(other.currentNode_) {}

            ConstIterator& operator++ ()     //prefix increment
            {
                if(currentNode_ == nullptr){
                    throw "indev out of range";
                }

                currentNode_ = currentNode_->pNext_;
                return *this; 
            }

            bool operator==(LinkedList<T>::ConstIterator const & other) const
            {
                return this->currentNode_ == other.currentNode_;
            }

            bool operator!=(LinkedList<T>::ConstIterator const & other) const
            {
                return !(this->currentNode_ == other.currentNode_);
            }

            void operator=(ConstIterator const & other)
            {
                currentNode_ = other.currentNode_;
            }

            T operator*() const
            {
                if(currentNode_ == nullptr){
                    throw "invalid index";
                }

                return currentNode_->data_;
            }
            


    };

    Iterator Begin() { return Iterator(head_);}
    Iterator End() { return Iterator(nullptr);}
    Iterator Back() { return Iterator(tail_);}

    ConstIterator ConstBegin() const { return ConstIterator(head_);}
    ConstIterator ConstEnd() const { return ConstIterator(nullptr);}

    void Erase(Iterator& it)
    {
        it.Erase(head_, tail_, size_);
    }

    LinkedList()
    {
        this->size_ = 0;
        this->head_ = nullptr;
        this->tail_ = nullptr;
    }

    LinkedList(int const size) : LinkedList()
    {
        if( size < 0)
        {    
            throw "Invalid size";
        }
        for(int i = 0; i < size; i++)
        {
            Append(T());
        }
    }

    LinkedList(T* items, int count) : LinkedList()
    {
        if (count < 0 || items == nullptr)
        {
            throw "Invalid argument";
        }
        for (int i = 0; i < count; i++)
        {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T> &list) : LinkedList()
    {
        Node *current = list.head_;
        for (int i = 0; i < list.size_; i++)
        {
            Append(current->data_);
            current = current->pNext_;
        }
        this->size_ = list.size_;
    }

    ~LinkedList()
    {
        Node *current = this->head_;
        Node *next;
        while (current != nullptr)
        {
            next = current->pNext_;
            delete current;
            current = next;
        }
        this->size_ = 0;

        this->head_ = nullptr;
        this->tail_ = nullptr;
    }

    T const & GetFirst()
    {
        if (this->head_ == nullptr)
        {
            throw "Index out of range";
        }
        return this->head_->data_;
    }

    T const &GetLast()
    {
        /*Node *current = this->head_;
        if (this->head_ == nullptr)
        {
            throw "Index out of range";
        }
        for (int i = 0; i < this->size_ - 1; i++)
        {
            current = current->pNext_;
        }
        return current->data_;*/

        if(this->tail_ == nullptr){
            throw "Index out of range";
        }

        return tail_->data_;
    }

    T const & Get(int index) const
    {
        Node *current = this->head_;
        if (index < 0 || index >= this->size_)
        {
            throw "Invalid argument";
        }
        for (int i = 0; i < index; i++)
        {
            current = current->pNext_;
        }
        return current->data_;
    }

    T & Get(int index)
    {
        Node *current = this->head_;
        if (index < 0 || index >= this->size_)
        {
            throw "Invalid argument";
        }
        for (int i = 0; i < index; i++)
        {
            current = current->pNext_;
        }
        return current->data_;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex)
    {
        if (startIndex < 0 || endIndex < 0 || endIndex >= this->size_ || endIndex < startIndex)
        {
            throw "Invalid argument";
        }
        LinkedList<T> *resultList = new LinkedList<T>();
        for (int i = startIndex; i < endIndex; i++)
        {
            resultList->Append(this->Get(i));
        }
        return resultList;
    }

    int GetLength() const
    {
        return this->size_;
    }

    void Append(T const & item)
    {
        if (this->tail_ == nullptr)
        {
            this->head_ = new Node(item);
            this->tail_ = this->head_;
        }
        else
        {
            Node *current = new Node(item);
            current->pPriv_ = tail_;
            this->tail_->pNext_ = current;
            this->tail_ = current;
        }
        this->size_++;
    }

    void Set(int const index, T const & item)
    {
        this->operator[](index) = item;
    }

    void Prepend(T const & item)
    {
        if(head_ == nullptr){
            this->Append(item);
            return;
        }
        Node *newHead = new Node(item, nullptr, this->head_);
        this->head_ = newHead;
        this->size_++;
    }

    void InsertAt(T const & item, int index)
    {
        if (index < 0 || index >= this->size_)
        {
            throw "Invalid argument";
        }
        Node *newElement = new Node(item);
        Node *current = this->head_;
        for (int i = 0; i < index - 1; i++) // go to element at privious position
        {
            current = current->pNext_;
        }
        newElement->pNext_ = current->pNext_;
        newElement->pPriv_ = current;
        newElement->pNext_->pPriv_ = newElement;
        current->pNext_ = newElement;
        this->size_++;
    }

    void Remove(int const index)
    {
        if (index < 0 || index >= this->size_)
        {
            throw "Invalid argument";
        }

        Node *deleteElement;

        if(index == 0){
            deleteElement = head_;
            if(head_ == tail_){
                tail_ = tail_->pNext_;
            }
            head_ = head_->pNext_;
            delete deleteElement;
            size_--;
            return;
        }

        if(index == (this->size_ - 1))
        {

            deleteElement = tail_;
            tail_ = tail_->pPriv_;
            delete deleteElement;
            size_--;
            tail_->pNext_ = nullptr;
            return;
        }

        
        Node *privioudDelete = this->head_;

        for (int i = 0; i < index - 1; i++)
        {
            privioudDelete = privioudDelete->pNext_;
        }
        
        deleteElement = privioudDelete->pNext_;

        privioudDelete->pNext_ = deleteElement->pNext_;

        deleteElement->pNext_->pPriv_ = privioudDelete;

        delete deleteElement;

        size_--;
        return;

        
    }
    void PopFirst()
    {
        if(size_ == 0){
            return;
        }
        Remove(0);
    }

    LinkedList<T>* Concat(LinkedList<T> &list)
    {
        LinkedList<T> *resultList = new LinkedList<T>();
        for (int i = 0; i < this->size_; i++)
        {
            resultList->Append(this->Get(i));
        }
        for (int i = 0; i < list.size_; i++)
        {
            resultList->Append(list.Get(i));
        }
        return resultList;
    }

    T &operator[] (int index)
    {
        if (index >= this->size_ || index < 0)
        {
            throw "Invalid argument";
        }

        Node *result = this->head_;

        for (int i = 0; i < index; i++)
        {
            result = result->pNext_;
        }
        return result->data_;
    }
    /*void MoveBack(Iterator it) // от этого метода можно добиться ошибки связанной с size_(передать итератор не от этого объекта)
                                // исправить это можно совершая линейный обход но для текущей задачи это неоптимально, или в GetLength обходить список
    {
        Node* currentNode = it.currentNode_;
        if(currentNode == nullptr){
            return;
        }

        if(tail_ == currentNode){
            return;
        }

        if(currentNode->pPriv_ != nullptr){ // вырываем узел из старой цепочки
            currentNode->pPriv_->pNext_ = currentNode->pNext_;
        }
        if(currentNode->pNext_ != nullptr){
            currentNode->pNext_->pPriv_ = currentNode->pPriv_;
        }

        if(currentNode == head_){
            if(head_ == tail_){
                return;
            }
            
            head_ = head_->pNext_;
        }

        tail_->pNext_ = currentNode;
        currentNode->pPriv_ = tail_;
        currentNode->pNext_ = nullptr;

    }*/
};

#endif