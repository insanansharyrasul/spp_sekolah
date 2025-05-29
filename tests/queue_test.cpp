#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>
#include <data_structures/SimpleQueue.hpp>

class QueuePerformanceTester {
private:
    std::mt19937 rng;
    
public:
    QueuePerformanceTester() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    
    // Test enqueue operations with n data
    void testEnqueuePerformance(int n) {
        std::cout << "\n=== Testing ENQUEUE operations with " << n << " elements ===" << std::endl;
        
        SimpleQueue<int> queue;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            queue.enqueue(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per enqueue: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Final queue size: " << queue.getSize() << std::endl;
    }
    
    // Test dequeue operations with n data
    void testDequeuePerformance(int n) {
        std::cout << "\n=== Testing DEQUEUE operations with " << n << " elements ===" << std::endl;
        
        SimpleQueue<int> queue;
        
        // First, fill the queue
        for (int i = 0; i < n; ++i) {
            queue.enqueue(i);
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            queue.dequeue();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per dequeue: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Final queue size: " << queue.getSize() << std::endl;
    }
    
    // Test mixed enqueue/dequeue operations
    void testMixedOperations(int n) {
        std::cout << "\n=== Testing MIXED operations with " << n << " operations ===" << std::endl;
        
        SimpleQueue<int> queue;
        std::uniform_int_distribution<int> dist(0, 1);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        int enqueueCount = 0, dequeueCount = 0;
        
        for (int i = 0; i < n; ++i) {
            if (queue.isEmpty() || dist(rng) == 0) {
                // Enqueue operation
                queue.enqueue(i);
                enqueueCount++;
            } else {
                // Dequeue operation
                queue.dequeue();
                dequeueCount++;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Enqueue operations: " << enqueueCount << std::endl;
        std::cout << "Dequeue operations: " << dequeueCount << std::endl;
        std::cout << "Average per operation: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Final queue size: " << queue.getSize() << std::endl;
    }
    
    // Test with different data types
    void testStringPerformance(int n) {
        std::cout << "\n=== Testing STRING operations with " << n << " elements ===" << std::endl;
        
        SimpleQueue<std::string> queue;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            queue.enqueue("String_" + std::to_string(i));
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Enqueue time: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per enqueue: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        
        // Test dequeue performance for strings
        start = std::chrono::high_resolution_clock::now();
        
        while (!queue.isEmpty()) {
            queue.dequeue();
        }
        
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Dequeue time: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per dequeue: " << std::fixed << std::setprecision(3) 
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
            SimpleQueue<int> queue;
            
            auto start = std::chrono::high_resolution_clock::now();
            
            for (int i = 0; i < size; ++i) {
                queue.enqueue(i);
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << std::left << std::setw(15) << size
                      << std::setw(20) << duration.count()
                      << std::setw(20) << std::fixed << std::setprecision(3) << (double)duration.count() / size
                      << std::fixed << std::setprecision(0) << (size * 1000000.0) / duration.count() << std::endl;
        }
    }
    
    // Test queue correctness with performance
    void testCorrectness(int n) {
        std::cout << "\n=== Testing CORRECTNESS with " << n << " elements ===" << std::endl;
        
        SimpleQueue<int> queue;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Enqueue elements
        for (int i = 0; i < n; ++i) {
            queue.enqueue(i);
        }
        
        // Verify FIFO behavior
        bool correct = true;
        for (int i = 0; i < n; ++i) {
            if (queue.isEmpty() || queue.dequeue() != i) {
                correct = false;
                break;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "FIFO behavior: " << (correct ? "CORRECT" : "INCORRECT") << std::endl;
        std::cout << "Time for correctness test: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Queue is empty: " << (queue.isEmpty() ? "YES" : "NO") << std::endl;
    }
    
    // Test peek operation performance
    void testPeekPerformance(int n) {
        std::cout << "\n=== Testing PEEK operations with " << n << " elements ===" << std::endl;
        
        SimpleQueue<int> queue;
        
        // Fill the queue
        for (int i = 0; i < n; ++i) {
            queue.enqueue(i);
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Perform peek operations
        for (int i = 0; i < n; ++i) {
            queue.peek();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per peek: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Queue size after peek operations: " << queue.getSize() << std::endl;
    }
    
    // Test queue vs stack performance comparison
    void testQueueVsStackComparison(int n) {
        std::cout << "\n=== Testing QUEUE vs STACK Performance with " << n << " elements ===" << std::endl;
        
        SimpleQueue<int> queue;
        
        // Test queue operations
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            queue.enqueue(i);
        }
        for (int i = 0; i < n; ++i) {
            queue.dequeue();
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto queue_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Queue total time: " << queue_duration.count() << " microseconds" << std::endl;
        std::cout << "Queue ops/sec: " << std::fixed << std::setprecision(0) 
                  << (n * 2 * 1000000.0) / queue_duration.count() << " ops/sec" << std::endl;
    }
    
    // Run all tests
    void runAllTests() {
        std::cout << "==========================================" << std::endl;
        std::cout << "    SimpleQueue Performance Tests" << std::endl;
        std::cout << "==========================================" << std::endl;
        
        // Test different sizes
        std::vector<int> sizes = {1000, 10000, 100000, 1000000};
        
        for (int size : sizes) {
            testEnqueuePerformance(size);
            testDequeuePerformance(size);
            testMixedOperations(size);
            testPeekPerformance(size);
        }
        
        // Test with strings
        testStringPerformance(10000);
        
        // Test memory growth
        testMemoryGrowth({1000, 5000, 10000, 50000, 100000, 500000, 1000000});
        
        // Test correctness
        testCorrectness(10000);
        
        // Test comparison
        testQueueVsStackComparison(100000);
    }
};

int main() {
    try {
        QueuePerformanceTester tester;
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