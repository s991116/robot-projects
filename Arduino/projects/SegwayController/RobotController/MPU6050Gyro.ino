#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

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
VectorFloat gravity;    // [x, y, z]            gravity vector

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

bool InitializeMPU()
{
  // initialize device
#ifdef DEBUG_MANUAL_COMMAND
  Serial.println(F("Initializing I2C devices..."));
#endif
  mpu.initialize();

    // verify connection
  bool mpuConnection = mpu.testConnection();
#ifdef DEBUG_MANUAL_COMMAND
    Serial.println(F("Testing device connections..."));
#endif
    if(mpuConnection) {
#ifdef DEBUG_MANUAL_COMMAND
      Serial.println(F("MPU6050 connection successful"));
#endif
    }
    else
    {
#ifdef DEBUG_MANUAL_COMMAND
      Serial.println(F("MPU6050 connection failed"));
#endif
      return false;
    }
    // load and configure the DMP
#ifdef DEBUG_MANUAL_COMMAND
    Serial.println(F("Initializing DMP..."));
#endif
  devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
        // turn on the DMP, now that it's ready
#ifdef DEBUG_MANUAL_COMMAND
      Serial.println(F("Enabling DMP..."));
#endif
    mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
  #ifdef DEBUG_MANUAL_COMMAND
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
  #endif
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
  #ifdef DEBUG_MANUAL_COMMAND
      Serial.println(F("DMP ready! Waiting for first interrupt..."));
  #endif
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  #ifdef DEBUG_MANUAL_COMMAND
    Serial.println(F("GetFIFOPacketSize."));
  #endif
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
#ifdef DEBUG_MANUAL_COMMAND
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
#endif
    return false;
  }
  return true;
}

boolean MPUDataReady()
{
  return (mpuInterrupt || fifoCount >= packetSize);  
}

void UpdateGyroData()
{
  if(!MPUDataReady())
    return;
  
  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    SetLED(false);
    mpu.resetFIFO();
#ifdef DEBUG_MANUAL_COMMAND
    Serial.println(F("FIFO overflow!"));
#endif
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

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

#ifdef DEBUG_MANUAL_COMMAND
    Serial.print("ypr\t");
    Serial.print(ypr[0] * 180/M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180/M_PI);
    Serial.print("\t");
    Serial.print(ypr[2] * 180/M_PI);
    Serial.print("accel\t");
    Serial.print(gyro[0]);
    Serial.print("\t");
    Serial.print(gyro[1]);
    Serial.print("\t");
    Serial.println(gyro[2]);
#endif
  }
}
