# Algorithm Library for C++
Mainly used for [competitive programming](https://en.wikipedia.org/wiki/Competitive_programming).

## DataStructures

* **binary_indexed_tree.cpp** : Binary Indexed Tree(BIT), also known as Fenwick Tree. It achives O(logN) time complexity for [Range Sum Query](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp).

* **coordinate_compression.cpp** : Coordinate Compression, a commonly used technique which is to map larger values to smaller distinct values.

* **doubling.cpp** : Doubling, also a commonly  used technique similar to [pointer jumping](https://en.wikipedia.org/wiki/Pointer_jumping).

* **segment_tree.cpp** : [Segment Tree](https://en.wikipedia.org/wiki/Segment_tree), also used for [Range Sum Query](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp). There is no lazy version yet, but I'm working on it.

* **suffix_array.cpp** : Constructs a [Suffix Array](https://en.wikipedia.org/wiki/Suffix_array) with O(n) complexity by using the [SA-IS](https://github.com/vladtepes1473/FM-Index/blob/master/readings/Linear%20Suffix%20Array%20Construction%20by%20Almost%20Pure%20Induced-Sorting.pdf) algorithm.

* **union_find_tree.cpp** : Union Find Tree, also known as [disjoint-set data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)

## Geometry
* **geometry2d.cpp** : 2D geometry library used for plane figure problems.

## Graph
* **ford_fulkerson.cpp** : [Ford-Fulkerson algorithm](https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm)

* **graph.cpp** : Trying to make a comprehensive graph class which has all the graph algorithms I've implemented, but I'm still working on it.

* **kruscal.cpp** : [Krucsal's algorithm](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)

* **dijkstra.cpp** : [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

* **bellman_ford.cpp** : [Bellman-Ford algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)

* **warshall_floyd.cpp** : [Warshall-Floyd algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)

* **topological_sort.cpp** : [Topological sorting](https://en.wikipedia.org/wiki/Topological_sorting) for [DAGs](https://en.wikipedia.org/wiki/Directed_acyclic_graph).

## Math
* **matrix.cpp**
2d matrix class. Not finished yet.

* **modlong.cpp** : `modlong` is a integer type that applies `% MOD` after every opperation( such as `+` `-` `*` `/` `pow` `comb` `fact`).

* **prime_factorization.cpp** : [Prime Factorization](https://en.wikipedia.org/wiki/Integer_factorization)

* **utils.cpp** : Math utility functions such as `gcd` and `lcm`.
