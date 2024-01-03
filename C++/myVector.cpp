template <typename T, typename Allocator = std::allocator<T>>
class MyVector {
private:
    T* elements;       // Mảng chứa các phần tử
    size_t size;        // Số lượng phần tử hiện tại
    size_t capacity;    // Dung lượng tối đa của mảng
    Allocator allocator; // Allocator cho phép tuỳ chỉnh cách quản lý bộ nhớ

public:
    // Constructor
    MyVector() : elements(nullptr), size(0), capacity(0) {}

    // Destructor
    ~MyVector() {
        clear();
        allocator.deallocate(elements, capacity);
    }

    // Thêm một phần tử vào cuối vector
    void push_back(const T& value) {
        if (size == capacity) {
            reserve((capacity == 0) ? 1 : capacity * 2);
        }
        elements[size++] = value;
    }

    // Xóa phần tử cuối cùng khỏi vector
    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    // Truy xuất phần tử tại vị trí index
    T& operator[](size_t index) {
        if (index < size) {
            return elements[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    // Trả về số lượng phần tử trong vector
    size_t size() const {
        return size;
    }

    // Trả về dung lượng hiện tại của vector
    size_t capacity() const {
        return capacity;
    }

    // Xóa tất cả phần tử khỏi vector
    void clear() {
        for (size_t i = 0; i < size; ++i) {
            allocator.destroy(elements + i);
        }
        size = 0;
    }

    // Tăng dung lượng của vector
    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            T* newElements = allocator.allocate(newCapacity);
            for (size_t i = 0; i < size; ++i) {
                allocator.construct(newElements + i, std::move(elements[i]));
                allocator.destroy(elements + i);
            }

            allocator.deallocate(elements, capacity);
            elements = newElements;
            capacity = newCapacity;
        }
    }

    // Iterator trỏ đến phần tử đầu tiên
    T* begin() const {
        return elements;
    }

    // Iterator trỏ đến phần tử sau phần tử cuối cùng
    T* end() const {
        return elements + size;
    }
};