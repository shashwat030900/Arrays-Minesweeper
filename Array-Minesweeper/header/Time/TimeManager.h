#pragma once
#include <chrono>

namespace Time
{
    class TimeManager
    {
    private:
        static std::chrono::time_point<std::chrono::steady_clock> previous_time;
        static float delta_time;

        static void UpdateDeltaTime();
        static float CalculateDeltaTime();
        static void UpdatePreviousTime();

    public:
        static void Initialize();
        static void Update();

        static float GetDeltaTime();
    };
}
