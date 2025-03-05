#include <iostream>

#include <siswa.h>
using namespace std;

class Node {
    public:
        Siswa siswa;
        Node* next;
        Node (Siswa siswa) {
            this->siswa = siswa;
            this->next = nullptr;
        }
};

class Stack {
    private:
        Node* top;
        int size;
    public:
        Stack() {
            this->top = nullptr;
            this->size = 0;
        }

        void push(Siswa data) {
            Node* newNode = new Node(data);
            if (this->top == nullptr) {
                this->top = newNode;
            } else {
                newNode->next = this->top;
                this->top = newNode;
            }
            this->size++;
        }

        void pop() {
            if (this->top == nullptr) {
                cout << "Stack is empty" << endl;
            } else {
                Node* temp = this->top;
                this->top = this->top->next;
                delete temp;
                this->size--;
            }
        }

        void display() {
            Node* temp = this->top;
            while (temp != nullptr) {
                cout << temp->siswa.nama << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        int getSize() {
            return this->size;
        }
};