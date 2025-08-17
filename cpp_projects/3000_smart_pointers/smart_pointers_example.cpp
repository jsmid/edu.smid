/*
    Smart Pointers Example in C++

    Purpose:
    Smart pointers, introduced in C++11, help manage dynamic memory automatically and safely.
    They prevent memory leaks and dangling pointers by ensuring that memory is released when it is no longer needed.
    The most common smart pointers are std::unique_ptr, std::shared_ptr, and std::weak_ptr.

    This example demonstrates how to use unique_ptr and shared_ptr to manage objects.
*/

#include <iostream>
#include <memory>

class Widget {
public:
    Widget(int id) : id(id) {
        std::cout << "Widget " << id << " constructed.\n";
    }
    ~Widget() {
        std::cout << "Widget " << id << " destroyed.\n";
    }
    void greet() const {
        std::cout << "Hello from Widget " << id << "!\n";
    }
private:
    int id;
};

int main() {
    // Unique pointer: sole ownership, automatically deletes the object
    std::unique_ptr<Widget> uptr(new Widget(1));
    uptr->greet();

    // Transfer ownership with std::move
    std::cout << "Transferring ownership of Widget 1 to uptr2.\n";
    std::unique_ptr<Widget> uptr2 = std::move(uptr);
    if (!uptr) {
        std::cout << "uptr is now empty after move.\n";
    }
    uptr2->greet();

    // Shared pointer: shared ownership, deletes object when last owner goes out of scope
    // sptr1 and sptr2 share ownership of the same Widget object
    // Use make_shared for better performance and safety
    // std::shared_ptr<Widget> sptr1 = std::make_shared<Widget>(2);
    // This is equivalent to the line below, but using make_shared is preferred
    // 
    // It allocates memory for the object and the control block in a single allocation.
    // This reduces memory fragmentation and improves cache locality.
    // It also avoids the overhead of an additional allocation for the control block.
    std::shared_ptr<Widget> sptr1(new Widget(2));
    {
        std::cout << "Creating shared_ptr sptr2 from sptr1.\n";
        // sptr2 is a copy of sptr1, sharing ownership of the Widget object
        // 
        // Both sptr1 and sptr2 now share ownership of the Widget object
        std::shared_ptr<Widget> sptr2 = sptr1; // Both share ownership
        // The use_count of the shared pointer increases to 2
        // This means that there are two shared pointers managing the same Widget object.
        // When both sptr1 and sptr2 go out of scope, the Widget object will be destroyed.
        // This is a common pattern in C++ to manage shared ownership of dynamically allocated objects.
        // Using shared_ptr ensures that the Widget object is deleted automatically when the last shared_ptr goes out of scope.
        // This prevents memory leaks and dangling pointers.
        std::cout << "sptr1 use_count: " << sptr1.use_count() << "\n";
        std::cout << "sptr2 use_count: " << sptr2.use_count() << "\n";
        sptr2->greet();
    } // sptr2 goes out of scope, but object is not deleted yet

    std::cout << "sptr1 use_count after sptr2 is out of scope: " << sptr1.use_count() << "\n";
    sptr1->greet();

    // Weak pointer: non-owning reference to a shared_ptr-managed object
    // It does not affect the reference count of the shared_ptr
    // This is useful to avoid circular references that can lead to memory leaks.
    // A weak_ptr can be converted to a shared_ptr using lock(), which returns a shared_ptr if the object is still alive.
    std::cout << "Creating weak_ptr wptr from sptr1.\n";
    // wptr is a weak reference to the Widget object managed by sptr1
    // It does not increase the reference count of sptr1.
    // If sptr1 is destroyed, wptr will no longer be valid.
    // This is useful for caching or observer patterns where you want to avoid ownership.
    //
    // A weak_ptr can be used to check if the object is still alive without affecting its lifetime.
    // If the object is destroyed, the weak_ptr becomes expired and cannot be locked.
    // This prevents dangling pointers and allows safe access to the object if it still exists.
    std::weak_ptr<Widget> wptr = sptr1;
    if (auto locked = wptr.lock()) {
        std::cout << "Locked weak_ptr, use_count: " << locked.use_count() << "\n";
        locked->greet();
    } else {
        std::cout << "Widget already destroyed.\n";
    }

    // When sptr1 goes out of scope, Widget 2 is destroyed automatically

    return 0;
}