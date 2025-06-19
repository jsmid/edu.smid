#include <cstdlib>

using namespace std;
#include "simlib/queue.h"

/// @brief Default constructor for the Queue class.
/// Initializes the queue with a specified size (default is 10).
/// @param qs The maximum size of the queue.
/// The queue is initially empty, with both front and rear pointers set to NULL and item count set to 0.
Queue::Queue(int qs) : qsize(qs)
{
    front = rear = NULL;
    items = 0;
}

/// @brief Destructor for the Queue class.
/// Cleans up the queue by deleting all nodes.
Queue::~Queue()
{
    Node * tmp;
    while (front != NULL) // while the queue is not empty
    {
        tmp = front->next;
        delete front;
        front = tmp;
    }
}

/// @brief Checks if the queue is empty.
/// @return true if the queue is empty, false otherwise.
bool Queue::isempty() const
{
    return items == 0;
}

/// @brief Checks if the queue is full.
/// @return true if the queue is full, false otherwise.
bool Queue::isfull() const
{
    return items == qsize;
}

/// @brief Returns the current number of items in the queue.
/// @return The number of items currently in the queue.
int Queue::queuecount() const
{
    return items;
}

/// @brief Adds an item to the end of the queue.
/// @param i The item to be added to the queue. 
/// @return true if the item was successfully added, false if the queue is full.
bool Queue::enqueue(const Item &i)
{
    if (isfull())
        return false;
    Node * add = new Node();
    if (add == NULL)
        return false;

    add->item = i;
    add->next = NULL;
    if (front == NULL) // if the queue is empty
    {
        front = add;
    } else 
    { // set the pointer of the current last element to the new element being added
        rear->next = add;
    }
    rear = add; // set the new element as the last one
    items++;

    return true;
}

/// @brief Removes an item from the front of the queue.
/// @param i Reference to an Item object where the removed item will be stored.
/// @return true if an item was successfully removed, false if the queue is empty.
bool Queue::dequeue(Item &i)
{
    if (front == NULL)
        return false;
    i = front->item;
    items--;
    Node * tmp = front;
    front = front->next;
    delete tmp;
    if (items == 0)
        rear = NULL;

    return true;
}
