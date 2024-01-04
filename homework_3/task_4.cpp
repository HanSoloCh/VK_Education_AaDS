/*
 * Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду: [ 1 2 3 4 ] [
 * 5 6 7 8 ] [ 9 10 11 12] [ 13 14 15 0 ], где 0 задает пустую ячейку. Достаточно найти хотя бы какое-то
 * решение. Число перемещений костяшек не обязано быть минимальным.
 */

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <set>
#include <unordered_map>

const char field_size = 16;
const std::array<char, field_size> finish_state = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

class Game {
   private:
    std::array<char, field_size> field;
    char empty_poz;
    size_t astar_stat;
    size_t shortest_way;

    [[nodiscard]] size_t GetInvCount() const {
        size_t inv_count = 0;
        for (int i = 0; i < field_size - 1; i++) {
            for (int j = i + 1; j < field_size; j++) {
                if (field[i] > field[j] && field[i] && field[j]) inv_count++;
            }
        }
        return inv_count;
    }

    // Считаем, как расстояние до нужной позиции
    void CalcAstarStat() {
        astar_stat = 0;
        for (int index = 0; index < field_size; index++) {
            if (field[index] != 0) {
                astar_stat += abs(index + 1 - field[index]);
            }
        }
    }

    friend class GameHasher;

    friend class Comparator;

    friend std::string GetSolution(const std::array<char, field_size> &field);

   public:
    explicit Game(const std::array<char, field_size> &field) : field(field), shortest_way(0), astar_stat(0) {
        empty_poz = -1;
        for (char i = 0; i < field_size; ++i) {
            if (field[i] == 0) empty_poz = i;
        }
        assert(empty_poz != -1);
    }

    [[nodiscard]] bool IsComplete() const { return field == finish_state && empty_poz == field_size - 1; }

    [[nodiscard]] bool IsSolvable() const { return (GetInvCount() + empty_poz / 4 + 1) % 2 == 0; }

    [[nodiscard]] bool CanMoveLeft() const { return empty_poz % 4 != 3; }

    [[nodiscard]] bool CanMoveRight() const { return empty_poz % 4 != 0; }

    [[nodiscard]] bool CanMoveUp() const { return empty_poz < 12; }

    [[nodiscard]] bool CanMoveDown() const { return empty_poz > 3; }

    [[nodiscard]] Game MoveLeft() const {
        assert(CanMoveLeft());
        Game new_state(*this);
        std::swap(new_state.field[empty_poz], new_state.field[empty_poz + 1]);
        new_state.empty_poz++;
        new_state.CalcAstarStat();
        return new_state;
    }

    [[nodiscard]] Game MoveRight() const {
        assert(CanMoveRight());
        Game new_state(*this);
        std::swap(new_state.field[empty_poz], new_state.field[empty_poz - 1]);
        new_state.empty_poz--;
        new_state.CalcAstarStat();
        return new_state;
    }

    [[nodiscard]] Game MoveUp() const {
        assert(CanMoveUp());
        Game new_state(*this);
        std::swap(new_state.field[empty_poz], new_state.field[empty_poz + 4]);
        new_state.empty_poz += 4;
        new_state.CalcAstarStat();
        return new_state;
    }

    [[nodiscard]] Game MoveDown() const {
        assert(CanMoveDown());
        Game new_state(*this);
        std::swap(new_state.field[empty_poz], new_state.field[empty_poz - 4]);
        new_state.empty_poz -= 4;
        new_state.CalcAstarStat();
        return new_state;
    }

    bool operator==(const Game &other) const { return field == other.field; }
};

class GameHasher {
   public:
    size_t operator()(const Game &state) const {
        size_t index = 0, pow = 1, hash = 0;
        while (index != 16) {
            hash += state.field[index] * pow;
            pow *= 16;
            index++;
        }
        return hash;
    }
};

class Comparator {
   public:
    bool operator()(const Game &state_1, const Game &state_2) const {
        if (state_1.astar_stat == state_2.astar_stat) {
            return state_1.shortest_way < state_2.shortest_way;
        } else {
            return state_1.astar_stat < state_2.astar_stat;
        }
    }
};

std::string GetSolution(const std::array<char, field_size> &field) {
    Game start_state(field);
    start_state.CalcAstarStat();
    if (!start_state.IsSolvable()) return "-1";

    std::unordered_map<Game, char, GameHasher> visited;
    visited[start_state] = 'S';

    std::set<Game, Comparator> queue;

    queue.insert(start_state);

    while (true) {
        Game cur_state = *queue.begin();
        queue.erase(queue.begin());

        if (cur_state.IsComplete()) break;

        if (cur_state.CanMoveLeft()) {
            Game new_state = cur_state.MoveLeft();
            if (visited.find(new_state) == visited.end()) {
                visited[new_state] = 'L';
                new_state.shortest_way = cur_state.shortest_way + 1;
                queue.insert(new_state);
            } else if (new_state.shortest_way > cur_state.shortest_way + 1) {
                queue.erase(visited.find(new_state)->first);
                new_state.shortest_way = cur_state.shortest_way + 1;
                queue.insert(new_state);
            }
        }

        if (cur_state.CanMoveRight()) {
            Game new_state = cur_state.MoveRight();
            if (visited.find(new_state) == visited.end()) {
                visited[new_state] = 'R';
                new_state.shortest_way = cur_state.shortest_way + 1;
                queue.insert(new_state);
            } else if (new_state.shortest_way > cur_state.shortest_way + 1) {
                queue.erase(visited.find(new_state)->first);
                new_state.shortest_way = cur_state.shortest_way + 1;
                queue.insert(new_state);
            }
        }

        if (cur_state.CanMoveUp()) {
            Game new_state = cur_state.MoveUp();
            if (visited.find(new_state) == visited.end()) {
                visited[new_state] = 'U';
                new_state.shortest_way = cur_state.shortest_way + 1;
                queue.insert(new_state);
            } else if (new_state.shortest_way > cur_state.shortest_way + 1) {
                queue.erase(visited.find(new_state)->first);
                new_state.shortest_way = cur_state.shortest_way + 1;
                queue.insert(new_state);
            }
        }

        if (cur_state.CanMoveDown()) {
            Game new_state = cur_state.MoveDown();
            if (visited.find(new_state) == visited.end()) {
                visited[new_state] = 'D';
                new_state.shortest_way = cur_state.shortest_way + 1;
                queue.insert(new_state);
            } else if (new_state.shortest_way > cur_state.shortest_way + 1) {
                queue.erase(visited.find(new_state)->first);
                new_state.shortest_way = cur_state.shortest_way + 1;
                queue.insert(new_state);
            }
        }
    }

    std::string path;
    Game state(finish_state);
    while (visited[state] != 'S') {
        char move = visited[state];
        switch (move) {
            case 'L':
                state = state.MoveRight();
                break;
            case 'R':
                state = state.MoveLeft();
                break;
            case 'U':
                state = state.MoveDown();
                break;
            case 'D':
                state = state.MoveUp();
                break;
            default:
                assert(false);
        }
        path += move;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    std::array<char, field_size> start_field{};
    for (size_t i = 0; i < field_size; ++i) {
        int elem = 0;
        std::cin >> elem;
        start_field[i] = static_cast<char>(elem);
    }

    std::string solution = GetSolution(start_field);
    if (solution == "-1") {
        std::cout << "-1";
    } else {
        std::cout << solution.length() << std::endl;
        for (auto way : solution) {
            std::cout << way;
        }
    }
    return 0;
}
