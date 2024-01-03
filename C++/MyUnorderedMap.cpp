template <typename Key, typename Value, typename Hash = std::hash<Key>>
class MyUnorderedMap {
private:
    // Cặp key-value
    struct KeyValuePair {
        Key key;
        Value value;
        KeyValuePair(const Key& k, const Value& v) : key(k), value(v) {}
    };

    // Danh sách liên kết để giải quyết xung đột
    using Bucket = std::list<KeyValuePair>;

    // Mảng các danh sách liên kết (bảng băm)
    std::vector<Bucket> buckets;

    // Hàm băm để chuyển key thành index trong bảng băm
    size_t hashFunction(const Key& key) const {
        Hash hash;
        return hash(key) % buckets.size();
    }

    // Hàm hỗ trợ để tìm kiếm key trong một bucket
    typename Bucket::iterator findInBucket(Bucket& bucket, const Key& key) {
        return std::find_if(bucket.begin(), bucket.end(),
                            [&key](const KeyValuePair& kvp) { return kvp.key == key; });
    }

public:
    // Constructor
    MyUnorderedMap(size_t size = 10) : buckets(size) {}

    // Hàm chèn phần tử vào unordered_map
    void insert(const Key& key, const Value& value) {
        size_t index = hashFunction(key);
        Bucket& bucket = buckets[index];

        // Kiểm tra xem key đã tồn tại chưa
        auto it = findInBucket(bucket, key);
        if (it != bucket.end()) {
            // Key đã tồn tại, cập nhật giá trị
            it->value = value;
        } else {
            // Key chưa tồn tại, thêm mới vào bucket
            bucket.push_back(KeyValuePair(key, value));
        }
    }

    // Hàm tìm kiếm giá trị theo key
    Value* find(const Key& key) {
        size_t index = hashFunction(key);
        Bucket& bucket = buckets[index];

        // Kiểm tra xem key có trong bucket không
        auto it = findInBucket(bucket, key);
        if (it != bucket.end()) {
            return &it->value;
        } else {
            return nullptr;
        }
    }
};