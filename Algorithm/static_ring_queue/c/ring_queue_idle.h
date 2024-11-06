#ifndef __RING_QUEUE_IDLE_H_
#define __RING_QUEUE_IDLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MaxSize         (1024)
#define TransSize       (128)

typedef unsigned char   ElemType;
typedef unsigned char   TranType;               //max(TranType)>=TransSize

typedef struct{
    ElemType        RingBuf[MaxSize];
    ElemType*       EnqueuePos;
    ElemType*       DequeuePos;
    TranType        StringCnt;
    TranType        TransCount;
}RingQueue;

void RingQueueInit(RingQueue *rq);
ElemType* GetEnqueuePos(RingQueue *rq);
ElemType* GetDequeuePos(RingQueue *rq);
TranType GetNotEmpty(RingQueue *rq);
TranType GetDequeueNums(RingQueue *rq);
void GetTransCount(RingQueue *rq, TranType NotTransCnt);
void CallbackDispose(RingQueue *rq);

#ifdef __cplusplus
}
#endif

#endif /* __RING_QUEUE_IDLE_H_ */
