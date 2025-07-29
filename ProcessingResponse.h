#pragma once
#include <array>
using namespace std;

struct ProcessingResponse{
    int examNumber;
    int scanMode;
    float rawData[100];

};