# Red-Black Trees
[![CMake](https://github.com/Algorithms-and-Data-Structures-2021/semester-work-template/actions/workflows/cmake.yml/badge.svg)](https://github.com/Algorithms-and-Data-Structures-2021/semester-work-red-black-tree/actions/workflows/cmake.yml)

Красно-черное дерево   - это
один из видов самобалансирующихся двоичных деревьев поиска, гарантирующих логарифмический рост высоты дерева от числа узлов и позволяющее быстро выполнять основные операции дерева поиска: добавление, удаление и поиск узла. Сбалансированность достигается за счёт введения дополнительного атрибута узла дерева — «цвета». Этот атрибут может принимать одно из двух возможных значений — «чёрный» или «красный».

##### Сложность ключевых операций структуры данных

| Операция   |Время выполнения |
| :---       |  ---:           |
| Insert     |   _O(log n)_    |
| Search     |   _O(log n)_    |
| Delete     |   _O(log n)_    |

## 2STARS

| Фамилия Имя   | Вклад (%) | Прозвище              |
| :---          |   ---:    |  ---:                 |
| Зеленков Данила   | 50        |  _главный_               |
|  Наумова Алёна  | 50       |  _босс_ |


## Структура проекта

_Описание основных частей семестрового проекта._

Проект состоит из следующих частей:

- [`src`](src)/[`include`](include) - реализация структуры данных (исходный код и заголовочные файлы);
- [`example`](example)  пример использования структуры данных
- [`benchmark`](benchmark) - контрольные тесты производительности структуры данных (операции добавления, удаления,
  поиска и пр.);
- [`dataset`](dataset) - наборы данных для запуска контрольных тестов и их генерация;

## Требования (Prerequisites)

Рекомендуемые требования:

1. С++ компилятор c поддержкой стандарта C++17 (например, _GNU GCC 8.1.x_ и выше).
2. Система автоматизации сборки _CMake_ (версия _3.12.x_ и выше).
3. Рекомендуемый объем оперативной памяти - не менее 6 ГБ.
4. Свободное дисковое пространство объемом ~ 4 ГБ (набор данных для контрольных тестов).

## Сборка и запуск

#### Сборка проекта

Склонируйте проект к себе на устройство через [Git for Windows](https://gitforwindows.org/) (либо используйте
возможности IDE):

```shell
git clone https://github.com/Algorithms-and-Data-Structures-2021/semester-work-red-black-tree.git
```

В папке example лежат примеры использования  структуры данных
#### Генерация тестовых данных

Для генерации чисел мы использовали ГПСЧ (генератор псевдослучайных чисел), а именно mersenne twister, (mt19937). Генерирует случайное число он довольно быстро. Определен он в хедере random и пространстве имён std. Является 32-битным генератором.


Генерация тестового набора данных в
формате [comma-seperated values (CSV)](https://en.wikipedia.org/wiki/Comma-separated_values):

```shell
# переход в папку генерации набора данных
cd dataset

```

По названию директории `/dataset/data/add` можно понять, что здесь хранятся наборы данных для контрольных тестов по
**добавлению** элементов в структуру данных. Названия файлов `100.csv`. `5000000.csv` и т.д. хранят информацию о размере набора данных (т.е. количество элементов).

[Ccылка](https://drive.google.com/drive/folders/1wN5Jd6pJpwWmZtIvVD4vEwsHWB1uzs9u?usp=sharing)
 на тестовые наборы

#### Контрольные тесты (benchmarks)

В [`benchmark`](benchmark)/[`Benchmark.cpp`](benchmark/Benchmark.cpp) реализовано одновременное тестирование всех ключевых методов
по всем контрольным тестам. Если Вы хотите протестировать лишь один из
методов, то закомментируйте тестирование остальных методов.

##### Список контрольных тестов

| Название                  | Описание                                | Метрики         |
| :---                      | ---                                     | :---            |
| `Benchmark` | insert/search/delete   | _время_         |

## Источники
[графическая визуализация RBTree](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

[Wikipedia](https://en.wikipedia.org/wiki/Red–black_tree)

[Коротко и ясно про RBTree](https://habr.com/ru/post/330644/)

[Введение в RBTree с последующей реализацией](http://espressocode.top/red-black-tree-set-1-introduction-2/)
