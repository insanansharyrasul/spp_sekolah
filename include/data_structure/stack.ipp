#include <iostream>
#include "stack.hpp"
using namespace std;

template <typename T>
Node<T>::Node(T data) {
    this->data = data;
    this->next = nullptr;
}

template <typename T>
Stack<T>::Stack() {
    this->top = nullptr;
    this->size = 0;
}

template <typename T>
void Stack<T>::push(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (this->top == nullptr) {
        this->top = newNode;
    } else {
        newNode->next = this->top;
        this->top = newNode;
    }
    this->size++;
}

template <typename T>
void Stack<T>::pop() {
    if (this->top == nullptr) {
        cout << "Stack is empty" << endl;
    } else {
        Node<T>* temp = this->top;
        this->top = this->top->next;
        delete temp;
        this->size--;
    }
}

template <typename T>
void Stack<T>::display() {
    Node<T>* temp = this->top;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

template <typename T>
int Stack<T>::getSize() {
    return this->size;
}

template <typename T>
Stack<T>::~Stack() {
    while (this->top != nullptr) {
        Node<T>* temp = this->top;
        this->top = this->top->next;
        delete temp;
    }
}