#include "ring_queue.hpp"

template<class T, class U,U BufSize>  
T RingQueue<T, U, BufSize>::RingBuf[BufSize];
