/*
Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого
элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
Требования: Время работы поиска для каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i]
сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска,
а потом уже в нем делать бинарный поиск.
 */
#include <algorithm>
#include <iostream>

#define N_MAX 110000

int BinarySearch(const int *arr, int left, int right, int k) {
    int mid = 0;

    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] > k)
            right = mid - 1;
        else if (arr[mid] < k)
            left = mid + 1;
        else
            return mid;
    }
    if (right < 0)
        return 0;
    else if (abs(arr[left] - k) < abs(arr[right] - k))
        return left;
    else
        return right;
}

int ExpSearch(const int *arr, int n, int k) {
    int i = 1;
    while (i < n && arr[i] < k) {
        i *= 2;
    }
    return i;
}

int main() {
    int a[N_MAX];
    int n = 0, m = 0;
    std::cin >> n;
    for (int i = 0; i != n; ++i) std::cin >> a[i];
    std::cin >> m;

    for (int j = 0; j != m; ++j) {
        int b = 0;
        std::cin >> b;
        int i = ExpSearch(a, n, b);

        int left = i / 2;
        int right = std::min(i, n - 1);

        int result = BinarySearch(a, left, right, b);

        std::cout << result << " ";
    }
    return 0;
}
