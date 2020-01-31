# Algorithm Library for C++
Mainly used for [competitive programming](https://en.wikipedia.org/wiki/Competitive_programming).

## DataStructures

### binary_indexed_tree.cpp
Binary Indexed Tree(BIT), also known as Fenwick Tree.

It achives O(logN) complexity for [Range Sum Query](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp).

### coordinate_compression.cpp
Coordinate Compression, a commonly used technique which is to map larger values to smaller distinct values.

### doubling.cpp
Doubling, also a commonly  used technique similar to [pointer jumping](https://en.wikipedia.org/wiki/Pointer_jumping).

### segment_tree.cpp
[Segment Tree](https://en.wikipedia.org/wiki/Segment_tree), also used for [Range Sum Query](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp).

There is no lazy version yet, but I'm working on it.

### union_find_tree.cpp
Union Find Tree, also known as [disjoint-set data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)

## Geometry
### vec2d.cpp
2d vector(math not STL) class. Used for plane figure problems.

## Math
### matrix.cpp
2d matrix class. Not finished yet.

### modlong.cpp
`modlong` is a integer type that applies `% MOD` after every opperation(+ - * / pow comb fact).

### utils.cpp
Math utility functions such as `gcd` and `lcm`.
