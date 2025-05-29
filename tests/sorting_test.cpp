#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <string>

class SortingPerformanceTester {
private:
    std::mt19937 rng;
    
public:
    SortingPerformanceTester() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}
    
    // Generate random data
    std::vector<int> generateRandomData(int n, int min_val = 1, int max_val = 1000000) {
        std::vector<int> data;
        data.reserve(n);
        std::uniform_int_distribution<int> dist(min_val, max_val);
        
        for (int i = 0; i < n; ++i) {
            data.push_back(dist(rng));
        }
        return data;
    }
    
    // Generate sorted data (best case)
    std::vector<int> generateSortedData(int n) {
        std::vector<int> data;
        data.reserve(n);
        for (int i = 0; i < n; ++i) {
            data.push_back(i);
        }
        return data;
    }
    
    // Generate reverse sorted data (worst case for some algorithms)
    std::vector<int> generateReverseSortedData(int n) {
        std::vector<int> data;
        data.reserve(n);
        for (int i = n; i > 0; --i) {
            data.push_back(i);
        }
        return data;
    }
    
    // Generate nearly sorted data
    std::vector<int> generateNearlySortedData(int n, double swap_probability = 0.1) {
        std::vector<int> data = generateSortedData(n);
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        
        for (int i = 0; i < n - 1; ++i) {
            if (dist(rng) < swap_probability) {
                std::swap(data[i], data[i + 1]);
            }
        }
        return data;
    }
    
    // Test std::sort performance
    void testStdSort(int n, const std::string& data_type) {
        std::cout << "\n=== Testing std::sort with " << n << " elements (" << data_type << ") ===" << std::endl;
        
        std::vector<int> data;
        if (data_type == "random") {
            data = generateRandomData(n);
        } else if (data_type == "sorted") {
            data = generateSortedData(n);
        } else if (data_type == "reverse") {
            data = generateReverseSortedData(n);
        } else if (data_type == "nearly_sorted") {
            data = generateNearlySortedData(n);
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::sort(data.begin(), data.end());
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per element: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Elements per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " elements/sec" << std::endl;
        
        // Verify sorting is correct
        bool is_sorted = std::is_sorted(data.begin(), data.end());
        std::cout << "Correctly sorted: " << (is_sorted ? "YES" : "NO") << std::endl;
    }
    
    void testStableSort(int n, const std::string& data_type) {
        std::cout << "\n=== Testing std::stable_sort with " << n << " elements (" << data_type << ") ===" << std::endl;
        
        std::vector<int> data;
        if (data_type == "random") {
            data = generateRandomData(n);
        } else if (data_type == "sorted") {
            data = generateSortedData(n);
        } else if (data_type == "reverse") {
            data = generateReverseSortedData(n);
        } else if (data_type == "nearly_sorted") {
            data = generateNearlySortedData(n);
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::stable_sort(data.begin(), data.end());
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per element: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Elements per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " elements/sec" << std::endl;
        
        // Verify sorting is correct
        bool is_sorted = std::is_sorted(data.begin(), data.end());
        std::cout << "Correctly sorted: " << (is_sorted ? "YES" : "NO") << std::endl;
    }
    
    // Test std::partial_sort performance
    void testPartialSort(int n, int k) {
        std::cout << "\n=== Testing std::partial_sort with " << n << " elements (top " << k << ") ===" << std::endl;
        
        std::vector<int> data = generateRandomData(n);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::partial_sort(data.begin(), data.begin() + k, data.end());
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per element: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Elements per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " elements/sec" << std::endl;
        
        // Verify partial sorting is correct
        bool is_partial_sorted = std::is_sorted(data.begin(), data.begin() + k);
        std::cout << "Correctly partial sorted: " << (is_partial_sorted ? "YES" : "NO") << std::endl;
    }
    
    // Test sorting with custom comparator
    void testCustomComparator(int n) {
        std::cout << "\n=== Testing std::sort with custom comparator (descending) ===" << std::endl;
        
        std::vector<int> data = generateRandomData(n);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::sort(data.begin(), data.end(), std::greater<int>());
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per element: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Elements per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " elements/sec" << std::endl;
        
        // Verify sorting is correct (descending)
        bool is_sorted = std::is_sorted(data.begin(), data.end(), std::greater<int>());
        std::cout << "Correctly sorted (descending): " << (is_sorted ? "YES" : "NO") << std::endl;
    }
    
    // Test string sorting performance
    void testStringSorting(int n) {
        std::cout << "\n=== Testing std::sort with strings (" << n << " elements) ===" << std::endl;
        
        std::vector<std::string> data;
        data.reserve(n);
        std::uniform_int_distribution<int> len_dist(5, 20);
        std::uniform_int_distribution<int> char_dist('a', 'z');
        
        // Generate random strings
        for (int i = 0; i < n; ++i) {
            int len = len_dist(rng);
            std::string str;
            str.reserve(len);
            for (int j = 0; j < len; ++j) {
                str += static_cast<char>(char_dist(rng));
            }
            data.push_back(str);
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        
        std::sort(data.begin(), data.end());
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
        std::cout << "Average per element: " << std::fixed << std::setprecision(3) 
                  << (double)duration.count() / n << " microseconds" << std::endl;
        std::cout << "Elements per second: " << std::fixed << std::setprecision(0) 
                  << (n * 1000000.0) / duration.count() << " elements/sec" << std::endl;
        
        // Verify sorting is correct
        bool is_sorted = std::is_sorted(data.begin(), data.end());
        std::cout << "Correctly sorted: " << (is_sorted ? "YES" : "NO") << std::endl;
    }
    
    // Compare sorting algorithms
    void compareSortingAlgorithms(int n, const std::string& data_type) {
        std::cout << "\n=== Comparing sorting algorithms with " << n << " elements (" << data_type << ") ===" << std::endl;
        std::cout << std::left << std::setw(20) << "Algorithm" 
                  << std::setw(15) << "Time (μs)" 
                  << std::setw(20) << "Avg per elem (μs)" 
                  << "Elems/sec" << std::endl;
        std::cout << std::string(75, '-') << std::endl;
        
        // Generate base data
        std::vector<int> base_data;
        if (data_type == "random") {
            base_data = generateRandomData(n);
        } else if (data_type == "sorted") {
            base_data = generateSortedData(n);
        } else if (data_type == "reverse") {
            base_data = generateReverseSortedData(n);
        } else if (data_type == "nearly_sorted") {
            base_data = generateNearlySortedData(n);
        }
        
        // Test std::sort
        {
            std::vector<int> data = base_data;
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(data.begin(), data.end());
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << std::left << std::setw(20) << "std::sort"
                      << std::setw(15) << duration.count()
                      << std::setw(20) << std::fixed << std::setprecision(3) << (double)duration.count() / n
                      << std::fixed << std::setprecision(0) << (n * 1000000.0) / duration.count() << std::endl;
        }
        
        // Test std::stable_sort
        {
            std::vector<int> data = base_data;
            auto start = std::chrono::high_resolution_clock::now();
            std::stable_sort(data.begin(), data.end());
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << std::left << std::setw(20) << "std::stable_sort"
                      << std::setw(15) << duration.count()
                      << std::setw(20) << std::fixed << std::setprecision(3) << (double)duration.count() / n
                      << std::fixed << std::setprecision(0) << (n * 1000000.0) / duration.count() << std::endl;
        }
        
        // Test std::sort with heap_sort (using make_heap, sort_heap)
        {
            std::vector<int> data = base_data;
            auto start = std::chrono::high_resolution_clock::now();
            std::make_heap(data.begin(), data.end());
            std::sort_heap(data.begin(), data.end());
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << std::left << std::setw(20) << "heap_sort"
                      << std::setw(15) << duration.count()
                      << std::setw(20) << std::fixed << std::setprecision(3) << (double)duration.count() / n
                      << std::fixed << std::setprecision(0) << (n * 1000000.0) / duration.count() << std::endl;
        }
    }
    
    // Memory growth test
    void testMemoryGrowth(const std::vector<int>& sizes) {
        std::cout << "\n=== Testing MEMORY GROWTH (std::sort) ===" << std::endl;
        std::cout << std::left << std::setw(15) << "Elements" 
                  << std::setw(20) << "Time (μs)" 
                  << std::setw(20) << "Avg per elem (μs)" 
                  << "Elems/sec" << std::endl;
        std::cout << std::string(75, '-') << std::endl;
        
        for (int size : sizes) {
            std::vector<int> data = generateRandomData(size);
            
            auto start = std::chrono::high_resolution_clock::now();
            std::sort(data.begin(), data.end());
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            std::cout << std::left << std::setw(15) << size
                      << std::setw(20) << duration.count()
                      << std::setw(20) << std::fixed << std::setprecision(3) << (double)duration.count() / size
                      << std::fixed << std::setprecision(0) << (size * 1000000.0) / duration.count() << std::endl;
        }
    }
    
    // Run all tests
    void runAllTests() {
        std::cout << "==========================================" << std::endl;
        std::cout << "    C++ Sorting Performance Tests" << std::endl;
        std::cout << "==========================================" << std::endl;
        
        // Test different sizes with random data
        std::vector<int> sizes = {1000, 10000, 100000, 1000000};
        std::vector<std::string> data_types = {"random", "sorted", "reverse", "nearly_sorted"};
        
        for (int size : sizes) {
            for (const std::string& type : data_types) {
                testStdSort(size, type);
            }
        }
        
        // Test stable sort
        testStableSort(100000, "random");
        
        // Test partial sort
        testPartialSort(100000, 1000);
        
        // Test custom comparator
        testCustomComparator(100000);
        
        // Test string sorting
        testStringSorting(10000);
        
        // Compare algorithms
        for (const std::string& type : data_types) {
            compareSortingAlgorithms(100000, type);
        }
        
        // Test memory growth
        testMemoryGrowth({1000, 5000, 10000, 50000, 100000, 500000, 1000000});
    }
};

int main() {
    try {
        SortingPerformanceTester tester;
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