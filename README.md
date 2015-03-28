mphf - Minimal Perfect Hashing Library
**************************************

A perfect hash function is a hash function that maps distinct elements to a set of integers, with no collisions.

Since no collisions occur each item can be retrieved from the table in a single probe.

A minimal perfect hash function is a perfect hash function that maps n keys to n consecutive integers. 

CHM
---
An optimal algorithm for generating minimal perfect hash functions based on graphs.

The algorithm is probabilistic, involving generation of random graphs.
It uses expected linear time and requires a linear number of words to represent the hash function, and thus is optimal up to constant factors.

It runs very fast in practice.
