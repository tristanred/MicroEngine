#include "TickTimer.h"

TickTimer::TickTimer(uint32_t totalTime)
{
    this->currentTime = 0;
    this->totalTime = totalTime;

    isRunning = false;
}

TickTimer::~TickTimer() {}

void TickTimer::Start()
{
    this->isRunning = true;
}

void TickTimer::Stop()
{
    this->isRunning = false;
}

void TickTimer::Reset()
{
    this->currentTime = 0;
}

void TickTimer::Update(uint32_t deltaTime)
{
    if(this->isRunning)
    {
        this->currentTime += deltaTime;
    }
}

bool TickTimer::HasFinished()
{
    return this->currentTime >= this->totalTime;
}

uint32_t TickTimer::GetCurrentTime()
{
    return this->currentTime;
}

uint32_t TickTimer::GetTotalTime()
{
    return this->totalTime;
}

float TickTimer::GetCurrentPercentage()
{
    return std::min((float)this->currentTime / (float)this->totalTime, 1.0f);
}