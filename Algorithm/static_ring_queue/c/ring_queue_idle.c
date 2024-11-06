#include "ring_queue_idle.h"

void RingQueueInit(RingQueue *rq){
    rq->EnqueuePos = rq->RingBuf;
    rq->DequeuePos = rq->RingBuf;
    rq->StringCnt = 0;
    rq->TransCount = 0;
}

ElemType* GetEnqueuePos(RingQueue *rq){
    return rq->EnqueuePos;
}

ElemType* GetDequeuePos(RingQueue *rq){
    return rq->DequeuePos;
}

TranType GetNotEmpty(RingQueue *rq){
    return rq->StringCnt;
}

TranType GetDequeueNums(RingQueue *rq){
    TranType tmpcnt = 0;
    while(*rq->DequeuePos++ != 0x00)
        tmpcnt++;
    if((&rq->RingBuf[MaxSize]-rq->DequeuePos)/sizeof(ElemType) <= TransSize)
        rq->DequeuePos = rq->RingBuf;
    rq->StringCnt--;
    return tmpcnt;
}

void GetTransCount(RingQueue *rq, TranType NotTransCnt){
    rq->TransCount = TransSize-NotTransCnt;
}

void CallbackDispose(RingQueue *rq){
    rq->EnqueuePos += rq->TransCount*sizeof(ElemType);
    *rq->EnqueuePos = 0x00;
    rq->EnqueuePos++;
    rq->StringCnt++;
    if((&rq->RingBuf[MaxSize]-rq->EnqueuePos)/sizeof(ElemType) <= TransSize)
        rq->EnqueuePos = rq->RingBuf;
    
    if(rq->EnqueuePos <= rq->DequeuePos){
        while((rq->DequeuePos-rq->EnqueuePos)/sizeof(ElemType) <= TransSize){
            while(*rq->DequeuePos++ != 0x00);
            rq->DequeuePos--;
            *rq->DequeuePos = 0x30;
            rq->DequeuePos++;
            rq->StringCnt--;
            // printf("RingQueue over write!\r\n");
            if((&rq->RingBuf[MaxSize]-rq->DequeuePos)/sizeof(ElemType) <= TransSize){
                rq->DequeuePos = rq->RingBuf;
                break;
            }
        }
    }
}
