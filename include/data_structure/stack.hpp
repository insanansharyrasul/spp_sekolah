#pragma once

template <typename T>
class Node {
   public:
    T data;
    Node* next;
    Node(T);
};

template <typename T>
class Stack {
   private:
    Node<T>* top;
    int size;

   public:
    Stack();
    void push(T);
    void pop();
    void display();
    int getSize();
    ~Stack();
};

#include "stack.ipp"