import lejos.robotics.EncoderMotor;
import lejos.utility.Delay;


public class BalanceModel extends Thread {


	private final int AdjustLoopCount = 20;
	private static final int AdjustLoopDelay = 100;
	private static final long LoopTime = 10;

	private int calibartedCenterAngle;
	private MPU6050GyroSensor gyroSensor;
	private int currentPosition;
	private int currentAccelration;

	private int MIN_CORRECTION;
	private int MAX_CORRECTION;
	private double D_CORR = 2;
	private double P_CORR = 1.5;
	private float speedCorr = 3;

	private int correction;
	private int sampleTimeInMS = 50;
	private MotorSpeedControl speedControl;
	private long StartTime;
	
		
	public BalanceModel(EncoderMotor left, EncoderMotor right, MPU6050GyroSensor gyro) {

		this.gyroSensor = gyro;
		
		speedControl = new MotorSpeedControl(left, right, sampleTimeInMS, getSpeedCorr());
		
		MAX_CORRECTION = 1000;
		MIN_CORRECTION = -1000;
		
		this.setDaemon(true);
	}
	
	public void CalibrateCenterValue() {
		int sampleSum = 0;
		for(int i=0; i< this.AdjustLoopCount; i++) {
			
			sampleSum += this.gyroSensor.getAngular();
			Delay.msDelay(AdjustLoopDelay);
		}
		this.setCalibartedCenterAngle(sampleSum / AdjustLoopCount);
	}
	
	public int getCalibartedCenterAngle() {
		return calibartedCenterAngle;
	}

	private void setCalibartedCenterAngle(int angle) {
		this.calibartedCenterAngle = angle;
	}

	public int getCurrentPosition() {
		return currentPosition;
	}

	public int getCurrentAccelration() {
		return currentAccelration;
	}

	public void run() {
		StartTime = System.currentTimeMillis();

		while(true) {
			
			this.correction = GetCorrectionBalance();
			this.speedControl.UpdateMotorSpeed(correction);
			WaitForNextSample();
		}
	}

	private int GetCorrectionBalance() {
		currentPosition = this.gyroSensor.getAngular();
		int anglePositionError = currentPosition - this.getCalibartedCenterAngle();
		
		int corr = (int) (anglePositionError * this.P_CORR + this.gyroSensor.getAngularVelocity() * this.D_CORR);
		
		if(corr > this.MAX_CORRECTION)
			corr = this.MAX_CORRECTION;
		else if(corr < this.MIN_CORRECTION)
			corr = this.MIN_CORRECTION;
		
		return corr;
	}
	
	private void WaitForNextSample() {
		long CurrentTime = System.currentTimeMillis();
		long WaitTime = (LoopTime - CurrentTime - StartTime);
		if(WaitTime > 0)
		{
			try {
				Thread.sleep(WaitTime);
			} catch (InterruptedException e) {}				
		}
		StartTime = System.currentTimeMillis();
	}

	
	public double getDCorr() {
		return D_CORR;
	}

	public void setDCorr(double d_CORR) {
		D_CORR = d_CORR;
	}

	public double getPCorr() {
		return P_CORR;
	}

	public void setPCorr(double p_CORR) {
		P_CORR = p_CORR;
	}

	public int getCorrection() {
		return this.correction;
	}

	public float getSpeedCorr() {
		return speedCorr;
	}

	public void setSpeedCorr(float speedCorr) {
		this.speedCorr = speedCorr;
	}
	
}