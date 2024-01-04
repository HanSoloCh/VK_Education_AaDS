/*
 * Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.

Требования:

    Время работы O(N * logK)
        Куча должна быть реализована в виде шаблонного класса.
    Решение должно поддерживать передачу функции сравнения снаружи.
    Куча должна быть динамической.
    Формат ввода
    Сначала вводится количество массивов K.
        . Затем по очереди размер каждого массива и элементы массива.
    Каждый массив упорядочен по возрастанию.

    Формат вывода
    Итоговый отсортированный массив.
 */

#include <iostream>

struct arr_t {
    int *arr;
    size_t cur_ind;
    size_t size;

    arr_t() : arr(nullptr), cur_ind(0), size(0) {}

    explicit arr_t(size_t n_size) : size(n_size), cur_ind(0) { arr = new int[size]; }
    ~arr_t() { delete[] arr; }
    // Конструктор копирования
    arr_t(const arr_t &other) : cur_ind(other.cur_ind), size(other.size) {
        arr = new int[size];
        for (size_t i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    // Оператор присвоения
    arr_t &operator=(const arr_t &other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            cur_ind = other.cur_ind;
            arr = new int[size];
            for (size_t i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    bool operator()(const arr_t &l, const arr_t &r) { return l.arr[l.cur_ind] < r.arr[r.cur_ind]; }
};

template <typename T, typename Comparator = std::less<T>>
class Heap {
   private:
    T *heap;
    size_t size;

    void SiftDown(size_t i, Comparator cmp = Comparator());

    void SiftUp(size_t i, Comparator cmp = Comparator());

   public:
    explicit Heap(size_t n_size) : size(0) { heap = new T[n_size]; }
    ~Heap() { delete[] heap; }
    Heap(const Heap &other) = delete;             // Конструктор копирования
    Heap &operator=(const Heap &other) = delete;  // Оператор присвоения

    T PopTop();
    void AddEl(T &data);
    [[nodiscard]] bool IsEmpty() const { return size == 0; }
};

template <typename T>
void swap(T &l, T &r) {
    T tmp = l;
    l = r;
    r = tmp;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::SiftDown(size_t i, Comparator cmp) {
    while (2 * i + 1 < size) {
        size_t left_ind = 2 * i + 1;
        size_t right_ind = 2 * i + 2;
        size_t j = left_ind;
        if (right_ind < size and cmp(heap[right_ind], heap[left_ind])) j = right_ind;
        if (cmp(heap[i], heap[j])) break;
        swap(heap[i], heap[j]);
        i = j;
    }
}

template <typename T, typename Comparator>
T Heap<T, Comparator>::PopTop() {
    T data = heap[0];
    heap[0] = heap[size - 1];
    size--;
    SiftDown(0);
    return data;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::AddEl(T &data) {
    heap[size] = data;
    size++;
    SiftUp(size - 1);
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::SiftUp(size_t i, Comparator cmp) {
    while (cmp(heap[i], heap[(static_cast<int>(i) - 1) / 2])) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main() {
    size_t k = 0;
    std::cin >> k;
    Heap<arr_t, arr_t> arr_heap(k);

    for (size_t i = 0; i < k; ++i) {
        size_t size = 0;
        std::cin >> size;
        arr_t arr(size);
        for (size_t j = 0; j < size; ++j) {
            std::cin >> arr.arr[j];
        }
        arr_heap.AddEl(arr);
    }

    while (!arr_heap.IsEmpty()) {
        arr_t tmp_arr = arr_heap.PopTop();
        std::cout << tmp_arr.arr[tmp_arr.cur_ind++] << " ";
        if (tmp_arr.cur_ind < tmp_arr.size) arr_heap.AddEl(tmp_arr);
    }
    return 0;
}