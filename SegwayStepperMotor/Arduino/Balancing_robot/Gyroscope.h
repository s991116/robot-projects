#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <Arduino.h>
#include <Wire.h>                                            //Include the Wire.h library so we can communicate with the gyro

class Gyroscope {
    public:
        Gyroscope(const TwoWire& wire);
        void Initialize();
        void CalculateAngle();

        long gyro_yaw_calibration_value;
        long gyro_pitch_calibration_value;
        float angle_gyro;
        float angle_acc;
        float angle;
        byte start;

    private:
        TwoWire _wire;
        int gyro_address;                                     //MPU-6050 I2C address (0x68 or 0x69)
        int acc_calibration_value;
};

#endif