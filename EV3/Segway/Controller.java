import lejos.hardware.Button;
import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;
import lejos.hardware.motor.NXTMotor;
import lejos.hardware.port.MotorPort;
import lejos.hardware.port.SensorPort;

public class Controller {

	private IState stateView;
	private boolean quitProgram = false;
	private BalanceModel model;
	private long time;
	private long updateTime;

	public Controller()
	{
		NXTMotor leftMotor = new NXTMotor(MotorPort.C);
		NXTMotor rightMotor = new NXTMotor(MotorPort.B);
		
		LCD.drawString("*", 1,2);
		//MPU6050GyroSensor gyroSensor = new MPU6050GyroSensor(SensorPort.S3);		
		ArduinoMPU6050 gyroSensor = new ArduinoMPU6050(SensorPort.S3);

		LCD.drawString("**", 1,2);
		model = new BalanceModel(leftMotor, rightMotor, gyroSensor);
		model.start();

		LCD.drawString("***", 1,2);		
		this.SwitchState(new CalibrateSegway(this));
		LCD.drawString("****", 1,2);
		AddKeyListeners();
		LCD.drawString("*****", 1,2);
	}

	private void AddKeyListeners() {
		Button.ESCAPE.addKeyListener(new QuitListener(this));
		Button.ENTER.addKeyListener(new ButtonListener(this, Key.ENTER));
		Button.DOWN.addKeyListener(new ButtonListener(this, Key.DOWN));
		Button.UP.addKeyListener(new ButtonListener(this, Key.UP));
		Button.LEFT.addKeyListener(new ButtonListener(this, Key.LEFT));
		Button.RIGHT.addKeyListener(new ButtonListener(this, Key.RIGHT));
	}

	public void Run() {
    	while(!quitProgram)
    	{
    		updateDisplay();
//    		model.Balance();
    	}
	}
		
	public void updateDisplay() {
		time = java.lang.System.currentTimeMillis();
		
		if(time - updateTime > 200)
		{
    		stateView.Display();
    		updateTime = time;			
		}
	}

	public IState getState() {
		return this.stateView;
	}
	
	public void SwitchState(IState state)
	{
		this.stateView = state;
		for(int y=1; y<=7; y++)
		{
			LCD.drawString("                 ", 1, y);			
		}
		Button.LEDPattern(state.GetLEDPattern());
	}
	
	public void QuitProgram() {
		this.quitProgram = true;
	}
		
	public void Calibrate() {
		this.model.CalibrateCenterValue();
	}
	
	public int getCenterValue() {
		return this.model.getCalibratedCenterAngle();
	}

	public int getCurrentValue() {
		return this.model.getCurrentAngel();
	}

	public void DCorrAdjust(int stepSize) {
		int adjust = this.model.getDCorr() + stepSize;
		this.model.setDCorr(adjust);		
	}

	public void PCorrAdjust(int stepSize) {
		int adjust = this.model.getPCorr() + stepSize;
		this.model.setPCorr(adjust);
	}

	public int getPValue() {
		return this.model.getPCorr();
	}

	public int getDValue() {
		return this.model.getDCorr();
	}

	public int getCorrection() {
		return this.model.getCorrection();
	}

	public double getCurrentAccelration() {
		return this.model.getCurrentAccelration();
	}

	public void PauseBalancing() {
		this.model.pauseBalancing();
	}
	
	public void StartBalancing() {
		this.model.startBalancing();
	}
	
	public long GetLoopRunTime() {
		return this.model.getCalculationTime();
	}

	public void AdjustCalibratedOffset(int offset) {
		this.model.AdjustCalibratedOffset(offset);
	}

	public int getPMotorCorr() {
		return this.model.getPMotorCorr();
	}

	public int getDMotorCorr() {
		return this.model.getDMotorCorr();
	}

}
