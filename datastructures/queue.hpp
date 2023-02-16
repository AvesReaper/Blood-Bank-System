#include <iostream>
#include "linkedlist.hpp"

using namespace std;

template <typename T>
class Queue
{
public:
    LinkedList<T> content;
    void enqueue(T item)
    {
        content.appendNode(item);
    }

    T dequeue()
    {
        T data = content.tail_->data;
        content.deleteNodeAt(content.length_ - 1);
        return data;
    }
};
