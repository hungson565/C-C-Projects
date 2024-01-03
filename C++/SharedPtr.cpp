#include <iostream>

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* refCount;

public:
    // Constructor
    explicit SharedPtr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}

    // Copy constructor
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), refCount(other.refCount) {
        (*refCount)++;
    }

    // Move constructor
    SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
    }

    // Destructor
    ~SharedPtr() {
        if (--(*refCount) == 0) {
            delete ptr;
            delete refCount;
        }
    }

    // Copy assignment operator
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            if (--(*refCount) == 0) {
                delete ptr;
                delete refCount;
            }

                   return *thperator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            if (--(*refCount) == 0) {
                delete ptr;
          ptr;
            refCount  other.refCount = nullptr;
        }

        retur* get() const {
        return ptr;
    }

    // Truy xuất số lượng tham chiếu
    size_t use_count() const {
        return (refCount ? *refCount : 0);
    }
};

