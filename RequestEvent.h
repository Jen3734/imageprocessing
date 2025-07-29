#pragma once
#include <array>
using namespace std;

static int ImageSize = 100;

struct RequestEvent{
    int examNumber;
    int scanMode;
    float rawData[100];

    bool operator== (RequestEvent &in){
        if(examNumber == in.examNumber
        && scanMode == in.scanMode){
            return true;
        }
        return false;
    }
};