#include "Gyroscope.h"

Gyroscope::Gyroscope() {}

void Gyroscope::Initialize() {
    this->gyro_address = 0x68;                                                 //MPU-6050 I2C address (0x68 or 0x69)
    this->acc_calibration_value = -8120;                                       //Enter the accelerometer calibration value

    Wire.begin();                                                             //Start the I2C bus as master
    TWBR = 12;                                                                //Set the I2C clock speed to 400kHz

    //By default the MPU-6050 sleeps. So we have to wake it up.
    Wire.beginTransmission(gyro_address);                                     //Start communication with the address found during search.
    Wire.write(0x6B);                                                         //We want to write to the PWR_MGMT_1 register (6B hex)
    Wire.write(0x00);                                                         //Set the register bits as 00000000 to activate the gyro
    Wire.endTransmission();                                                   //End the transmission with the gyro.
    //Set the full scale of the gyro to +/- 250 degrees per second
    Wire.beginTransmission(gyro_address);                                     //Start communication with the address found during search.
    Wire.write(0x1B);                                                         //We want to write to the GYRO_CONFIG register (1B hex)
    Wire.write(0x00);                                                         //Set the register bits as 00000000 (250dps full scale)
    Wire.endTransmission();                                                   //End the transmission with the gyro
    //Set the full scale of the accelerometer to +/- 4g.
    Wire.beginTransmission(gyro_address);                                     //Start communication with the address found during search.
    Wire.write(0x1C);                                                         //We want to write to the ACCEL_CONFIG register (1A hex)
    Wire.write(0x08);                                                         //Set the register bits as 00001000 (+/- 4g full scale range)
    Wire.endTransmission();                                                   //End the transmission with the gyro
    //Set some filtering to improve the raw data.
    Wire.beginTransmission(gyro_address);                                     //Start communication with the address found during search
    Wire.write(0x1A);                                                         //We want to write to the CONFIG register (1A hex)
    Wire.write(0x03);                                                         //Set the register bits as 00000011 (Set Digital Low Pass Filter to ~43Hz)
    Wire.endTransmission();                                                   //End the transmission with the gyro 

    int receive_counter;
    for(receive_counter = 0; receive_counter < 500; receive_counter++){       //Create 500 loops
        //if(receive_counter % 15 == 0)digitalWrite(13, !digitalRead(13));    //Change the state of the LED every 15 loops to make the LED blink fast
        Wire.beginTransmission(gyro_address);                                 //Start communication with the gyro
        Wire.write(0x43);                                                     //Start reading the Who_am_I register 75h
        Wire.endTransmission();                                               //End the transmission
        Wire.requestFrom(gyro_address, 4);                                    //Request 2 bytes from the gyro
        this->gyro_yaw_calibration_value += Wire.read()<<8|Wire.read();        //Combine the two bytes to make one integer
        this->gyro_pitch_calibration_value += Wire.read()<<8|Wire.read();      //Combine the two bytes to make one integer
        delayMicroseconds(3700);                                              //Wait for 3700 microseconds to simulate the main program loop time
    }
    this->gyro_pitch_calibration_value /= 500;                                 //Divide the total value by 500 to get the avarage gyro offset
    this->gyro_yaw_calibration_value /= 500;                                   //Divide the total value by 500 to get the avarage gyro offset
}

void Gyroscope::CalculateAngle() {
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Angle calculations
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Wire.beginTransmission(this->gyro_address);                                //Start communication with the gyro
    Wire.write(0x3F);                                                         //Start reading at register 3F
    Wire.endTransmission();                                                   //End the transmission
    Wire.requestFrom(this->gyro_address, 2);                                   //Request 2 bytes from the gyro
    int accelerometer_data_raw = Wire.read()<<8|Wire.read();                  //Combine the two bytes to make one integer
    accelerometer_data_raw += this->acc_calibration_value;                     //Add the accelerometer calibration value

    if(accelerometer_data_raw > 8200)accelerometer_data_raw = 8200;           //Prevent division by zero by limiting the acc data to +/-8200;
    if(accelerometer_data_raw < -8200)accelerometer_data_raw = -8200;         //Prevent division by zero by limiting the acc data to +/-8200;

    this->angle_acc = asin((float)accelerometer_data_raw/8200.0)* 57.296;      //Calculate the current angle according to the accelerometer
    if(this->start == 0 && this->angle_acc > -0.5&& this->angle_acc < 0.5){      //If the accelerometer angle is almost 0
        this->angle_gyro = this->angle_acc;                                     //Load the accelerometer angle in the angle_gyro variable
        this->start = 1;                                                       //Set the start variable to start the PID controller
    }

    Wire.beginTransmission(this->gyro_address);                                //Start communication with the gyro
    Wire.write(0x43);                                                         //Start reading at register 43
    Wire.endTransmission();                                                   //End the transmission
    Wire.requestFrom(this->gyro_address, 4);                                   //Request 4 bytes from the gyro
    int gyro_yaw_data_raw = Wire.read()<<8|Wire.read();                           //Combine the two bytes to make one integer
    int gyro_pitch_data_raw = Wire.read()<<8|Wire.read();                         //Combine the two bytes to make one integer

    gyro_pitch_data_raw -= this->gyro_pitch_calibration_value;           //Add the gyro calibration value
    this->angle_gyro += gyro_pitch_data_raw * 0.000031;                             //Calculate the traveled during this loop angle and add this to the angle_gyro variable
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //MPU-6050 offset compensation
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Not every gyro is mounted 100% level with the axis of the robot. This can be cause by misalignments during manufacturing of the breakout board. 
    //As a result the robot will not rotate at the exact same spot and start to make larger and larger circles.
    //To compensate for this behavior a VERY SMALL angle compensation is needed when the robot is rotating.
    //Try 0.0000003 or -0.0000003 first to see if there is any improvement.

    gyro_yaw_data_raw -= this->gyro_yaw_calibration_value;               //Add the gyro calibration value
    //Uncomment the following line to make the compensation active
    //this->angle_gyro -= gyro_yaw_data_raw * 0.0000003;                            //Compensate the gyro offset when the robot is rotating

    this->angle_gyro = this->angle_gyro * 0.9996 + angle_acc * 0.0004;          //Correct the drift of the gyro angle with the accelerometer angle
    this->angle = this->angle_gyro;
}