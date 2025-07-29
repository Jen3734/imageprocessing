#pragma once

#include "MemHandler.h"
#include "RequestEvent.h"
#include <unordered_map>
#include <iostream>
#include <vector>


using namespace std;

class MemHandleControl{
    public:

        MemHandleControl* getInstance(){
            if(memHandleControl == nullptr){
                memHandleControl = new MemHandleControl();
            }
            return memHandleControl;
        }
        MemHandleControl(){
            Memory_Manager * memoryHandler = 
            InitializeMemoryManager(10, 
						10, 
						10);
        }
        Memory_Manager* getMemHandler(){
            return &memoryHandler;
        }
        vector<void *>* eventAssign(RequestEvent& e){ //return memory Address Assigned by MemHandle
            addressVec.clear();
            addressVec.reserve(ImageSize/3);// reserve the size of number of images
            vector<void*>* addressForThisEvent = new vector<void *>(ImageSize/3);
            for (int i =0;i < ImageSize;i=i+3){
                addressForThisEvent->push_back(Allocate(10,&memoryHandler));
                addressVec[i] = *(addressForThisEvent->rbegin());
            }
            map[&e] = &addressVec;
            return addressForThisEvent;    
        }
        vector<void*>* getAddress(RequestEvent* event){
            return map[event];
        }

        bool freeJobMemory(RequestEvent& e, int id, void* mem){
            vector<void*> * addressForThisEvent = map[&e];
                Free(10,addressForThisEvent->at(id), & memoryHandler);
            addressForThisEvent->erase(addressForThisEvent->begin()+id);
            if(addressForThisEvent->empty()){
                map.erase(&e);
            }
            return true;
        }
        bool freeJobMemoryFromMemVector(vector<void *>* memVector){
            for(int i = 0;i < memVector->size();i++){

                Free(10,memVector->at(i), & memoryHandler);
                memVector->erase(memVector->begin()+i);

            }
            return true;
        }
        bool cleanMemVectorMap(RequestEvent* e){
            map.erase(e);
        }
    private:
        static MemHandleControl* memHandleControl;
        vector<void *> addressVec;
        unordered_map<RequestEvent*, vector<void*>*> map;
        Memory_Manager memoryHandler;
};