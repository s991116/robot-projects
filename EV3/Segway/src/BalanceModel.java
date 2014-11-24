import lejos.robotics.EncoderMotor;
import lejos.utility.Delay;

public class BalanceModel extends Thread {

	private final int AdjustLoopCount = 20;
	private static final int AdjustLoopDelay = 100;
	private static final long LoopTime = 12;
	private int kAng = 20;//20;
	
	private int kAngRate = 40;//60;
	private int kIntAng = 0;//16;//13;//8;
	private int intAngleMax = 1200;
	
	private int calibartedCenterAngle;
	private MPU6050GyroSensor gyroSensor;
	private int currentPosition;
	private int currentAccelration;


	private int correction;
	private MotorSpeedControl speedControl;
	private long StartTime;
	private volatile boolean Paused;
	private long LoopRunTime;
	private int intAngle;
	private int angle;
	private int rate;
	private long CalculationTime;
	
		
	public BalanceModel(EncoderMotor left, EncoderMotor right, MPU6050GyroSensor gyro) {
		this.gyroSensor = gyro;
		
		speedControl = new MotorSpeedControl(left, right);
				
		Paused = true;
		
		DataLogging.addSetting(this.kAng, this.kIntAng, this.kAngRate);
		
		this.setDaemon(true);
	}
	
	public void CalibrateCenterValue() {
		int sampleSum = 0;
		for(int i=0; i< this.AdjustLoopCount; i++) {
			
			sampleSum += this.gyroSensor.getAngular();
			Delay.msDelay(AdjustLoopDelay);
		}
		this.setCalibartedCenterAngle(sampleSum / AdjustLoopCount);
		this.speedControl.ResetPosition();
	}
	
	public int getCalibratedCenterAngle() {
		return calibartedCenterAngle;
	}

	private void setCalibartedCenterAngle(int angle) {
		this.calibartedCenterAngle = angle;
	}

	public int getCurrentAngel() {
		return this.angle;
	}

	public int getCurrentAccelration() {
		return currentAccelration;
	}

	public void run() {
		StartTime = System.currentTimeMillis();
		
		while(true) {
			long StartLoopRunTime = System.currentTimeMillis();
			this.correction = GetCorrectionBalance();

			if(Paused)
			{
				this.speedControl.Stop();
			}
			else
			{
				try {
					this.speedControl.UpdateMotorSpeed(this.correction, 0);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				DataLogging.addData(new int[] {this.angle, this.rate, this.speedControl.getPosition(), this.speedControl.getSpeed(), (int)this.CalculationTime});
				
			}
			WaitForNextSample();
			setLoopRunTime(System.currentTimeMillis() - StartLoopRunTime);
		}
	}

	private int GetCorrectionBalance() {
		
        // Calculate the PID value
				
		currentPosition = this.gyroSensor.getAngular();
		angle = currentPosition - this.getCalibratedCenterAngle();
		rate = this.gyroSensor.getAngularVelocity();
        intAngle += angle;
        intAngle = limit(intAngle, this.intAngleMax);
        
        int corr = kAng*angle - kAngRate*rate + kIntAng*intAngle;
		
		return corr;
	}

	private int limit(int corr, int maxValue) {
		if(corr > maxValue)
			corr = maxValue;
		else if(corr < -maxValue)
			corr = -maxValue;
		return corr;
	}
	
	private void WaitForNextSample() {
		long CurrentTime = System.currentTimeMillis();
		CalculationTime = (CurrentTime - StartTime);
		long WaitTime = (LoopTime - CalculationTime);
		if(WaitTime > 0)
		{
			try {
				Thread.sleep(WaitTime);
			} catch (InterruptedException e) {}				
		}
		StartTime = System.currentTimeMillis();
	}

	
	public int getDCorr() {
		return this.kAngRate;
	}

	public void setDCorr(int d_CORR) {
		this.kAngRate = d_CORR;
	}

	public int getICorr() {
		return this.kIntAng;
	}

	public void setICorr(int I_CORR) {
		this.kIntAng = I_CORR;
	}
	
	public int getPCorr() {
		return this.kAng;
	}

	public void setPCorr(int p_CORR) {
		this.kAng = p_CORR;
	}

	public int getCorrection() {
		return this.correction;
	}

	public void pauseBalancing() {
		Paused = true;
		DataLogging.WriteLogToFile("GyroData.txt");
	}

	public void startBalancing() {
		Paused = false;		
	}

	public long getLoopRunTime() {
		return LoopRunTime;
	}

	private void setLoopRunTime(long loopRunTime) {
		LoopRunTime = loopRunTime;
	}
}