#ifndef STACK_H
#define STACK_H
#include <iostream>

#include "data.hpp"

class Node {
   public:
    Siswa siswa;
    Node* next;
    Node(Siswa siswa);
};

class Stack {
   private:
    Node* top;
    int size;

   public:
    Stack();
    void push(Siswa data);
    void pop();
    void display();
    int getSize();
};
#endif