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
	private float pSpeedCorr;

	public MotorSpeedControl(EncoderMotor left, EncoderMotor right, int sampleTimeInMs, float PSpeedCorr)
	{
		this.leftMotor = left;
		this.rightMotor = right;
		this.sampleTimeInMs = sampleTimeInMs;
		setPSpeedCorr(PSpeedCorr);
		this.averageDistanceSampleTimeMs = this.averageDistanceCount * this.sampleTimeInMs;
	}
	
	public void UpdateMotorSpeed(int targetSpeed) {
		
		long currentMotorSpeed = CurrentMotorSpeed();
		
		UpdateMotorSpeed(currentMotorSpeed, targetSpeed);
	}

	private long CurrentMotorSpeed() {
		long currentMotorSpeed;
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
		
		currentMotorSpeed = this.deltaDistanceAverage / this.averageDistanceSampleTimeMs;
		
		return currentMotorSpeed;
	}

	private void UpdateMotorSpeed(long currentMotorSpeed, int targetSpeed) {
		int power = (int) ((currentMotorSpeed - targetSpeed) * this.pSpeedCorr );
		
		power = GetLimitPower(power);
		
		this.leftMotor.setPower(Math.abs(power));
		this.rightMotor.setPower(Math.abs(power));

		if(power > 0)
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

	private int GetLimitPower(int power) {
		
		if(power > this.MaxMotorPower)
			return this.MaxMotorPower;
		else if(power < this.MinMotorPower)
			return this.MinMotorPower;

		return power;
	}

	private void UpdateDeltaAverage(long deltaDistanceSample) {
/*		
		this.deltaDistanceAverage += (deltaDistanceSample-averageDistanceSamples[averageDistanceUpdateIndex]);	
		averageDistanceSamples[averageDistanceUpdateIndex] = deltaDistanceSample;
		averageDistanceUpdateIndex++;
		if(averageDistanceUpdateIndex >= averageDistanceCount)
			averageDistanceUpdateIndex = 0;
*/
		this.deltaDistanceAverage = deltaDistanceSample;
	}

	public float getPSpeedCorr() {
		return pSpeedCorr;
	}

	public void setPSpeedCorr(float pSpeedCorr) {
		this.pSpeedCorr = pSpeedCorr;
	}
}
