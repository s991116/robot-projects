import lejos.robotics.EncoderMotor;

public class MotorSpeedControl {

	private EncoderMotor leftMotor;
	private EncoderMotor rightMotor;
	private int sampleTimeInMs;
	private long mrcSumPrev;
	private long mrcSum;
	final private int MaxMotorPower = 100;
	final private int MinMotorPower = -100;

	final private int averageDistanceCount = 3;
	private long averageDistanceSamples[] = new long[averageDistanceCount];
	private int averageDistanceUpdateIndex = 0;
	private long deltaDistanceAverage;
	private int averageDistanceSampleTimeMs;
	private double pSpeedCorr;
	private int motorPower;

	public MotorSpeedControl(EncoderMotor left, EncoderMotor right, int sampleTimeInMs, double PSpeedCorr)
	{
		this.leftMotor = left;
		this.rightMotor = right;
		this.sampleTimeInMs = sampleTimeInMs;
		setPSpeedCorr(PSpeedCorr);
		this.averageDistanceSampleTimeMs = this.averageDistanceCount * this.sampleTimeInMs;
	}
	
	public void UpdateMotorSpeed(int targetSpeed) {
		
		long currentMotorSpeed = CurrentMotorSpeed();
		
		AdjustMotorSpeed(currentMotorSpeed, targetSpeed);
	}

	private long CurrentMotorSpeed() {
		long tachoCountLeft, tachoCountRight, mrcDelta;

		// Keep track of motor position and speed
		tachoCountLeft = this.leftMotor.getTachoCount();
		tachoCountRight = this.rightMotor.getTachoCount();

		// Maintain previous mrcSum so that delta can be calculated and get
		// new mrcSum and Diff values
		mrcSumPrev = mrcSum;
		mrcSum = tachoCountLeft + tachoCountRight;
		// mrcDetla is the change int sum of the motor encoders, update
		// motorPos based on this detla
		mrcDelta = mrcSum - mrcSumPrev;
		UpdateDeltaAverage(mrcDelta);
		
		long currentMotorSpeed = this.deltaDistanceAverage / this.averageDistanceSampleTimeMs;
		
		return currentMotorSpeed;
	}

	private void AdjustMotorSpeed(long currentMotorSpeed, int targetSpeed) {
		int power = (int) ((currentMotorSpeed - targetSpeed) * this.pSpeedCorr );
		this.setMotorPower(power);				
	}

	private void setMotorPower(int power) {
		if(power > this.MaxMotorPower)
			this.motorPower = this.MaxMotorPower;
		else if(power < this.MinMotorPower)
			this.motorPower = this.MinMotorPower;
		
		this.motorPower = power;

		this.leftMotor.setPower(Math.abs(this.motorPower));
		this.rightMotor.setPower(Math.abs(this.motorPower));

		if(this.motorPower > 0)
		{
			this.leftMotor.forward();
			this.rightMotor.forward();
		}
		else
		{
			this.leftMotor.backward();
			this.rightMotor.backward();
		}
	}
	
	private int getMotorPower() {
		return this.motorPower;
	}

	private void UpdateDeltaAverage(long deltaDistanceSample) {
		this.deltaDistanceAverage = deltaDistanceSample;	
/*
		this.deltaDistanceAverage += (deltaDistanceSample-averageDistanceSamples[averageDistanceUpdateIndex]);	
		averageDistanceSamples[averageDistanceUpdateIndex] = deltaDistanceSample;
		if(averageDistanceUpdateIndex < averageDistanceCount-1)
		{
			averageDistanceUpdateIndex++;						
		}
		else
		{
			averageDistanceUpdateIndex = 0;						
		}
*/
	}

	public double getPSpeedCorr() {
		return pSpeedCorr;
	}

	private void setPSpeedCorr(double pSpeedCorr) {
		this.pSpeedCorr = pSpeedCorr;
	}
	
	public void Stop()
	{
		setMotorPower(0);				
	}
}
