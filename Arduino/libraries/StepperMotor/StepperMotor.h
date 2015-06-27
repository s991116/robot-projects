/**
  This class is designed to control a stepper motor 28BYJ-48

  This motor has the following specifications
    4 phases
    1/64 speed ratio
    Stride angle: 5.625deg/64
      => 4094 steps for 360deg
    Maximum frequency: 1KHz
    
    The sequence for counter-clockwise rotation is (Input PIN of the control board) 
    IN1  IN2  IN3  IN4
    0    0    0    1
    0    0    1    1
    0    0    1    0
    0    1    1    0
    0    1    0    0
    1    1    0    0
    1    0    0    0
    1    0    0    1
    
   For another motor this sequence will be different 
   
   The specifications of the motor and the board can be found at:
   http://www.geeetech.com/wiki/index.php/Stepper_Motor_5V_4-Phase_5-Wire_%26_ULN2003_Driver_Board_for_Arduino
*/
#ifndef StepperMotor_h
#define StepperMotor_h

#include "arduino.h"

#define PHASE_NUMBER 4
#define NUMBER_OF_STEPS 8
#define DEFAULT_PERIOD 10

class StepperMotor 
{
  public:
    /**
     * Constructor assigning the motor control PIN
     */
    StepperMotor(byte motorPin1, byte motorPin2, byte motorPin3, byte motorPin4);  
    
	/**
	 * Sets the period to send the command quartet
	 *
	 * @param period Period in ms between to control quartets
	 */
    void  setPeriod(int period);
    
	/**
	 * Moves the motor of a given number of steps.
	 * Positive in a direction, Negative in the opposite
	 * 
	 * @param numberOfSteps	Number of steps to move
	 */
    bool  move(int numberOfSteps);
	
	/**
	 * Stops the motor, setting all bits to LOW and raising the 
	 * interrupt flag when interrupt is set to true
	 *
	 * @param interrupt If true it will stop the current sequence. When set to true
	 * 		  this method is meant to be called from an interruption serving
	 *		  routine (ISR). When false it doesn't raise the interrupt flag, just
	 *		  set all the PIN to LOW.If not called from an interrupt routine, it 
     * 		  prevents the motor from running. 
	 */
	void  stop(bool interrupt = false);
	
	/**
	 * Reset the interrupt flag to false so the motor
	 * can be moved again
	 */
	void reset();
 
  private:
	void moveOneStep(byte seqIdx);
	bool moveOneStepForward();
	bool moveOneStepBackward();
	bool moveStepsForward(int steps);
	bool moveStepsBackward(int steps);
	inline void assignMotorPins()
	{
		for (int n = 0; n < PHASE_NUMBER; ++n)
		{
			pinMode(motorPins[n], OUTPUT);
		}
	}
	
	inline int incrementStep(int stepId)
	{
		return (stepId + 1) % NUMBER_OF_STEPS;
	}
	
	volatile bool interrupt;
    int period;                    // Period in ms
    byte motorPins[PHASE_NUMBER];   // Motor PIN assignement
    byte stepSequence[NUMBER_OF_STEPS][PHASE_NUMBER];
	byte stepIdx;
	
	static byte M_28BYJ_48[][PHASE_NUMBER];
};

#endif