# Модуль №1

[___Заадание №1___](https://github.com/HanSoloCh/VK_Education_AaDS/blob/main/homework_3/task_1)<br>

Дан базовый интерфейс для представления ориентированного графа:
```cpp
struct IGraph {
virtual ~IGraph() {}
	
	// Добавление ребра от from к to.
virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};
```

Необходимо написать несколько реализаций интерфейса:
 - ListGraph, хранящий граф в виде массива списков смежности,
 - MatrixGraph, хранящий граф в виде матрицы смежности,
 - SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
 - ArcGraph, хранящий граф в виде одного массива пар {from, to}.
<br>Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект. Для каждого класса создавайте отдельные h и cpp файлы. Число вершин графа задается в конструкторе каждой реализации.


[___Заадание №2___](https://github.com/HanSoloCh/VK_Education_AaDS/blob/main/homework_3/task_2.cpp)<br>

Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

[___Заадание №3___](https://github.com/HanSoloCh/VK_Education_AaDS/blob/main/homework_3/task_3.cpp)<br>

Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.

Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.

[___Заадание №4___](https://github.com/HanSoloCh/VK_Education_AaDS/blob/main/homework_3/task_4.cpp)<br>

Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду: [ 1 2 3 4 ] [ 5 6 7 8 ] [ 9 10 11 12] [ 13 14 15 0 ], где 0 задает пустую ячейку. Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.

