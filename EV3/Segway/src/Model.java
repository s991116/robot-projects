import lejos.hardware.motor.Motor;
import lejos.hardware.motor.NXTRegulatedMotor;
import lejos.utility.Delay;


public class Model {

	private static final int Roll = 1;
	private final int AdjustLoopCount = 20;
	private static final int AdjustLoopDelay = 100;

	private int centerValue;
	private int sampleSize;
	private float[] sample;
	private MPU6050GyroSensor gyroSensor;
	private NXTRegulatedMotor leftMotor;
	private NXTRegulatedMotor rightMotor;
	private int currentPosition;
	private boolean centerAdjusted = false;
	
	public Model(MPU6050GyroSensor gyroSensor, NXTRegulatedMotor leftMotor, NXTRegulatedMotor rightMotor) {
		this.gyroSensor = gyroSensor;
		this.leftMotor = leftMotor;
		this.rightMotor = rightMotor;
		this.sampleSize = this.gyroSensor.sampleSize();
		this.sample = new float[this.sampleSize];
	}
	
	public void AdjustCenterValue() {
		int sampleSum = 0;
		for(int i=0; i< this.AdjustLoopCount; i++) {
			this.gyroSensor.fetchSample(this.sample,0);
			sampleSum += this.sample[Roll];
			Delay.msDelay(AdjustLoopDelay);
		}
		this.setCenterValue(sampleSum / AdjustLoopCount);
		centerAdjusted = true;
	}
	
	public int getCenterValue() {
		return centerValue;
	}

	private void setCenterValue(int centerValue) {
		this.centerValue = centerValue;
	}

	@Override
    protected void finalize() throws Throwable {
		gyroSensor.close();
	}

	public int getCurrentPosition() {
		return currentPosition;
	}

	public void Balance() {

		if(centerAdjusted)
		{
			UpdatePosition();
			int error = (currentPosition - centerValue);

			if(error < 0)
			{
				leftMotor.forward();
				rightMotor.forward();
			}
			else
			{
				leftMotor.backward();
				rightMotor.backward();				
			}
			
			int factor = 4;
			int newSpeedLeft = error*factor;
			int newSpeedRight = error*factor;
			
			leftMotor.setSpeed(newSpeedLeft);
			rightMotor.setSpeed(newSpeedRight);					
		}
	}

	private void UpdatePosition() {
		this.gyroSensor.fetchSample(this.sample,0);
		currentPosition = (int) this.sample[Roll];
	}
}