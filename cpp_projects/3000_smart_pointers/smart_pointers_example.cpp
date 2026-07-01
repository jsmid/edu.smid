/*
Smart Pointers in C++11
=======================
Smart pointers are RAII wrappers around dynamically allocated objects.
They manage object lifetime automatically and reduce memory bugs.

Main tools:
- std::unique_ptr : exclusive ownership
- std::shared_ptr : shared ownership (reference counted)
- std::weak_ptr   : non-owning observer of shared_ptr-managed objects
*/

#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;

void section(const char* title) {
    cout << "\n=== " << title << " ===\n";
}

class Widget {
public:
    explicit Widget(int id_) : id(id_) {
        cout << "Widget " << id << " constructed\n";
    }

    ~Widget() {
        cout << "Widget " << id << " destroyed\n";
    }

    void hello() const {
        cout << "Hello from Widget " << id << "\n";
    }

private:
    int id;
};

int main() {
    section("1) unique_ptr: single owner");

    // C++11 supports unique_ptr and move semantics.
    // Use std::make_unique in real code (C++14) to avoid manual new/delete.
    std::unique_ptr<Widget> owner1(new Widget(1));
    owner1->hello();

    // Transfer ownership with std::move.
    // After the move, owner1 is null and owner2 owns the Widget.
    std::unique_ptr<Widget> owner2 = std::move(owner1);
    cout << "owner1 is " << (owner1 ? "not null" : "null after move") << "\n";
    owner2->hello();

    section("2) unique_ptr in containers");

    // unique_ptr can be stored in containers, but they cannot be copied.
    std::vector<std::unique_ptr<Widget> > store;
    store.push_back(std::unique_ptr<Widget>(new Widget(2)));
    store.push_back(std::unique_ptr<Widget>(new Widget(3)));

    for (std::size_t i = 0; i < store.size(); ++i) {
        store[i]->hello();
    }

    section("3) shared_ptr: shared ownership");

    // Prefer make_shared in real code (single allocation for object+control block).
    // shared_ptr can be copied, and it keeps track of how many owners exist.
    // When the last shared_ptr is destroyed, the object is deleted automatically.
    // Note: shared_ptr is heavier than unique_ptr due to reference counting.
    std::shared_ptr<Widget> shared1 = std::make_shared<Widget>(10);
    cout << "shared1 use_count = " << shared1.use_count() << "\n";

    {
        // Create additional shared_ptr instances sharing ownership of the same Widget.
        // Each copy increments the reference count.
        // When they go out of scope, the count decrements.
        // When the count reaches zero, the Widget is destroyed.
        std::shared_ptr<Widget> shared2 = shared1;
        std::shared_ptr<Widget> shared3 = shared1;
        cout << "inside scope use_count = " << shared1.use_count() << "\n";
        shared2->hello();
        shared3->hello();
    }

    cout << "after scope use_count = " << shared1.use_count() << "\n";

    section("4) weak_ptr: observe without owning");

    // weak_ptr does not affect the reference count of shared_ptr.
    // It can be used to break cycles or to observe an object without extending its lifetime.
    // Use lock() to get a shared_ptr if the object is still alive.
    // weak_ptr is useful for caches, observers, and breaking circular references.
    // Note: weak_ptr is not copyable from unique_ptr, only from shared_ptr.
    std::weak_ptr<Widget> observer = shared1;
    cout << "observer expired? " << (observer.expired() ? "yes" : "no") << "\n";

    if (std::shared_ptr<Widget> locked = observer.lock()) {
        cout << "lock() succeeded, use_count = " << locked.use_count() << "\n";
        locked->hello();
    }

    // Drop last shared owner.
    // After this, the Widget will be destroyed, and observer will expire.
    shared1.reset();
    cout << "after reset, observer expired? " << (observer.expired() ? "yes" : "no") << "\n";

    // Attempt to lock the weak_ptr after the object has been destroyed.
    // This will return a null shared_ptr, indicating the object is gone.
    // Note: lock() is safe and does not throw; it returns an empty shared_ptr if the object is gone.
    if (!observer.lock()) {
        cout << "lock() now fails safely (object already destroyed)\n";
    }

    section("5) Typical guidance");
    cout << "Use unique_ptr by default.\n";
    cout << "Use shared_ptr only for real shared ownership.\n";
    cout << "Use weak_ptr to break cycles and avoid extending lifetime.\n";

    return 0;
}