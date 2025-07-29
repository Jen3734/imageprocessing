#pragma once

#include "ProcessingResponse.h"
#include "CountRef.h"
#include "QueueControl.h"
#include "MemHandleControl.h"
#include <iostream>
#include <vector>

class OutputDriver{
    public:
        OutputDriver(CountRef* c){
            count = c;
        }
        void flushOutput(){
            while(true){
                if (count->isCounterZero()){
                    ProcessingResponse* output = formatResponse();
                }
            }

        }
        ProcessingResponse* formatResponse(){
            vector<void *>* memVector = queueControl->getLastMemVector();
            ProcessingResponse* response = new ProcessingResponse();
            for (int i =0;i < (int)memVector->size();i++){
                writeFromMemory(response, memVector->at(i),count->getRequestEvent());
            }
            memHandleControl->getInstance()->freeJobMemoryFromMemVector(memVector);
            memHandleControl->getInstance()->cleanMemVectorMap(count->getRequestEvent());
        }
        ProcessingResponse * writeFromMemory(ProcessingResponse* response, void * pMemory, RequestEvent* e){
            char* buffer = static_cast<char*> (pMemory);

            
        }
    private:
        CountRef* count;
        QueueControl * queueControl;
        MemHandleControl* memHandleControl;
};