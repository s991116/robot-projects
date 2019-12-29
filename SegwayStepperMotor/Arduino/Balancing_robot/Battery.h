#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>

class Battery {
    public:
        void Initialize();
        void UpdateBatteryLevel();
        int GetVoltage();
        bool LowBattery();
        
    private:
        float _batteryVoltage;
        bool _lowBattery;
};

#endif