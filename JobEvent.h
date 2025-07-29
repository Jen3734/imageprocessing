#pragma once
#include <array>
using namespace std;

static int const SingleImageJobSize = 3;

struct JobEvent{
    float rawData [SingleImageJobSize];
};