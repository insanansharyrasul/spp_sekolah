#include <iostream>
#include <iomanip>

int main() {
    // Basic usage - setting field width to 10 characters
    std::cout << "[" << std::setw(10) << "Hello" << "]" << std::endl;
    // Output: [     Hello]
    
    // The effect only applies to the next output operation
    std::cout << "[" << std::setw(10) << "Hi" << "][" << "World" << "]" << std::endl;
    // Output: [        Hi][World]
    
    return 0;
}