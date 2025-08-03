#pragma once

#include "ThreadSafeQueue.h"
#include "RequestEvent.h"
#include <iostream>
#include <vector>

class InputInterface{
    public:
        void setQueue(ThreadSafeQueue<RequestEvent *>* que){
            queue = que;
        }
        void runInputInterface(){
            RequestEvent a = RequestEvent();
            a.examNumber = 2;
            float temp[100];
            temp[0] = 1;
            memcpy(a.rawData, temp, 100);
            a.scanMode = 1;
            
            queue->push(&a);

            RequestEvent b = RequestEvent();
            b.examNumber = 2;
            temp[1] = 2;
            memcpy(b.rawData, temp, 100);
            b.scanMode = 1;
            
            queue->push(&b);

            RequestEvent c = RequestEvent();
            c.examNumber = 2;
            temp[2] = 3;
            memcpy(c.rawData, temp, 100);
            c.scanMode = 1;
            
            queue->push(&c);

        }
    private:
        ThreadSafeQueue<RequestEvent *> * queue;

};