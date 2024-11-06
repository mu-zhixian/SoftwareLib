#ifndef __RING_QUEUE_H_
#define __RING_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define RING_QUEUE_SIZE (100)

typedef unsigned char   ElementType;
typedef unsigned short  IndexType;

typedef struct{
    ElementType RingBuf[RING_QUEUE_SIZE];
    IndexType   EmptyCnt;
    IndexType   Head;
    IndexType   Tail;
}RingQueue;

void RingQueueInit(RingQueue *rq);
bool isEmpty(RingQueue *rq);
bool isFull(RingQueue *rq);
IndexType QueryEmpty(RingQueue *rq);
bool PushRingQueue(RingQueue *rq, ElementType data);
ElementType PopRingQueue(RingQueue *rq);

#ifdef __cplusplus
}
#endif

#endif /* __RING_QUEUE_H_ */
