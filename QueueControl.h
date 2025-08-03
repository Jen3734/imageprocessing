#pragma once

#include "ThreadSafeQueue.h"
#include "RequestEvent.h"
#include "JobEvent.h"
#include "ThreadPool.h"
#include "CountRef.h"
#include "ThreadPool.h"
#include "MemHandleControl.h"
#include "MemHandler.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;



class QueueControl{
    public:
        QueueControl(){
            q = new ThreadSafeQueue<RequestEvent*>();
            threadpool = new ThreadPool(10);
            memVectorStore = new queue<vector<void *>*>();
            count = new CountRef();
        }
        QueueControl* getInstance(){
            if(queueControl == nullptr){
                queueControl = new QueueControl();
            }
            return queueControl;
        }
        void popEventAndAssignThreadPoolWithMem(){
            if(!lastEventFinished && !q->empty()){
                return;
            }
            RequestEvent* work = q->pop();
            vector<void *>* memVector = memHandleControl->getInstance()->eventAssign(*work);
            count->resetCounter();
            count->setRequestEvent(work);
            
            for (int i =0;i < (ImageSize/SingleImageJobSize);i = i+SingleImageJobSize){
                for(int j = i;j < i+SingleImageJobSize;j++){                
                    JobEvent* jobEvent = new JobEvent();
                    jobEvent->rawData[j-i] = work->rawData[j];
                    void* mem = memVector->at(count->getCurrentCount());
                    threadpool->enqueue([this, jobEvent, work, mem]{
                        this->getInstance()->runJob(jobEvent,work, count, mem);
                    });
                    std::this_thread::sleep_for(std::chrono::seconds(1)); 
                    count->incrementCoutner();
                }
            }
            memVectorStore->push(memVector);
        }
        vector<void *>* getLastMemVector(){
            return memVectorStore->front();
        }
        void runJob(JobEvent * e,RequestEvent* work, CountRef* count, void * mem){

            if(count->getCurrentCount() >0){
                count->decrementCounter();
            }else{
                throw "error : countRef = 0";
            }
        }

        CountRef* getCountRef(){
            return count;
        }
        ThreadSafeQueue<RequestEvent*>* getQueue(){
            return q;
        }
    private:
        static QueueControl* queueControl;
        ThreadSafeQueue<RequestEvent*>* q;
        bool lastEventFinished = true;
        ThreadPool* threadpool;
        MemHandleControl* memHandleControl;
        CountRef* count;
        queue<vector<void *>*>* memVectorStore;
};