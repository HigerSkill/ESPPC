#ifndef POMODORO_H
#define POMODORO_H

#include "esp_log.h"

class Pomodoro
{
    public:
        void start()
        {
        }
        void pause();
        void reset();
        void next();

        int work { 25 };
        int short_rest { 5 };
        int long_rest { 15 };

    private:
        bool is_running { false };

};

#endif