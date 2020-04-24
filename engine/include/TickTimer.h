#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

#include "core.h"
using namespace std;

/**
 * \brief Timer object.
 *
 * The timer is stopped when created.
 *
 * This timer is started with a total time in seconds and when started, counts
 * up to it. The timer can be queried to see if it finished or to get the
 * percentage of completed time.
 */
class ENGINE_CLASS TickTimer
{
public:
    TickTimer(uint32_t totalTime);
    ~TickTimer();

    /**
     * \brief Start the timer.
     */
    void Start();

    /**
     * \brief Stop the timer.
     */
    void Stop();

    /**
     * \brief Reset the time to 0
     */
    void Reset();

    /**
     * \brief Called each frame to update the ticker's time.
     *
     * \param deltaTime - Time difference between this frame and the last.
     */
    void Update(uint32_t deltaTime);

    /**
     * \brief Returns if the timer has reached the time specified in the
     * constructor.
     *
     * \return bool - True if the timer is completed.
     */
    bool HasFinished();

    /**
     * \brief Get the current time of the timer, in miliseconds.
     *
     * \return uint32_t - Time in miliseconds.
     */
    uint32_t GetCurrentTime();

    /**
     * \brief Get the end time of the timer.
     *
     * \return uint32_t - End time in miliseconds.
     */
    uint32_t GetTotalTime();

    /**
     * \brief Get the current percentage of completion.
     *
     * \return float - Percent from 0 to 1.
     */
    float GetCurrentPercentage();

private:
    bool isRunning;

    uint32_t currentTime;
    uint32_t totalTime;
};