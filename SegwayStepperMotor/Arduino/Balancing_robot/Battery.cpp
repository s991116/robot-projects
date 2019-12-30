#include "Battery.h"
#include "PinSetup.h"

void Battery::Initialize() {
    this->_lowBattery = 0;
}

void Battery::UpdateBatteryLevel() {
    //Load the battery voltage to the battery_voltage variable.
    //85 is the voltage compensation for the diode.
    //Resistor voltage divider => (3.3k + 3.3k)/2.2k = 2.5
    //12.5V equals ~5V @ Analog 0.
    //12.5V equals 1023 analogRead(0).
    //1250 / 1023 = 1.222.
    //The variable battery_voltage holds 1050 if the battery voltage is 10.5V.
    
    //Battery voltage input is not working on pcb-board
    return;
    
    this->_batteryVoltage = (analogRead(PIN_ANALOG_BATTERY_VOLTAGE) * 1.222) + 85;
    
    if(this->_batteryVoltage < 1050 && this->_batteryVoltage > 800){                      //If batteryvoltage is below 10.5V and higher than 8.0V
        this->_lowBattery = 1;                                                          //Set the low_bat variable to 1
    }
}

int Battery::GetVoltage() {
    return this->_batteryVoltage;
}

bool Battery::LowBattery() {
    return this->_lowBattery;
}
