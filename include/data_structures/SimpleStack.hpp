#pragma once

#include <stdexcept>
#include <vector>

template <typename T>
class SimpleStack {
   private:
    std::vector<T> elements;

   public:
    void push(const T& element) {
        elements.push_back(element);
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Cannot pop from an empty stack");
        }

        T top = elements.back();
        elements.pop_back();
        return top;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Cannot peek at an empty stack");
        }
        return elements.back();
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }

    void clear() {
        elements.clear();
    }
};
