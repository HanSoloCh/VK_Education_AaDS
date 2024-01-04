/*
Реализовать очередь с динамическим зацикленным буфером. Обрабатывать команды push back и pop front.
 */
#include <iostream>

class Queue {
   private:
    int *array;
    int head;
    int tail;
    int size;
    int capacity;

    bool IsFull() const;

   public:
    Queue() : array(nullptr), head(0), tail(0), size(0), capacity(0) {}

    ~Queue() { delete[] array; }

    Queue(const Queue &other) = delete;             // Конструктор копирования
    Queue &operator=(const Queue &other) = delete;  // оператор присвоения

    void Enqueue(int data);
    int Dequeue();
    bool IsEmpty() const;
};

bool Queue::IsFull() const { return capacity == size; }

void Queue::Enqueue(int data) {
    if (IsFull()) {
        int new_capacity = capacity == 0 ? 1 : capacity * 2;
        int *new_array = new int[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_array[i] = array[(head + i) % capacity];
        }
        delete[] array;
        array = new_array;
        head = 0;
        tail = size;
        capacity = new_capacity;
    }
    array[tail] = data;
    tail = (tail + 1) % capacity;
    size++;
}

int Queue::Dequeue() {
    if (IsEmpty()) return -1;
    int data = array[head];
    head = (head + 1) % capacity;
    size--;
    if (IsEmpty()) {
        head = tail = 0;
    }
    return data;
}

bool Queue::IsEmpty() const { return size == 0; }

int main() {
    Queue queue;
    size_t n = 0;
    std::cin >> n;
    bool flag = true;
    for (size_t i = 0; i != n; ++i) {
        int command = 0, num = 0;
        std::cin >> command >> num;
        if (command == 3) {
            queue.Enqueue(num);
        } else if (command == 2) {
            int tmp_data = queue.Dequeue();
            if (tmp_data != num) flag = false;
        }
    }
    if (flag)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}
