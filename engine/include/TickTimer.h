#pragma once

#include "core.h"

#include <cmath>
#include <algorithm>
#include <cstdint>
using namespace std;

class ENGINE_CLASS TickTimer
{
public:
    TickTimer(uint32_t totalTime);
    ~TickTimer();
    
    void Start();
    void Stop();
    void Reset();
    
    void Update(uint32_t deltaTime);
    
    bool HasFinished();
    uint32_t GetCurrentTime();
    uint32_t GetTotalTime();
    
    float GetCurrentPercentage();

private:
    bool isRunning;

    uint32_t currentTime;
    uint32_t totalTime;
};