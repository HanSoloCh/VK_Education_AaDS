#include <iostream>

/*
1.4 Инвертируйте значение бита в числе N по его номеру K.
Формат входных данных. Число N, номер бита K.
Формат выходных данных. Число с инвертированным битом в десятичном виде.
 */
int main() {
    unsigned n, k;
    std::cin >> n >> k;
    n = n ^ (1 << k);
    std::cout << n;
    return 0;
}
