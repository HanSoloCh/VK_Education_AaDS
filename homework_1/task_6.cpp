/*
 * 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте
 * методом прохода двумя итераторами от начала массива к концу.
 */

#include <iostream>

template <typename T, typename Comparator = std::less<T>>
int partition(T *arr, int l, int r, Comparator cmp = Comparator()) {
    if (r == l) return r;
    int pivot_ind = l + rand() % (r - l);
    std::swap(arr[r - 1], arr[pivot_ind]);

    int i = l - 1;
    int j = l;

    T pivot = arr[r - 1];  // Опорный элемент

    // Проходим по элементам массива от начала к концу
    while (j < r - 1) {
        if (cmp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
        j++;
    }

    std::swap(arr[i + 1], arr[r - 1]);
    return i + 1;
}

template <typename T, typename Comparator = std::less<T>>
T kth_statistic(T *arr, int k, int l, int r, Comparator cmp = Comparator()) {
    while (l < r) {
        int pivot_pos = partition(arr, l, r, cmp);

        if (pivot_pos == k) {
            return arr[pivot_pos];
        }
        if (pivot_pos > k) {
            r = pivot_pos;
        } else {
            l = pivot_pos + 1;
        }
    }

    return arr[l];
}

int main() {
    int n = 0;
    std::cin >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int k1 = n / 10;
    int k2 = n / 2;
    int k3 = n * 9 / 10;

    int percentile_10 = kth_statistic(arr, k1, 0, n);
    int median = kth_statistic(arr, k2, 0, n);
    int percentile_90 = kth_statistic(arr, k3, 0, n);

    std::cout << percentile_10 << std::endl;
    std::cout << median << std::endl;
    std::cout << percentile_90 << std::endl;

    delete[] arr;
    return 0;
}
