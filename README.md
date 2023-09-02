# lru-cache

Efficient implementation of a in-memory **Cache** using **LRU** (Least Recently Used) logic. Unlike most implementation found online,
this one **guarantees constant time** in every operation, including item insertion/deletion/peek/re-position and also constant
time for all operations regarding the LRU tracking.
