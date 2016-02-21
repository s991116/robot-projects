// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev_duo.h"

#include "MPU6050_6Axis_MotionApps20_duo.h"

MPU6050 mpu;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
int16_t gyro[3];

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

int16_t ax, ay, az;
int16_t gx, gy, gz;

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void InitializeMPU() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Wire.setClock(400000); //400kHz I2C speed
    WriteLog("Initializing I2C MPU6050");
    mpu.initialize();

    WriteLog("Testing device connections...");
    if(mpu.testConnection())
    {
      WriteLog("MPU6050 connection successful");
    }
    else
    {
      WriteLog("MPU6050 connection failed");
    }

    WriteLog("Initializing DMP...");
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(-43);  //220
    mpu.setYGyroOffset(-23);  //76
    mpu.setZGyroOffset(40);  //-85
    mpu.setZAccelOffset(1835); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        WriteLog("Enabling DMP...");
        mpu.setDMPEnabled(true);

        WriteLog("Enabling interrupt detection (Arduino external interrupt 0)...");
        attachInterrupt(digitalPinToInterrupt(2), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        WriteLog("DMP ready! Waiting for first interrupt...");
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        WriteLog("DMP Initialization failed code: ");
        WriteLog((int)(devStatus));
    }
}


bool writeInfoMessage = false;

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void UpdateGyroData() {
    // if programming failed, don't try to do anything

    if(!mpuInterrupt && fifoCount < packetSize) {
      return;
    }

    long startCalc = micros();
    
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        WriteLog("MPU Data overflow");
        mpu.resetFIFO();
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        //while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
        if(fifoCount < packetSize)
        {
          WriteLog("Not enough data available");
          return;
        }

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGyro(gyro, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        
        long timer = micros();
        calcTime = timer - startCalc;
        updatePeriod = timer - updateTime;
        
        updateTime = timer;
    }
}
