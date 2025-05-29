#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>
#include <data_structures/SimpleStack.hpp>

class StackPerformanceTester {
private:
    std::mt19937 rng;
    
public:
    StackPerformanceTester() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    
    // Test push operations with n data
    void testPushPerformance(int n) {
        std::cout << "\n=== Testing PUSH operations with " << n << " elements ===" << std::endl;
        
        SimpleStack<int> stack;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            stack.push(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per push: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Final stack size: " << stack.size() << std::endl;
    }
    
    // Test pop operations with n data
    void testPopPerformance(int n) {
        std::cout << "\n=== Testing POP operations with " << n << " elements ===" << std::endl;
        
        SimpleStack<int> stack;
        
        // First, fill the stack
        for (int i = 0; i < n; ++i) {
            stack.push(i);
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            stack.pop();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per pop: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Final stack size: " << stack.size() << std::endl;
    }
    
    // Test mixed push/pop operations
    void testMixedOperations(int n) {
        std::cout << "\n=== Testing MIXED operations with " << n << " operations ===" << std::endl;
        
        SimpleStack<int> stack;
        std::uniform_int_distribution<int> dist(0, 1);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        int pushCount = 0, popCount = 0;
        
        for (int i = 0; i < n; ++i) {
            if (stack.isEmpty() || dist(rng) == 0) {
                // Push operation
                stack.push(i);
                pushCount++;
            } else {
                // Pop operation
                stack.pop();
                popCount++;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Push operations: " << pushCount << std::endl;
        std::cout << "Pop operations: " << popCount << std::endl;
        std::cout << "Average per operation: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Final stack size: " << stack.size() << std::endl;
    }
    
    // Test with different data types
    void testStringPerformance(int n) {
        std::cout << "\n=== Testing STRING operations with " << n << " elements ===" << std::endl;
        
        SimpleStack<std::string> stack;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            stack.push("String_" + std::to_string(i));
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Push time: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per push: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        
        // Test pop performance for strings
        start = std::chrono::high_resolution_clock::now();
        
        while (!stack.isEmpty()) {
            stack.pop();
        }
        
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Pop time: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per pop: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
    }
    
    // Memory usage test
    void testMemoryGrowth(const std::vector<int>& sizes) {
        std::cout << "\n=== Testing MEMORY GROWTH ===" << std::endl;
        std::cout << std::left << std::setw(15) << "Elements" 
                  << std::setw(20) << "Time (μs)" 
                  << std::setw(20) << "Avg per op (μs)" 
                  << "Ops/sec" << std::endl;
        std::cout << std::string(70, '-') << std::endl;
        
        for (int size : sizes) {
            SimpleStack<int> stack;
            
            auto start = std::chrono::high_resolution_clock::now();
            
            for (int i = 0; i < size; ++i) {
                stack.push(i);
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << std::left << std::setw(15) << size
                      << std::setw(20) << duration.count()
                      << std::setw(20) << std::fixed << std::setprecision(3) << (double)duration.count() / size
                      << std::fixed << std::setprecision(0) << (size * 1000000.0) / duration.count() << std::endl;
        }
    }
    
    // Test stack correctness with performance
    void testCorrectness(int n) {
        std::cout << "\n=== Testing CORRECTNESS with " << n << " elements ===" << std::endl;
        
        SimpleStack<int> stack;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Push elements
        for (int i = 0; i < n; ++i) {
            stack.push(i);
        }
        
        // Verify LIFO behavior
        bool correct = true;
        for (int i = n - 1; i >= 0; --i) {
            if (stack.isEmpty() || stack.pop() != i) {
                correct = false;
                break;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "LIFO behavior: " << (correct ? "CORRECT" : "INCORRECT") << std::endl;
        std::cout << "Time for correctness test: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Stack is empty: " << (stack.isEmpty() ? "YES" : "NO") << std::endl;
    }
    
    // Run all tests
    void runAllTests() {
        std::cout << "==========================================" << std::endl;
        std::cout << "    SimpleStack Performance Tests" << std::endl;
        std::cout << "==========================================" << std::endl;
        
        // Test different sizes
        std::vector<int> sizes = {1000, 10000, 100000, 1000000};
        
        for (int size : sizes) {
            testPushPerformance(size);
            testPopPerformance(size);
            testMixedOperations(size);
        }
        
        // Test with strings
        testStringPerformance(10000);
        
        // Test memory growth
        testMemoryGrowth({1000, 5000, 10000, 50000, 100000, 500000, 1000000});
        
        // Test correctness
        testCorrectness(10000);
    }
};

int main() {
    try {
        StackPerformanceTester tester;
        tester.runAllTests();
        
        std::cout << "\n==========================================" << std::endl;
        std::cout << "    All tests completed successfully!" << std::endl;
        std::cout << "==========================================" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error during testing: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}