/*
 * Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в
 * правое поддерево root; иначе в левое поддерево root. Требования: Рекурсия запрещена. Решение должно
 * поддерживать передачу функции сравнения снаружи.
 * Вариант 2_1. Выведите элементы в порядке in-order (слева направо).
 */

#include <iostream>
#include <stack>

template <typename T, typename Comparator = std::less<T>>
class BinaryTree {
    struct Node {
        Node(const T &data) : data(data), left(nullptr), right(nullptr) {}

        T data;
        Node *left;
        Node *right;
    };

   private:
    Node *root;
    void InOrderHelper(Node *node);

   public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {
        std::stack<Node *> stack_node;
        Node *cur_node = root;
        while (cur_node != nullptr || !stack_node.empty()) {
            // Кладем все левые узлы
            while (cur_node != nullptr) {
                stack_node.push(cur_node);
                cur_node = cur_node->left;
            }
            Node *node_for_delete = stack_node.top();
            stack_node.pop();
            cur_node = node_for_delete->right;
            delete node_for_delete;
        }
    }
    void Add(T add_data, Comparator cmp = Comparator());
    void Remove(T remove_data, Comparator cmp = Comparator());
    void InOrder();
};

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::Add(T add_data, Comparator cmp) {
    Node *prev_node = nullptr;
    Node *cur_node = root;
    while (cur_node != nullptr) {
        prev_node = cur_node;
        // Если не меньше, то в правое поддерево
        if (cmp(cur_node->data, add_data))
            cur_node = cur_node->right;
        else
            cur_node = cur_node->left;
    }

    if (prev_node == nullptr)
        root = new Node(add_data);
    else {
        struct Node *new_node = new Node(add_data);
        if (cmp(prev_node->data, add_data))
            prev_node->right = new_node;
        else
            prev_node->left = new_node;
    }
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::Remove(T remove_data, Comparator cmp) {}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::InOrder() {
    InOrderHelper(root);
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::InOrderHelper(Node *node) {
    std::stack<Node *> stack_node;
    Node *cur_node = node;
    while (cur_node != nullptr || !stack_node.empty()) {
        // Кладем все левые узлы
        while (cur_node != nullptr) {
            stack_node.push(cur_node);
            cur_node = cur_node->left;
        }
        // Печать головы
        Node *node_for_print = stack_node.top();
        stack_node.pop();
        std::cout << node_for_print->data << " ";
        // После головы переходим в правое дерево
        cur_node = node_for_print->right;
    }
}

int main() {
    BinaryTree<int> binary_tree;
    size_t n = 0;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        int data = 0;
        std::cin >> data;
        binary_tree.Add(data);
    }
    binary_tree.InOrder();
    return 0;
}