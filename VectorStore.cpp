#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

template <class T>
ArrayList<T>::ArrayList(int initCapacity = 10) : capacity(initCapacity), count(0) {
    begin = Iterator(this, 0);
    end = Iterator(this, 1);
    data = new T[capacity];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) : capacity(other.capacity), count(other.count) {
    this->data = new T[this->capacity];
    for (int i = 0; i < count; i++) {
        (this->data)[i] = (other.data)[i];
    }
    this->begin = other.begin;
    this->end = other.end;
}   

template <class T>
ArrayList<T>::~ArrayList() {
    delete[] data;
}

template <class T>
ArrayList<T>&  ArrayList<T>::operator=(const ArrayList<T>& other) {
    delete[] this->data;
    this->capacity = other.capacity;
    this->data = new T[this->capacity];
    memcpy(this->data, other.data, sizeof(T) * other.count);
    this->count = other.count;
    this->begin = other.begin;
    this->end = other.end;
    return *this;
}

// TODO: implement other methods of ArrayList

template <class T>
void ArrayList<T>::setCapacity(int newCapacity) {
    T *newData = new T[newCapacity];
    memcpy(newData, data, sizeof(T) * count);
    capacity = newCapacity;
    delete[] data;
    data = newData;
}

template <class T>
void ArrayList<T>::ensureCapacity(int cap) {
    if (cap > this->capacity) {
        int newCapacity = (capacity * 3)/2 + 1;
        if (newCapacity < cap) {
            newCapacity = cap;
        }
        setCapacity(newCapacity);
    }
}

template <class T>
void ArrayList<T>::rangeCheck(int index) {
    if (index < 0 || index >= count)
        throw throw out_of_range("Index is invalid!");
}

template <class T>
void ArrayList<T>::add(T e) {
    // TODO: after implementing iterators
    ensureCapacity(count + 1);
    data[count++] = e;
    end++;
}

template <class T>
void ArrayList<T>::add(int index, T e) {
    if (index < 0 || index > count)
        throw out_of_range("Index is invalid!");

    ensureCapacity(count + 1);

    int moveCount = count - index;
    if (moveCount != 0) // moveCount == 0: insert at end
        memmove(storage + index + 1, storage + index, sizeof(T) * moveCount);
    
    data[index] = e;
    count++;
}

template <class T>
T ArrayList<T>::removeAt(int index) {
    rangeCheck(index);
    int moveCount = count - index - 1;
    if (moveCount > 0)
        memmove(data + index, data + (index + 1), sizeof(T) * moveCount);
    
    count--;
}

template <class T>
bool ArrayList<T>::empty() const {
    return count == 0;
}

template <class T>
int ArrayList<T>::size() const {
    return count;
}

template <class T>
void ArrayList<T>::clear() {
    delete[] data;
    capacity = 10;
    count = 0;
    data = new T[capacity];
}

template <class T>
T& ArrayList<T>::get(int index) {
    rangeCheck(index);
    return data[index];
}

template <class T>
void ArrayList<T>::set(int index, T e) {
    rangeCheck(index);
    data[index] = e;
}

template <class T>
int ArrayList<T>::indexOf(T item) const {
    for (int i = 0; i < count; i++) {
        if (data[i] == item)
            return i;
    }
    return -1;
}

template <class T>
bool ArrayList<T>::contains(T item) const {
    for (int i = 0; i < count; i++) {
        if (data[i] == item)
            return true;
    }
    return false;
}

template <class T>
string ArrayList<T>::toString(string (*item2str)(T&)) const {
    stringstream result;
    result << "[";
    for (int i = 0; i < count; i++) {
        if (item2str)
            result << item2str(data[i]);
        else
            result << data[i];

        if (i < count - 1)
            result << ",";
    }
    result << "]";
}

// ----------------- Iterator of ArrayList Implementation -----------------
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index) {
    // TODO
    if (pList) {
        if (index < 0 || index > pList->size())
            throw out_of_range("Index is invalid!");
        
        this->pList = pList;
        this->cursor = index;
    }
}

template <class T>
ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator=(const ArrayList<T>::Iterator& other) {
    this->pList = other.pList;
    this->cursor = other.cursor;
    return *this;
}

template <class T>
T& ArrayList<T>::Iterator::operator*() {
    if (cursor < 0 || cursor >= pList->size())
        throw out_of_range("Iterator is out of range!");
    // FIXME: check for pList == nullptr
    return pList->get(cursor);
}

template <class T>
bool ArrayList<T>::Iterator::operator!=(const ArrayList<T>::Iterator& other) const {
    if (this->pList != other.pList || this->cursor != other.cursor) {
        return false;
    }
    return true;
}

template <class T>
ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator++() {
    if (cursor == pList->size())
        throw out_of_range("Iterator cannot advance past end!");
    cursor++;
    return *this;
}

template <class T>
ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int) {
    if (cursor == pList->size())
        throw out_of_range("Iterator cannot advance past end!");
    Iterator temp(this->pList, this->cursor);
    (this->cursor)++;
    return temp;
} 

template <class T>
ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator--() {
    if (cursor == 0)
        throw out_of_range("Iterator cannot move before begin!");
    cursor--;
    return *this;
}

template <class T>
ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int) {
    if (cursor == 0)
        throw out_of_range("Iterator cannot move before begin!");
    Iterator temp(this->pList, this->cursor);
    (this->cursor)++;
    return temp;
}


// TODO: implement other methods of ArrayList::Iterator



// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    // TODO
}   

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    // TODO
}   

// TODO: implement other methods of SinglyLinkedList



// ----------------- Iterator of SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node) {
    // TODO
}   

// TODO: implement other methods of SinglyLinkedList::Iterator



// ----------------- VectorStore Implementation -----------------

VectorStore::VectorStore(int dimension = 512, EmbedFn embeddingFunction = nullptr) {
    // TODO
}

VectorStore::~VectorStore() {
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
