Buffers
========

1.  Will be attached to epoll/kqueue structures to continue reading till a complete request is formed.
2.  Probably just use jemalloc to malloc and free underlying buffers since allocations and free happen on the same thread.