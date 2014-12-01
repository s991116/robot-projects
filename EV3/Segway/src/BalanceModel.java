import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import lejos.robotics.EncoderMotor;
import lejos.utility.Delay;

public class BalanceModel extends Thread {

	private final int AdjustLoopCount = 20;
	private static final int AdjustLoopDelay = 100;
	private long LoopTime;
	private int kAng;
	private int kAngRate;
	
	private int kIntAng = 0;//16;//13;//8;
	private int intAngleMax = 1200;
	
	private int calibartedCenterAngle;
	private int manualCenterAngle;
	private int CalibrationOffset;

	private MPU6050GyroSensor gyroSensor;
	private int currentPosition;
	private int currentAccelration;


	private int correction;
	private MotorSpeedControl speedControl;
	private long StartTime;
	private volatile boolean Paused;
	private long calculationTime;
	private int intAngle;
	private int angle;
	private int rate;
	private long CalculationTime;
	private int kPos;
	private int kPosRate;	
		
	public BalanceModel(EncoderMotor left, EncoderMotor right, MPU6050GyroSensor gyro) {
		this.gyroSensor = gyro;
				
		speedControl = new MotorSpeedControl(left, right);
		Paused = true;
		
		getPropertiesFromFile();	 		
		
		DataLogging.setSetting(this.kAng, this.kIntAng, this.kAngRate);
		this.setDaemon(true);
	}

	private void getPropertiesFromFile() {
		Properties properties = new Properties();
		InputStream input = null;
	 
		try {
	 
			input = new FileInputStream("config.properties");
	 
			// load a properties file
			properties.load(input);
	 
			// get the property value
			this.kAng = Integer.parseInt(properties.getProperty("angleFactor"));
			this.kAngRate = Integer.parseInt(properties.getProperty("angleRateFactor"));
			this.kPos = Integer.parseInt(properties.getProperty("positionFactor"));
			this.kPosRate = Integer.parseInt(properties.getProperty("speedFactor"));
			this.LoopTime = (long)Integer.parseInt(properties.getProperty("LoopTime"));
			this.speedControl.ResetPosition();
		} catch (IOException ex) {
			ex.printStackTrace();
		} finally {
			if (input != null) {
				try {
					input.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	public void CalibrateCenterValue() {
		int sampleSum = 0;
		for(int i=0; i< this.AdjustLoopCount; i++) {
			
			sampleSum += this.gyroSensor.getAngular();
			Delay.msDelay(AdjustLoopDelay);
		}
		manualCenterAngle = sampleSum / AdjustLoopCount;
		this.setCalibartedCenterAngle(this.manualCenterAngle);
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
			long StartCaluclationTime = System.currentTimeMillis();
			this.correction = GetCorrectionBalance();

			if(Paused)
			{
				this.speedControl.Stop();
			}
			else
			{
				try {
					this.speedControl.UpdateMotorSpeed(this.correction, 0, this.kPos, this.kPosRate);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				DataLogging.addData(new int[] {this.angle, this.rate, this.speedControl.getPosition(), this.speedControl.getSpeed(), (int)this.CalculationTime});
				
			}
			setCalculationTime(System.currentTimeMillis() - StartCaluclationTime);
			WaitForNextSample();
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
		getPropertiesFromFile();
		Paused = false;		
	}

	public long getCalculationTime() {
		return calculationTime;
	}

	private void setCalculationTime(long time) {
		calculationTime = time;
	}

	public void AdjustCalibratedOffset(int offset) {
		this.setCalibartedCenterAngle(this.getCalibratedCenterAngle() + offset);
	}
}