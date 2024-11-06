#include "ring_queue.h"

void RingQueueInit(RingQueue *rq){
    rq->EmptyCnt = RING_QUEUE_SIZE-1;
    rq->Head = 0;
    rq->Tail = 0;
}

bool isEmpty(RingQueue *rq){
    return (rq->Head == rq->Tail);
}

bool isFull(RingQueue *rq){
    return (rq->Head == (rq->Tail+1)%RING_QUEUE_SIZE);
}

IndexType QueryEmpty(RingQueue *rq){
    return rq->EmptyCnt;
}

bool PushRingQueue(RingQueue *rq, ElementType data){
    if(isFull(rq))
        return false;
    rq->RingBuf[rq->Tail++] = data;
    if(rq->Tail == RING_QUEUE_SIZE) rq->Tail = 0;
    rq->EmptyCnt--;
    return true;
}

ElementType PopRingQueue(RingQueue *rq){
    if(isEmpty(rq))
        return false;
    rq->EmptyCnt++;
    if(rq->Head == RING_QUEUE_SIZE) rq->Head = 0;
    return rq->RingBuf[rq->Head++];
}
