#include <stdio.h>
#include "ring_queue.h"

int main() {
    RingQueue rq;
    RingQueueInit(&rq);
    unsigned short Emptytmp = QueryEmpty(&rq);
    printf("Emptytmp = %d\n", Emptytmp);
    PushRingQueue(&rq, 1);
    printf("Add 1 to queue\n");
    printf("Emptytmp = %d\n", QueryEmpty(&rq));
    PushRingQueue(&rq, 2);
    printf("Add 2 to queue\n");
    printf("Emptytmp = %d\n", QueryEmpty(&rq));
    PushRingQueue(&rq, 3);
    printf("Add 3 to queue\n");
    printf("Emptytmp = %d\n", QueryEmpty(&rq));
    PushRingQueue(&rq, 4);
    printf("Add 4 to queue\n");
    printf("Emptytmp = %d\n", QueryEmpty(&rq));
    printf("Pop element from queue: %d\n", PopRingQueue(&rq));
    printf("Emptytmp = %d\n", QueryEmpty(&rq));
    printf("Pop element from queue: %d\n", PopRingQueue(&rq));
    printf("Emptytmp = %d\n", QueryEmpty(&rq));
    printf("Pop element from queue: %d\n", PopRingQueue(&rq));
    printf("Emptytmp = %d\n", QueryEmpty(&rq));
    printf("Pop element from queue: %d\n", PopRingQueue(&rq));
    printf("Emptytmp = %d\n", QueryEmpty(&rq));
    return 0;
}
