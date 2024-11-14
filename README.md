# Анишкин кээш$$$
## Что он делает?
Вы можете использовать эту программу для построения LFU и PCA кэшей, посмотреть, как они меняются при добавлении элемента, узнать количество попаданий мои кэшэй, а так же увидеть график-сравнение попаданий.

## Какой принцип работы?
<ul>
 <li><b>LFU(least frequently used)</b> - это алгоритм хранения данных в кэше, который подсчитывает частоту использования каждого элемента и удаляет те, к которым обращаются реже всего. </li>

Допустим у нас есть уже заполненный кэш размера 4:

<image src="for_readme/cache1.jpeg" width=300px>

где слева находится самый старый и редский запрос, а справа самый частый и недавний запрос. Cнизу частота запросов. Если мы, например, захотим добавить элемент 5, то самый левый элемент кэша вытеснится:

<image src="for_readme/cache2.jpeg" width=300px>

Если же мы захотим добавить элемент 2, который уже есть в нашем кэшэ, то его частота увеличится, а позиция сдвинется вправо:

<image src="for_readme/cache3.jpeg" width=300px>

 <li><b>PCA(perfect cache algorithm) or algorithm Belady</b> - это алгоритм хранения данных в кэше, отбрасывающий из кэша ту информацию, которая не понадобится в будущем дольше всего. </li>

Допустим у нас уже имеется заполненный кэш с размером 4:

<image src="for_readme/cache4.jpeg" width=300px>

где слева находятся самые старые элементы, а справа самые новые. У нас имеется поток записи в кэш

<image src="for_readme/cache6.jpeg" width=300px>

Как мы видим, в этом потоке дольше всего не понадобятся элементы 1 и 2 из кэша. Но нам нужно удалить только один, поэтому мы выбираем самый старый из них и кладем на его место 5:

<image src="for_readme/cache5.jpeg" width=300px>

</ul>

## Как запустить программу?

```
mkdir build && cd build
```

Для ручного ввода данных достаточно ввести команду

```
cmake ../
```

Для запуска юнит-тестов нужно добавить флаг

```
cmake ../ -DTEST=ON
```

Для генерации теста нужно ввести команду

```
python3.8 test/test_gen.py 100000
```

где последний аргумент это количество генерируемых элементов.
Для dump сборки:

```
cmake ../ -DNO_OPTIMIZATION=ON
```

Для запуска lfu, pca и тестов соответсвенно:

```
./lfu
./pca
./test
```


## Как выглядит результат работы программы?

Для [теста](test/test.txt) график частоты попаданий будет иметь такой вид:

<image src="graph/graph_example.png" width=450px>

А для более простого примера, как

```
4 12 1 2 3 4 1 2 5 1 2 4 3 4
```

результат для двух кэшэй почти идентичен:

<image src="graph/graph.png" width=450px>

Так же в папке [logs](logs/) можно поэтапно увидеть как меняется наш кэш во время прохода по потоку.
