/**
 * @class Singleton
 * @brief Implements the Singleton design pattern.
 *
 * The Singleton class ensures that only one instance of itself can be created,
 * providing a global point of access to that instance. This is achieved by:
 * - Making the constructor private to prevent direct instantiation.
 * - Providing a static method (getInstance) to access the single instance.
 * - Deleting the copy constructor and assignment operator to prevent copying.
 * - Using a static pointer to hold the instance and a mutex for thread-safe initialization.
 *
 * Purpose of the Singleton design pattern:
 * The Singleton pattern is used when exactly one object is needed to coordinate actions
 * across the system. It is commonly used for managing shared resources, configuration,
 * logging, or connection pools, where having multiple instances could lead to inconsistent
 * state or resource conflicts.
 */
#include <iostream>
#include <mutex>

// Singleton class definition
class Singleton {
private:
    // Private static pointer to the single instance
    static Singleton* instance;
    // Mutex for thread-safe initialization (optional for single-threaded)
    static std::mutex mtx;

    // Private constructor to prevent direct instantiation
    Singleton() {
        std::cout << "Singleton instance created.\n";
    }

    // Delete copy constructor and assignment operator to prevent copying
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // Static method to access the single instance
    static Singleton* getInstance() {
        // Double-checked locking for thread safety
        if (instance == nullptr) {
            // Lock the mutex only if the instance is not created yet
            // This avoids locking overhead after the instance is created
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }

    // Example method
    void showMessage() {
        std::cout << "Hello from the Singleton!\n";
    }
};

// Initialize static members
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;

// Example usage
int main() {
    // Get the singleton instance and call a method
    Singleton* s1 = Singleton::getInstance();
    s1->showMessage();

    // Get the singleton instance again (should be the same instance)
    Singleton* s2 = Singleton::getInstance();
    if (s1 == s2) {
        std::cout << "Both pointers point to the same Singleton instance.\n";
    } else {
        std::cout << "Different instances (should not happen).\n";
    }

    return 0;
}