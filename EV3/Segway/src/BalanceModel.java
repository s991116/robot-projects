import lejos.hardware.motor.NXTRegulatedMotor;
import lejos.utility.Delay;

public class BalanceModel {

	private static final int Roll = 1;
	private static final int RollAccelration = 4;

	private final int AdjustLoopCount = 20;
	private static final int AdjustLoopDelay = 100;

	private int centerValue;
	private int sampleSize;
	private float[] sample;
	private SimpleArduinoSensor gyroSensor;
	private NXTRegulatedMotor leftMotor;
	private NXTRegulatedMotor rightMotor;
	private int currentPosition;
	private int currentAccelration;

	private boolean centerAdjusted = false;
	private PIDController pidController;

	private int MIN_CORRECTION;
	private int MAX_CORRECTION;
	private int D_CORR = 4;
	private int P_CORR = 10;
	private int correction;
	
		
	public BalanceModel(SimpleArduinoSensor gyroSensor, NXTRegulatedMotor leftMotor, NXTRegulatedMotor rightMotor) {
		this.gyroSensor = gyroSensor;
		this.leftMotor = leftMotor;
		this.rightMotor = rightMotor;
		this.sampleSize = this.gyroSensor.sampleSize();
		this.sample = new float[this.sampleSize];
				
		MAX_CORRECTION = 1000;
		MIN_CORRECTION = -1000;

		pidController = new PIDController(getPCorr(),getDCorr(),MAX_CORRECTION,MIN_CORRECTION);
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

	public int getCurrentPosition() {
		return currentPosition;
	}

	public int getCurrentAccelration() {
		return currentAccelration;
	}

	public void Balance() {

		if(centerAdjusted)
		{
			UpdatePosition();
			int error = (currentPosition - centerValue);

			this.correction = this.pidController.getCorrection(error);
			
			if(this.correction < 0)
			{
				leftMotor.forward();
				rightMotor.forward();
			}
			else
			{
				leftMotor.backward();
				rightMotor.backward();				
			}
			
			int newSpeedLeft = this.correction;
			int newSpeedRight = this.correction;
			
			leftMotor.setSpeed(newSpeedLeft);
			rightMotor.setSpeed(newSpeedRight);					
		}
	}

	private void UpdatePosition() {
		this.gyroSensor.fetchSample(this.sample,0);
		currentPosition = (int) this.sample[Roll];
		currentAccelration = (int) this.sample[RollAccelration];

	}

	public int getDCorr() {
		return D_CORR;
	}

	public void setDCorr(int d_CORR) {
		D_CORR = d_CORR;
	}

	public int getPCorr() {
		return P_CORR;
	}

	public void setPCorr(int p_CORR) {
		P_CORR = p_CORR;
	}

	@Override
    protected void finalize() throws Throwable {
		gyroSensor.close();
	}

	public int getCorrection() {
		return this.correction;
	}
	
}