#ifndef __RING_QUEUE_H_
#define __RING_QUEUE_H_

template<class T, class U, U BufSize>
class RingQueue{
public:
    explicit RingQueue(){
        Size = BufSize;
        EmptyCnt = BufSize-1;
        Head = 0;
        Tail = 0;
    }

    bool isEmpty() const{
        return (Head == Tail);
    }

    bool isFull() const{
        return (Head == (Tail+1)%Size);
    }

    unsigned short QueryEmpty(){
        return EmptyCnt;
    }

    bool PushQueue(T element){
        if(isFull())
            return false;
        RingBuf[Tail++] = element;
        if(Tail == Size) Tail = 0;
        EmptyCnt--;
        return true;
    }

    T PopQueue() noexcept{
        if(isEmpty())
            return false;
        EmptyCnt++;
        if(Head == Size) Head = 0;
        return RingBuf[Head++];
    }

    bool PushQueues(T* element, U len){
        if(isFull() || (len > EmptyCnt))
            return false;
        for(U i=0; i<len; i++){
            RingBuf[Tail++] = *element++;
            if(Tail == Size) Tail = 0;
        }   EmptyCnt -= len;
        return true;
    }

    bool PopQueues(T* element, U len){
        if(isEmpty() || (len > Size-1-EmptyCnt))
            return false;
        for(U i=0; i<len; i++){
            *element++ = RingBuf[Head++];
            if(Head == Size) Head = 0;
        }   EmptyCnt += len;
        return true;
    }

private:
    static T RingBuf[BufSize]; 
    U Head;
    U Tail;
    U Size;
    U EmptyCnt;
};

template<class T, class U, U BufSize>  
T RingQueue<T, U, BufSize>::RingBuf[BufSize];

#endif /* __RING_QUEUE_H_ */
