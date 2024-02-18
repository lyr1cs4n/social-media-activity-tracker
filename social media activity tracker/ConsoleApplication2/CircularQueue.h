#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>
#include <algorithm> // For std::fill

template <typename T>
class CircularQueue {
public:
    static const int MAX_CAPACITY = 20;
    int currentSize;
    T* elements[MAX_CAPACITY];
    int frontIndex;
    int rearIndex;

    CircularQueue();

    bool isEmpty() const;

    bool isFull() const;

    void enqueue(const T& newElement);

    void dequeue();

    void display() const;
    void displayposts() const;
    T* search(const T& target) const;

private:
    int getNextIndex(int currentIndex) const;
};

using namespace std;

template<typename T>
CircularQueue<T>::CircularQueue() : frontIndex(0), rearIndex(0), currentSize(0) {
    fill(begin(elements), end(elements), nullptr);
}

template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return currentSize == 0;
}

template<typename T>
bool CircularQueue<T>::isFull() const {
    return currentSize == MAX_CAPACITY;
}

template<typename T>
void CircularQueue<T>::enqueue(const T& newElement) {
    if (isFull()) {
        dequeue();
    }

    elements[rearIndex] = new T(newElement);  // Allocate memory for the new element
    rearIndex = getNextIndex(rearIndex);
    currentSize++;
}

template<typename T>
void CircularQueue<T>::dequeue() {
    if (!isEmpty()) {
        delete elements[frontIndex];  // Delete the memory of the element being dequeued
        elements[frontIndex] = nullptr;  // Set to nullptr after deletion
        frontIndex = getNextIndex(frontIndex);
        currentSize--;
    }
    else {
        cout << "[*] "
            << "\033[33mQueue is empty. Cannot dequeue. \033[0m" << endl;
    }
}

template<typename T>
void CircularQueue<T>::display() const {
    if (isEmpty()) {
        cout << "   - Empty" << endl;
        return;
    }
    cout << endl;
    int counter = 0;
    for (int i = 0; i < currentSize; ++i) {
        counter++;
        cout<< *elements[(frontIndex + i) % MAX_CAPACITY] << endl;
    }
}
template<typename T>
void CircularQueue<T>::displayposts() const {
    if (isEmpty()) {
        cout << "Empty" << endl;
        return;
    }

    for (int i = 0; i < currentSize; ++i) {
        if (elements[(frontIndex + i) % MAX_CAPACITY]->type == Activity::ActivityData::Type::POST) {
            cout << *elements[(frontIndex + i) % MAX_CAPACITY] << endl;
        }
    }
}
template<typename T>
int CircularQueue<T>::getNextIndex(int currentIndex) const {
    return (currentIndex + 1) % MAX_CAPACITY;
}

template<typename T>
T* CircularQueue<T>::search(const T& target) const {
    for (int i = 0; i < currentSize; ++i) {
        if (*elements[(frontIndex + i) % MAX_CAPACITY] == target) {
            return elements[(frontIndex + i) % MAX_CAPACITY];
        }
    }
    return nullptr;
}

#endif
