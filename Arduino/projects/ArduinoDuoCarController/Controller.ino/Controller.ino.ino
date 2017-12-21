#include <DueMotorEncoder.h>

#define ENCODER_LEFT_1_PIN (50)
#define ENCODER_LEFT_2_PIN (53)
#define ENCODER_RIGHT_1_PIN (51)
#define ENCODER_RIGHT_2_PIN (52)

short encoderUpdatePeriod = 10;

DueMotorEncoder dueMotorEncoder(ENCODER_LEFT_1_PIN, ENCODER_LEFT_2_PIN, ENCODER_RIGHT_1_PIN, ENCODER_RIGHT_2_PIN, encoderUpdatePeriod);

void setup() {
  Serial.begin(9600);
}

void loop() {
  dueMotorEncoder.Update();
  Serial.println(dueMotorEncoder.GetSpeedLeft());
}
