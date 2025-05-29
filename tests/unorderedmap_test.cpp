#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>

class UnorderedMapPerformanceTester {
private:
    std::mt19937 rng;
    
public:
    UnorderedMapPerformanceTester() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    
    // Generate random keys
    std::vector<int> generateRandomKeys(int n, int min_val = 1, int max_val = 1000000) {
        std::vector<int> keys;
        keys.reserve(n);
        std::uniform_int_distribution<int> dist(min_val, max_val);
        
        for (int i = 0; i < n; ++i) {
            keys.push_back(dist(rng));
        }
        return keys;
    }
    
    // Generate sequential keys
    std::vector<int> generateSequentialKeys(int n) {
        std::vector<int> keys;
        keys.reserve(n);
        for (int i = 0; i < n; ++i) {
            keys.push_back(i);
        }
        return keys;
    }
    
    // Test insert operations with n data
    void testInsertPerformance(int n) {
        std::cout << "\n=== Testing INSERT operations with " << n << " elements ===" << std::endl;
        
        std::unordered_map<int, int> map;
        std::vector<int> keys = generateRandomKeys(n);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            map[keys[i]] = i;
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per insert: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Final map size: " << map.size() << std::endl;
        std::cout << "Load factor: " << std::fixed << std::setprecision(3) << map.load_factor() << std::endl;
        std::cout << "Bucket count: " << map.bucket_count() << std::endl;
    }
    
