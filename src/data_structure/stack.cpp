#include <siswa.h>
#include <stack.h>

#include <iostream>
using namespace std;

Node::Node(Siswa siswa) {
    this->siswa = siswa;
    this->next = nullptr;
}

Stack::Stack() {
    this->top = nullptr;
    this->size = 0;
}

void Stack::push(Siswa data) {
    Node* newNode = new Node(data);
    if (this->top == nullptr) {
        this->top = newNode;
    } else {
        newNode->next = this->top;
        this->top = newNode;
    }
    this->size++;
}

void Stack::pop() {
    if (this->top == nullptr) {
        cout << "Stack is empty" << endl;
    } else {
        Node* temp = this->top;
        this->top = this->top->next;
        delete temp;
        this->size--;
    }
}

void Stack::display() {
    Node* temp = this->top;
    while (temp != nullptr) {
        cout << temp->siswa.nama << " ";
        temp = temp->next;
    }
    cout << endl;
}

int Stack::getSize() {
    return this->size;
}