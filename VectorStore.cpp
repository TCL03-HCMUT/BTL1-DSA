#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

template <class T>
ArrayList<T>::ArrayList(int initCapacity) : capacity(initCapacity), count(0)
{
    front = Iterator(this, 0);
    back = Iterator(this, count);
    data = new T[capacity];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> &other) : capacity(other.capacity), count(other.count)
{
    this->data = new T[this->capacity];
    for (int i = 0; i < count; i++)
    {
        (this->data)[i] = (other.data)[i];
    }
    this->front = other.front;
    this->back = other.back;
}

template <class T>
ArrayList<T>::~ArrayList()
{
    delete[] data;
}

template <class T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &other)
{
    delete[] this->data;
    this->capacity = other.capacity;
    this->data = new T[this->capacity];
    memcpy(this->data, other.data, sizeof(T) * other.count);
    this->count = other.count;
    this->front = other.front;
    this->back = other.back;
    return *this;
}

// TODO: implement other methods of ArrayList

template <class T>
void ArrayList<T>::setCapacity(int newCapacity)
{
    T *newData = new T[newCapacity];
    memcpy(newData, data, sizeof(T) * count);
    capacity = newCapacity;
    delete[] data;
    data = newData;
}

template <class T>
void ArrayList<T>::ensureCapacity(int cap)
{
    if (cap > this->capacity)
    {
        int newCapacity = (capacity * 3) / 2;
        if (newCapacity < cap)
        {
            newCapacity = cap;
        }
        setCapacity(newCapacity);
    }
}

template <class T>
void ArrayList<T>::rangeCheck(int index)
{
    if (index < 0 || index >= count)
        throw out_of_range("Index is invalid!");
}

template <class T>
void ArrayList<T>::add(T e)
{
    // TODO: after implementing iterators
    ensureCapacity(count + 1);
    data[count++] = e;
    back = Iterator(this, count);
}

template <class T>
void ArrayList<T>::add(int index, T e)
{
    if (index < 0 || index > count)
        throw out_of_range("Index is invalid!");

    ensureCapacity(count + 1);

    int moveCount = count - index;
    if (moveCount != 0) // moveCount == 0: insert at end
        memmove(data + index + 1, data + index, sizeof(T) * moveCount);

    data[index] = e;
    count++;
    back = Iterator(this, count);
}

template <class T>
T ArrayList<T>::removeAt(int index)
{
    rangeCheck(index);
    T temp = data[index];
    int moveCount = count - index - 1;
    if (moveCount > 0)
        memmove(data + index, data + (index + 1), sizeof(T) * moveCount);

    count--;
    back = Iterator(this, count);
    return temp;
}

template <class T>
bool ArrayList<T>::empty() const
{
    return count == 0;
}

template <class T>
int ArrayList<T>::size() const
{
    return count;
}

template <class T>
void ArrayList<T>::clear()
{
    delete[] data;
    capacity = 10;
    count = 0;
    data = new T[capacity];
}

template <class T>
T &ArrayList<T>::get(int index)
{
    rangeCheck(index);
    return data[index];
}

template <class T>
void ArrayList<T>::set(int index, T e)
{
    rangeCheck(index);
    data[index] = e;
}

template <class T>
int ArrayList<T>::indexOf(T item) const
{
    for (int i = 0; i < count; i++)
    {
        if (data[i] == item)
            return i;
    }
    return -1;
}

template <class T>
bool ArrayList<T>::contains(T item) const
{
    for (int i = 0; i < count; i++)
    {
        if (data[i] == item)
            return true;
    }
    return false;
}

