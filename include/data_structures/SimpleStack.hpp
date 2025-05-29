#pragma once

#include <stdexcept>

template <typename T>
class SimpleStack {
   private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* top_node;
    size_t stack_size;

   public:
    SimpleStack() : top_node(nullptr), stack_size(0) {}
    
    ~SimpleStack() {
        clear();
    }
    
    SimpleStack(const SimpleStack& other) : top_node(nullptr), stack_size(0) {
        if (other.top_node != nullptr) {
            SimpleStack temp;
            Node* current = other.top_node;
            while (current != nullptr) {
                temp.push(current->data);
                current = current->next;
            }
            
            while (!temp.isEmpty()) {
                push(temp.pop());
            }
        }
    }
    
    SimpleStack& operator=(const SimpleStack& other) {
        if (this != &other) {
            clear();
            if (other.top_node != nullptr) {
                SimpleStack temp;
                Node* current = other.top_node;
                while (current != nullptr) {
                    temp.push(current->data);
                    current = current->next;
                }
                
                while (!temp.isEmpty()) {
                    push(temp.pop());
                }
            }
        }
        return *this;
    }

    void push(const T& element) {
        Node* new_node = new Node(element);
        new_node->next = top_node;
        top_node = new_node;
        stack_size++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from an empty stack");
        }

        Node* temp = top_node;
        T data = temp->data;
        top_node = top_node->next;
        delete temp;
        stack_size--;
        return data;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot peek at an empty stack");
        }
        return top_node->data;
    }

    bool isEmpty() const {
        return top_node == nullptr;
    }

    size_t size() const {
        return stack_size;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};
