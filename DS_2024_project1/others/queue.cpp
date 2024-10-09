template <class T>
class Queue
{
    // A finite ordered list with zero or more elements.
public:
    Queue(int queueCapacity = 10);                   // Create an empty queue whose initial capacity is queueCapacity.
    bool IsEmpty() const;                            // If number of elements in the queue is 0, return true else return false.
    T& Front() const;                                // Return the element at the front of the queue.
    T& Rear() const;                                 // Return the element at the rear of the queue.
    void Push(const T& item);                        // Insert item at the rear of the queue.
    void Pop();                                      // Delete the front element of the queue.

private:
    T* queue; // array for queue elements
    int front, rear, capacity; // one counterclockwise from front, array position of rear element, capacity of queue array
};

template <class T>
Queue<T>::Queue(int queueCapacity) : capacity(queueCapacity)
{
    if (capacity < 1) throw "Queue capacity must be > 0";
    queue = new T[capacity];
    front = rear = 0;
}

template <class T>
inline bool Queue<T>::IsEmpty() const
{
    return front == rear;
}

template <class T>
inline T& Queue<T>::Front() const
{
    if (IsEmpty()) throw "Queue is empty. No front element";
    return queue[(front + 1) % capacity];
}

template <class T>
inline T& Queue<T>::Rear() const
{
    if (IsEmpty()) throw "Queue is empty. No rear element";
    return queue[rear];
}

template <class T>
void Queue<T>::Push(const T& x)
{
    // Add x at rear of queue.
    if ((rear + 1) % capacity == front) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2) {
            // No wrap around
            copy(queue + start, queue + start + capacity - 1, newQueue);
        }
        else {
            // Queue wraps around
            copy(queue + start, queue + capacity, newQueue);
            copy(queue, queue + rear + 1, newQueue + capacity - start);
        }

        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete[] queue;
        queue = newQueue;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = x;
}

template <class T>
void Queue<T>::Pop()
{
    if (IsEmpty()) throw "Queue is empty. Cannot delete";
    front = (front + 1) % capacity;
    queue[front].~T();
}
