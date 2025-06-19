#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "customer.h"

typedef Customer Item;

class Queue
{
    struct Node // class-scoped definition
    {
        Item item;
        struct Node * next = NULL;
    };

    enum {Q_SIZE = 10};

private:
    Node * front;       // pointer to the front of the queue
    Node * rear;        // pointer to the end of the queue
    int items;          // current number of items in the queue
    const int qsize;    // maximum number of items in the queue
    // preemptive definition, necessary to prevent public copying
    // implicit methods are overridden by these private ones, which cannot be used outside the class
    Queue(const Queue & q) : qsize(0) {};
    Queue & operator=(const Queue & q) { return *this; };

public:
    Queue(int qs = Q_SIZE);
    ~Queue();
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const Item &i); // add item to the end
    bool dequeue(Item &i);       // remove item from the front
};

#endif