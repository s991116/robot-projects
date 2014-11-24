import lejos.robotics.EncoderMotor;

public class MotorSpeedControl {

	private static final int deadSpeed = 70;
	private static final long deadTime = 1;
	private static final int PIDOffset = 256;
	private EncoderMotor leftMotor;
	private EncoderMotor rightMotor;
	final private int MaxMotorPower = 100*PIDOffset;

	private double pSpeedCorr;
	private int posOffset;
	private int prevPos;
	private int kPos = 10;
	private int kPosRate = 400;
	private int motorPowerOffset = 4;

	private int prevTorque;
	private int lastTorque;
	private int speed;
	private int pos;
	
	private int nrOfSpeedMeasures = 4;
	private int[] speedMeasures = new int[nrOfSpeedMeasures];
	private int speedMeasureIndex = 0;
	private int averageSpeed;

	public MotorSpeedControl(EncoderMotor left, EncoderMotor right)
	{
		this.leftMotor = left;
		this.rightMotor = right;
		ResetPosition();
	}
	
	public void Stop()
	{
		leftMotor.setPower(0);
		rightMotor.setPower(0);
	}
	
	public void ResetPosition() {
        posOffset = (leftMotor.getTachoCount() + rightMotor.getTachoCount())/2;
	}
	
	public void UpdateMotorSpeed(int angleCorrection, int turn) throws InterruptedException {
		
        pos = -((leftMotor.getTachoCount() + rightMotor.getTachoCount())/2 - posOffset);
        speed = this.GetAverageSpeed(pos - prevPos);
        prevPos = pos;

		int torque = angleCorrection + kPos*pos + kPosRate*speed;

	    // Limit power to 100%
	    if (torque > MaxMotorPower)
	        torque = MaxMotorPower;
	    else if (torque < -MaxMotorPower)
	        torque = -MaxMotorPower;

	    //Smooth the shift from one power setting to the next
//	    torque = (torque + prevTorque)/2;
//	    prevTorque = torque;
	    
	    // Allow for motor power offset
	    if (torque > 0)
	        torque = motorPowerOffset + (torque*(100-motorPowerOffset) + (MaxMotorPower)/2)/(MaxMotorPower);
	    else if (torque < 0)
	        torque = -motorPowerOffset + (torque*(100-motorPowerOffset) - (MaxMotorPower)/2)/(MaxMotorPower);
	    
        // Allow for backlash in the gear system
        if (torque != 0 && ((lastTorque ^ torque) & 0x80000000) != 0)
        {
            lastTorque = torque;
            int t = (torque < 0 ? -deadSpeed : deadSpeed);
            leftMotor.setPower(-t);
            rightMotor.setPower(-t);
            Thread.sleep(deadTime);
        }
	            
        // Set the power output
        pSpeedCorr = torque;
        leftMotor.setPower(-torque + turn);
        rightMotor.setPower(-torque - turn);		
	}
	
	private int GetAverageSpeed(int speedMeasure) {
		
		if(speedMeasureIndex == nrOfSpeedMeasures-1)
		{
			speedMeasureIndex = 0;
		}
		else {
			speedMeasureIndex++;
		}
		
		averageSpeed += (speedMeasure - speedMeasures[speedMeasureIndex]); 
		
		speedMeasures[speedMeasureIndex] = speedMeasure;
		
		return averageSpeed;
	}
	
	public double getPSpeedCorr() {
		return pSpeedCorr;
	}

	public int getSpeed() {
		return this.speed;
	}

	public int getPosition() {
		return this.pos;
	}
}
