#include "../../header/Time/TimeManager.h"

namespace Time
{
    // Static variable definitions
    std::chrono::time_point<std::chrono::steady_clock> TimeManager::previousTime;
    float TimeManager::deltaTime = 0.0f;

    void TimeManager::Initialize()
    {
        previousTime = std::chrono::steady_clock::now();
        deltaTime = 0.0f;
    }

    void TimeManager::Update()
    {
        UpdateDeltaTime();
    }

    float TimeManager::GetDeltaTime()
    {
        return deltaTime;
    }

    void TimeManager::UpdateDeltaTime()
    {
        deltaTime = CalculateDeltaTime();
        UpdatePreviousTime();
    }

    float TimeManager::CalculateDeltaTime()
    {
        // Calculate time difference in microseconds between the current and previous frame.
        int delta = std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now() - previousTime).count();

        // Convert delta time from microseconds to seconds.
        return static_cast<float>(delta) / 1000000.0f;
    }

    void TimeManager::UpdatePreviousTime()
    {
        previousTime = std::chrono::steady_clock::now();
    }
}
