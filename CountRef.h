#pragma once

#include <iostream>
#include "RequestEvent.h"
using namespace std;

class CountRef{
    public:
        void incrementCoutner(){
            count++;
        }
        void decrementCounter(){
            count--;
        }
        bool isCounterZero(){
            return count == 0;
        }
        void resetCounter(){
            count=0;
        }
        int getCurrentCount(){
            return count;
        }
        void setRequestEvent(RequestEvent * event){
            e = event;
        }
        RequestEvent * getRequestEvent(){
            return e;
        }
    private:
        int count = 0;
        RequestEvent * e;
};