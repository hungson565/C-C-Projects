template <typename Key, typename Value>
class MyMap {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Hàm hỗ trợ cho việc chèn phần tử vào cây
    Node* insert(Node* node, const Key& key, const Value& value) {
        if (node == nullptr) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            // Key đã tồn tại, cập nhật giá trị
            node->value = value;
        }

        return node;
    }

    // Hàm hỗ trợ cho việc tìm kiếm phần tử trong cây
    Value* find(Node* node, const Key& key) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            return find(node->left, key);
        } else if (key > node->key) {
            return find(node->right, key);
        } else {
            // Key đã tồn tại, trả về giá trị
            return &node->value;
        }
    }

public:
    // Constructor
    MyMap() : root(nullptr) {}

    // Hàm chèn phần tử vào map
    void insert(const Key& key, const Value& value) {
        root = insert(root, key, value);
    }

    // Hàm tìm kiếm giá trị theo key
    Value* find(const Key& key) const {
        return find(root, key);
    }
};