    // Test lookup operations with n data
    void testLookupPerformance(int n) {
        std::cout << "\n=== Testing LOOKUP operations with " << n << " elements ===" << std::endl;
        
        std::unordered_map<int, int> map;
        std::vector<int> keys = generateRandomKeys(n);
        
        // First, fill the map
        for (int i = 0; i < n; ++i) {
            map[keys[i]] = i;
        }
        
        // Shuffle keys for random access pattern
        std::shuffle(keys.begin(), keys.end(), rng);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        int found_count = 0;
        for (int i = 0; i < n; ++i) {
            auto it = map.find(keys[i]);
            if (it != map.end()) {
                found_count++;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per lookup: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Elements found: " << found_count << "/" << n << std::endl;
    }
    
    // Test erase operations with n data
    void testErasePerformance(int n) {
        std::cout << "\n=== Testing ERASE operations with " << n << " elements ===" << std::endl;
        
        std::unordered_map<int, int> map;
        std::vector<int> keys = generateRandomKeys(n);
        
        // First, fill the map
        for (int i = 0; i < n; ++i) {
            map[keys[i]] = i;
        }
        
        // Shuffle keys for random erase pattern
        std::shuffle(keys.begin(), keys.end(), rng);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        int erased_count = 0;
        for (int i = 0; i < n; ++i) {
            erased_count += map.erase(keys[i]);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per erase: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Elements erased: " << erased_count << "/" << n << std::endl;
        std::cout << "Final map size: " << map.size() << std::endl;
    }
    
    // Test mixed operations
    void testMixedOperations(int n) {
        std::cout << "\n=== Testing MIXED operations with " << n << " operations ===" << std::endl;
        
        std::unordered_map<int, int> map;
        std::uniform_int_distribution<int> op_dist(0, 2); // 0=insert, 1=lookup, 2=erase
        std::uniform_int_distribution<int> key_dist(1, n * 2);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        int insert_count = 0, lookup_count = 0, erase_count = 0;
        
        for (int i = 0; i < n; ++i) {
            int operation = op_dist(rng);
            int key = key_dist(rng);
            
            if (operation == 0) {
                // Insert operation
                map[key] = i;
                insert_count++;
            } else if (operation == 1) {
                // Lookup operation
                auto it = map.find(key);
                lookup_count++;
            } else {
                // Erase operation
                map.erase(key);
                erase_count++;
            }
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Insert operations: " << insert_count << std::endl;
        std::cout << "Lookup operations: " << lookup_count << std::endl;
        std::cout << "Erase operations: " << erase_count << std::endl;
        std::cout << "Average per operation: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Operations per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " ops/sec" << std::endl;
        std::cout << "Final map size: " << map.size() << std::endl;
    }
    
    // Test with string keys
    void testStringKeyPerformance(int n) {
        std::cout << "\n=== Testing STRING KEY operations with " << n << " elements ===" << std::endl;
        
        std::unordered_map<std::string, int> map;
        std::vector<std::string> keys;
        keys.reserve(n);
        
        // Generate string keys
        for (int i = 0; i < n; ++i) {
            keys.push_back("Key_" + std::to_string(i) + "_" + std::to_string(rng()));
        }
        
        // Test insert
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            map[keys[i]] = i;
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto insert_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Insert time: " << insert_duration.count() << " microseconds" << std::endl;
        std::cout << "Average per insert: " << std::fixed << std::setprecision(3) 
                  << (double)insert_duration.count() / n << " microseconds" << std::endl;
        
        // Test lookup
        std::shuffle(keys.begin(), keys.end(), rng);
        
        start = std::chrono::high_resolution_clock::now();
        
        int found_count = 0;
        for (int i = 0; i < n; ++i) {
            auto it = map.find(keys[i]);
            if (it != map.end()) {
                found_count++;
            }
        }
        
        end = std::chrono::high_resolution_clock::now();
        auto lookup_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Lookup time: " << lookup_duration.count() << " microseconds" << std::endl;
        std::cout << "Average per lookup: " << std::fixed << std::setprecision(3) 
                  << (double)lookup_duration.count() / n << " microseconds" << std::endl;
        std::cout << "Elements found: " << found_count << "/" << n << std::endl;
    }
    
    // Test hash collision performance
    void testHashCollisionPerformance(int n) {
        std::cout << "\n=== Testing HASH COLLISION performance with " << n << " elements ===" << std::endl;
        
        std::unordered_map<int, int> map;
        
        // Create keys that might cause more collisions (sequential)
        std::vector<int> keys = generateSequentialKeys(n);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n; ++i) {
            map[keys[i]] = i;
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per insert: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Load factor: " << std::fixed << std::setprecision(3) << map.load_factor() << std::endl;
        std::cout << "Bucket count: " << map.bucket_count() << std::endl;
        std::cout << "Max bucket size: " << map.max_bucket_count() << std::endl;
        
        // Analyze bucket distribution
        size_t max_bucket_size = 0;
        size_t empty_buckets = 0;
        for (size_t i = 0; i < map.bucket_count(); ++i) {
            size_t bucket_size = map.bucket_size(i);
            if (bucket_size == 0) {
                empty_buckets++;
            }
            max_bucket_size = std::max(max_bucket_size, bucket_size);
        }
        
        std::cout << "Empty buckets: " << empty_buckets << "/" << map.bucket_count() << std::endl;
        std::cout << "Max elements in single bucket: " << max_bucket_size << std::endl;
    }
    
    // Test reserve performance
    void testReservePerformance(int n) {
        std::cout << "\n=== Testing RESERVE performance with " << n << " elements ===" << std::endl;
        
        // Test without reserve
        {
            std::unordered_map<int, int> map;
            std::vector<int> keys = generateRandomKeys(n);
            
            auto start = std::chrono::high_resolution_clock::now();
            
            for (int i = 0; i < n; ++i) {
                map[keys[i]] = i;
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << "Without reserve - Time: " << duration.count() << " μs" << std::endl;
            std::cout << "Without reserve - Final bucket count: " << map.bucket_count() << std::endl;
        }
        
        // Test with reserve
        {
            std::unordered_map<int, int> map;
            map.reserve(n);
            std::vector<int> keys = generateRandomKeys(n);
            
            auto start = std::chrono::high_resolution_clock::now();
            
            for (int i = 0; i < n; ++i) {
                map[keys[i]] = i;
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << "With reserve - Time: " << duration.count() << " μs" << std::endl;
            std::cout << "With reserve - Final bucket count: " << map.bucket_count() << std::endl;
        }
    }
    
    // Memory usage test
    void testMemoryGrowth(const std::vector<int>& sizes) {
        std::cout << "\n=== Testing MEMORY GROWTH ===" << std::endl;
        std::cout << std::left << std::setw(15) << "Elements" 
                  << std::setw(20) << "Time (μs)" 
                  << std::setw(20) << "Avg per op (μs)" 
                  << std::setw(15) << "Load Factor"
                  << "Bucket Count" << std::endl;
        std::cout << std::string(85, '-') << std::endl;
        
        for (int size : sizes) {
            std::unordered_map<int, int> map;
            std::vector<int> keys = generateRandomKeys(size);
            
            auto start = std::chrono::high_resolution_clock::now();
            
            for (int i = 0; i < size; ++i) {
                map[keys[i]] = i;
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << std::left << std::setw(15) << size
                      << std::setw(20) << duration.count()
                      << std::setw(20) << std::fixed << std::setprecision(3) << (double)duration.count() / size
                      << std::setw(15) << std::fixed << std::setprecision(3) << map.load_factor()
                      << map.bucket_count() << std::endl;
        }
    }
    
    // Run all tests
    void runAllTests() {
        std::cout << "==========================================" << std::endl;
        std::cout << "   std::unordered_map Performance Tests" << std::endl;
        std::cout << "==========================================" << std::endl;
        
        // Test different sizes
        std::vector<int> sizes = {1000, 10000, 100000, 1000000};
        
        for (int size : sizes) {
            testInsertPerformance(size);
            testLookupPerformance(size);
            testErasePerformance(size);
            testMixedOperations(size);
        }
        
        // Test with strings
        testStringKeyPerformance(10000);
        
        // Test hash collisions
        testHashCollisionPerformance(100000);
        
        // Test reserve performance
        testReservePerformance(100000);
        
        // Test memory growth
        testMemoryGrowth({1000, 5000, 10000, 50000, 100000, 500000, 1000000});
    }
};

int main() {
    try {
        UnorderedMapPerformanceTester tester;
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