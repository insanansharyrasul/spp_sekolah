#pragma once
#include <stdexcept>

template <typename T>
class SimpleQueue {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& item) : data(item), next(nullptr) {}
    };
    
    Node* front;
    Node* rear;
    int size;
    
public:
    SimpleQueue() : front(nullptr), rear(nullptr), size(0) {}
    
    ~SimpleQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    void enqueue(const T& item) {
        Node* newNode = new Node(item);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        
        Node* temp = front;
        T data = temp->data;
        front = front->next;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;
        size--;
        return data;
    }
    
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
    
    int getSize() const {
        return size;
    }
};