template <class T>
string ArrayList<T>::toString(string (*item2str)(T &)) const
{
    stringstream result;
    result << "[";
    for (int i = 0; i < count; i++)
    {
        if (item2str)
            result << item2str(data[i]);
        else
            result << data[i];

        if (i < count - 1)
            result << ", ";
    }
    result << "]";
    return result.str();
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin()
{
    return front;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end()
{
    return back;
}

// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T> *pList, int index)
{
    // TODO
    if (pList)
    {
        if (index < 0 || index > pList->size())
            throw out_of_range("Index is invalid!");

        this->pList = pList;
        this->cursor = index;
    }
}

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator=(const ArrayList<T>::Iterator &other)
{
    this->pList = other.pList;
    this->cursor = other.cursor;
    return *this;
}

template <class T>
T &ArrayList<T>::Iterator::operator*()
{
    if (cursor < 0 || cursor >= pList->size())
        throw out_of_range("Iterator is out of range!");
    // FIXME: check for pList == nullptr
    return pList->get(cursor);
}

template <class T>
bool ArrayList<T>::Iterator::operator!=(const ArrayList<T>::Iterator &other) const
{
    return (this->pList != other.pList || this->cursor != other.cursor);
}

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator++()
{
    if (cursor == pList->size())
        throw out_of_range("Iterator cannot advance past end!");
    (this->cursor)++;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int)
{
    if (cursor == pList->size())
        throw out_of_range("Iterator cannot advance past end!");
    Iterator temp(this->pList, this->cursor);
    (this->cursor)++;
    return temp;
}

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator--()
{
    if (cursor == 0)
        throw out_of_range("Iterator cannot move before begin!");
    (this->cursor)--;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int)
{
    if (cursor == 0)
        throw out_of_range("Iterator cannot move before begin!");
    Iterator temp(this->pList, this->cursor);
    (this->cursor)--;
    return temp;
}

// TODO: implement other methods of ArrayList::Iterator

// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr), count(0)
{
    front = Iterator(head);
    back = Iterator(head);
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
    clear();
}

template <class T>
void SinglyLinkedList<T>::rangeCheck(int index)
{
    if (index < 0 || index >= count)
        throw out_of_range("Index is invalid!");
}

template <class T>
void SinglyLinkedList<T>::add(T e)
{
    Node *temp = new Node(e);
    if (count == 0)
    {
        head = temp;
        tail = temp;
        count++;
        return;
    }

    tail->next = temp;
    tail = tail->next;
    count++;
}

template <class T>
void SinglyLinkedList<T>::insertAtHead(T e)
{
    Node *temp = new Node(e);
    if (count == 0)
    {
        head = temp;
        tail = temp;
        return;
    }

    temp->next = head;
    head = temp;
    count++;
}

template <class T>
void SinglyLinkedList<T>::add(int index, T e)
{
    if (index < 0 || index > count)
        throw out_of_range("Index is invalid!");

    if (index == 0)
    {
        insertAtHead(e);
        return;
    }

    if (index == count) // insert at tail
    {
        add(e);
        return;
    }

    Node *prev = head;

    for (int i = 0; i < index - 1; i++)
        prev = prev->next;

    Node *temp = new Node(e);
    temp->next = prev->next;
    prev->next = temp;
    count++;
}

template <class T>
T SinglyLinkedList<T>::removeHead()
{
    Node *temp = head;
    head = head->next;
    if (count == 1) // if count == 1
        tail = nullptr;

    T value = temp->data;
    delete temp;
    count--;
    return value;
}

template <class T>
T SinglyLinkedList<T>::removeAt(int index)
{
    rangeCheck(index);
    // Case 1: head deletion
    if (index == 0)
    {
        return removeHead();
    }

    // Case 2: middle or tail deletion
    Node *prev = head;
    for (int i = 0; i < index - 1; i++)
        prev = prev->next;

    if (index == count - 1) // deletion at tail
    { 
        tail = prev;        // move tail to previous
    }
    Node *temp = prev->next;
    prev->next = temp->next;

    T value = temp->data;
    delete temp;
    count--;
    return value;
}

template <class T>
bool SinglyLinkedList<T>::removeItem(T item)
{
    if (head == nullptr)
        return false;

    if (item == head->data)
    {
        removeHead();
        return true;
    }

    Node *prev = head, *temp = head->next;
    while (temp != nullptr && temp->data != item)
    {
        prev = prev->next;
        temp = temp->next;
    }

    if (temp == nullptr)
        return false;

    if (temp == tail)
        tail = prev;

    prev->next = temp->next;
    delete temp;
    count--;
    back--;
    return true;
}

template <class T>
bool SinglyLinkedList<T>::empty() const
{
    return count == 0;
}

template <class T>
int SinglyLinkedList<T>::size() const
{
    return count;
}

template <class T>
void SinglyLinkedList<T>::clear()
{
    Node *temp = head, *next;
    while (temp != nullptr)
    {
        next = temp->next;
        delete temp;
        temp = next;
    }
    count = 0;
    head = nullptr;
    tail = nullptr;
}

template <class T>
T &SinglyLinkedList<T>::get(int index)
{
    rangeCheck(index);
    Node *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp->data;
}

template <class T>
int SinglyLinkedList<T>::indexOf(T item) const
{
    Node *temp = head;
    for (int i = 0; i < count; i++)
    {
        if (temp->data == item)
            return i;

        temp = temp->next;
    }
    return -1;
}

template <class T>
bool SinglyLinkedList<T>::contains(T item) const
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == item)
            return true;
        temp = temp->next;
    }
    return false;
}

template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T &) = 0) const
{
    stringstream result;
    result << "[";
    Node *temp = head;
    while (temp != nullptr)
    {
        if (item2str)
            result << item2str(temp->data);
        else
            result << temp->data;

        if (i < count - 1)
            result << "]->[";
    }
    result << "]";
    return result.str();
}



// TODO: implement other methods of SinglyLinkedList

// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node *node)
{
    // TODO
}

// TODO: implement other methods of SinglyLinkedList::Iterator

// ----------------- VectorStore Implementation -----------------

VectorStore::VectorStore(int dimension, EmbedFn embeddingFunction)
{
    // TODO
}

VectorStore::~VectorStore()
{
    // TODO
}

// TODO: implement other methods of VectorStore

// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
