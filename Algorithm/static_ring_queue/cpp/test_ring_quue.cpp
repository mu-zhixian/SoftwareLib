#include  <iostream>
#include "ring_queue.hpp"
using namespace std;

int main(){
    RingQueue<int, 5> rq;
    cout<<"push element to ring queue:"<<endl;
    rq.printfvalue();
    rq.PushQueue(1);
    rq.printfvalue();
    rq.PushQueue(2);
    rq.printfvalue();
    rq.PushQueue(3);
    rq.printfvalue();
    rq.PushQueue(4);
    rq.printfvalue();  
    cout<<"push element 5 to ring queue, state:"<<rq.PushQueue(5)<<endl;
    rq.printfvalue();
    cout<<"pop element from ring queue:"<<endl;
    rq.PopQueue();
    rq.printfvalue();
    rq.PopQueue();
    rq.printfvalue();
    rq.PopQueue();
    rq.printfvalue();
    rq.PopQueue();
    rq.printfvalue();
    cout<<"pop element 5 to ring queue, state:"<<rq.PopQueue()<<endl;
    rq.printfvalue();

    return 0;
}