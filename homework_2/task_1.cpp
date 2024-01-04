/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой
адресацией. Хранимые строки непустые и состоят из строчных латинских букв. Хеш-функция строки должна быть
реализована с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть
равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения
таблицы достигает 3/4. Структура данных должна поддерживать операции добавления строки в множество, удаления
строки из множества и проверки принадлежности данной строки множеству.

Вариант 2. Для разрешения коллизий используйте двойное хеширование.
*/

#include <iostream>
#include <utility>
#include <vector>

const size_t kDefaultSize = 8;
const float kMaxAlpha = 0.75;

enum Status {
    KEY,
    DELL,
    NIL,
};

template <typename T>
struct HashTableBlock {
    explicit HashTableBlock(T initial_data) : data(std::move(initial_data)), status(KEY) {}
    HashTableBlock() : status(NIL) {}
    T data;
    Status status;
};

class StringHasher {
   public:
    explicit StringHasher(size_t prime = 11) : prime(prime){};

    size_t operator()(const std::string &str) const;

   private:
    size_t prime;
};

size_t StringHasher::operator()(const std::string &str) const {
    size_t hash = 0;
    for (char i : str) {
        hash = hash * prime + i;
    }
    return hash;
}

template <typename T, typename Hasher>
class HashTable {
   public:
    explicit HashTable(size_t initial_size = kDefaultSize, Hasher first_hasher = Hasher(),
                       Hasher second_hasher = Hasher(71))
        : size(0), table(initial_size), hasher(first_hasher), hasher_2(second_hasher){};
    ~HashTable() = default;
    bool Add(const T &key);
    bool Remove(const T &key);
    bool IsInTable(const T &key);

   private:
    void Grow();
    std::vector<HashTableBlock<T>> table;
    size_t size;
    Hasher hasher;
    Hasher hasher_2;
};

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T &key) {
    if (size > kMaxAlpha * table.size()) {
        Grow();
    }
    size_t index_for_insert = 0;
    for (size_t count_steps = 0; count_steps < table.size(); ++count_steps) {
        size_t hash = (hasher(key) + count_steps * (2 * hasher_2(key) + 1)) % table.size();
        if (table[hash].status == KEY && table[hash].data == key) return false;

        if (table[hash].status == DELL) index_for_insert = hash;

        if (table[hash].status == NIL) {
            table[hash] = HashTableBlock<T>(key);
            size++;
            return true;
        }
    }
    table[index_for_insert] = HashTableBlock<T>(key);
    size++;
    return true;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Remove(const T &key) {
    for (size_t count_steps = 0; count_steps < table.size(); ++count_steps) {
        size_t hash = (hasher(key) + count_steps * (2 * hasher_2(key) + 1)) % table.size();

        if (table[hash].status == KEY && table[hash].data == key) {
            table[hash].status = DELL;
            size--;
            return true;
        }
        if (table[hash].status == NIL) return false;
    }
    return false;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::IsInTable(const T &key) {
    for (size_t count_steps = 0; count_steps < table.size(); ++count_steps) {
        size_t hash = (hasher(key) + count_steps * (2 * hasher_2(key) + 1)) % table.size();

        if (table[hash].status == KEY && table[hash].data == key) return true;

        if (table[hash].status == NIL) return false;
    }
    return false;
}

template <typename T, typename Hasher>
void HashTable<T, Hasher>::Grow() {
    std::vector<HashTableBlock<T>> new_table(table.size() * 2);
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i].status == KEY) {
            size_t step = 0;
            size_t new_hash =
                (hasher(table[i].data) + step * (2 * hasher_2(table[i].data) + 1)) % new_table.size();
            while (new_table[new_hash].status == KEY) {
                step++;
                new_hash =
                    (hasher(table[i].data) + step * (2 * hasher_2(table[i].data) + 1)) % new_table.size();
            }
            new_table[new_hash] = table[i];
        }
    }
    table = std::move(new_table);
}

int main() {
    HashTable<std::string, StringHasher> table;
    char op;
    std::string key;

    while (std::cin >> op >> key) {
        switch (op) {
            case '?': {
                std::cout << (table.IsInTable(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '+': {
                std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-': {
                std::cout << (table.Remove(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            default: {
                return 0;
            }
        }
    }
    return 0;
}