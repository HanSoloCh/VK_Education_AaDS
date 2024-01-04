/*
 * Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел, а также
 * запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A,
 * команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики
 * задается числом k. Требуемая скорость выполнения запроса - O(log n).
 */
#include <iostream>

template <typename T, typename Comparator = std::less<T>>
class AvlTree {
    struct Node {
        explicit Node(const T &data)
            : data(data), left(nullptr), right(nullptr), height(1), subtree_size(1) {}
        T data;
        Node *left;
        Node *right;
        size_t height;
        size_t subtree_size;
    };

   public:
    AvlTree() : root(nullptr) {}

    ~AvlTree() { DestroyTree(root); }

    void Add(const T &data) { root = AddInternal(root, data); }

    void Remove(const T &data) { root = RemoveInternal(root, data); }

    T FindKthStatistic(size_t k) { return FindKthStatisticInternal(root, k); }

    bool Has(const T &data) {
        Node *tmp = root;
        while (tmp) {
            if (tmp->data == data)
                return true;
            else if (tmp->data < data)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return false;
    }

   private:
    Node *root;

    T FindKthStatisticInternal(Node *node, size_t k) {
        size_t left_size = GetSubtreeSize(node->left);
        if (left_size == k) return node->data;

        if (k < left_size)
            return FindKthStatisticInternal(node->left, k);
        else
            return FindKthStatisticInternal(node->right, k - left_size - 1);
    }

    void FixParam(Node *node) {
        node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
        node->subtree_size = GetSubtreeSize(node->left) + GetSubtreeSize(node->right) + 1;
    }

    size_t GetSubtreeSize(Node *node) { return node ? node->subtree_size : 0; }

    size_t GetHeight(Node *node) { return node ? node->height : 0; }

    void DestroyTree(Node *node) {
        if (node) {
            DestroyTree(node->left);
            DestroyTree(node->right);
            delete node;
        }
    }

    Node *RemoveInternal(Node *node, const T &data, Comparator cmp = Comparator()) {
        if (node == nullptr) return nullptr;

        if (cmp(node->data, data))
            node->right = RemoveInternal(node->right, data);
        else if (cmp(data, node->data))
            node->left = RemoveInternal(node->left, data);
        else {
            Node *left = node->left;
            Node *right = node->right;

            delete node;

            if (!right) return left;

            Node *new_node = nullptr;
            if (GetHeight(right) > GetHeight(left)) {
                new_node = FindAndRemoveMin(right);
                new_node->left = left;
            } else {
                new_node = FindAndRemoveMax(left);
                new_node->right = right;
            }

            return DoBalance(new_node);
        }

        return DoBalance(node);
    }

    Node *FindAndRemoveMin(Node *node) {
        Node *min = node;
        while (min->left) min = min->left;
        min->right = RemoveMin(node);
        return min;
    }

    Node *RemoveMin(Node *node) {
        if (!node->left) return node->right;
        node->left = RemoveMin(node->left);
        return DoBalance(node);
    }

    Node *FindAndRemoveMax(Node *node) {
        Node *max = node;
        while (max->right) max = max->right;
        max->left = RemoveMax(node);
        return max;
    }

    Node *RemoveMax(Node *node) {
        if (!node->right) return node->left;
        node->right = RemoveMax(node->right);
        return DoBalance(node);
    }

    Node *AddInternal(Node *node, const T &data, Comparator cmp = Comparator()) {
        if (node == nullptr) return new Node(data);
        if (cmp(node->data, data))
            node->right = AddInternal(node->right, data);
        else
            node->left = AddInternal(node->left, data);

        return DoBalance(node);
    }

    int GetBalance(Node *node) { return GetHeight(node->right) - GetHeight(node->left); }

    Node *RotateLeft(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        FixParam(node);

        FixParam(tmp);

        return tmp;
    }

    Node *RotateRight(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        FixParam(node);

        FixParam(tmp);

        return tmp;
    }

    Node *DoBalance(Node *node) {
        FixParam(node);
        switch (GetBalance(node)) {
            // Виновато правое поддерево
            case 2:
                // Виновато правое-левое поддерево
                if (GetBalance(node->right) < 0) node->right = RotateRight(node->right);
                return RotateLeft(node);
            // Виновато левое поддерево
            case -2:
                // Виновато левое-правое поддерево
                if (GetBalance(node->left) > 0) node->left = RotateLeft(node->left);
                return RotateRight(node);
            default:
                return node;
        }
    }
};

int main() {
    AvlTree<int> avl_tree;
    size_t n = 0;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        int data = 0;
        size_t k = 0;
        std::cin >> data >> k;
        if (data > 0)
            avl_tree.Add(data);
        else
            avl_tree.Remove(-data);
        std::cout << avl_tree.FindKthStatistic(k) << "\n";
    }
    return 0;
}
