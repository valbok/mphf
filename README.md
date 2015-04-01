mphf - Minimal Perfect Hashing Library
--------------------------------------

A perfect hash function is a hash function that maps distinct elements to a set of integers, with no collisions.

Since no collisions occur each item can be retrieved from the table in a single probe.

A minimal perfect hash function is a perfect hash function that maps n keys to n consecutive integers. 
Minimal perfect hash functions are widely used for memory efficient storage and fast retrieval of items from static sets.

**********
CHM
===
Overview of the algorithm: http://habrahabr.ru/post/254431
An optimal algorithm for generating minimal perfect hash functions based on random graphs.

The algorithm is probabilistic, involving generation of random graphs.
It uses expected linear time and requires a linear number of words to represent the hash function, and thus is optimal up to constant factors.

It runs very fast in practice.

- Construct minimal MPHFs in linear time. 
- It is based on acyclic random graphs 
- The resulting MPHFs are order preserving.

Build
===

    $ mkdir build; make
    $ ./build/ChmTest
