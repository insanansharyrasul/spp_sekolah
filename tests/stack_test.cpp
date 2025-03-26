#include <stack.hpp>

int main() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.pop();
    stack.display();
    return 0;
}