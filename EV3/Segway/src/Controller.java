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
//	private Segoway model;
	private long time;
	private long updateTime;

	public Controller()
	{
		NXTMotor leftMotor = new NXTMotor(MotorPort.C);
		NXTMotor rightMotor = new NXTMotor(MotorPort.B);
		
		LCD.drawString("*", 1,2);
		MPU6050GyroSensor gyroSensor = new MPU6050GyroSensor(SensorPort.S2);		

		LCD.drawString("**", 1,2);
		model = new BalanceModel(leftMotor, rightMotor, gyroSensor);
//		model = new Segoway(leftMotor, rightMotor, gyroSensor, 5.6);		


		LCD.drawString("***", 1,2);		
		this.SwitchState(new Paused(this));
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
		return this.model.getCalibartedCenterAngle();
	}

	public int getCurrentValue() {
		return this.model.getCurrentPosition();
	}

	public void DCorrDown() {
		double adjust = this.model.getDCorr()-0.1;
		this.model.setDCorr(adjust);		
	}

	public void DCorrUp() {
		double adjust = this.model.getDCorr()+0.1;
		this.model.setDCorr(adjust);
	}

	public void PCorrUp() {
		double adjust = this.model.getPCorr()+0.1;
		this.model.setPCorr(adjust);
	}

	public void PCorrDown() {
		double adjust = this.model.getPCorr()-0.1;
		this.model.setPCorr(adjust);
	}

	public double getPValue() {
		return this.model.getPCorr();
	}

	public double getDValue() {
		return this.model.getDCorr();
	}

	public double getCorrection() {
		return this.model.getCorrection();
	}

	public double getCurrentAccelration() {
		return this.model.getCurrentAccelration();
	}

	public void StartBalancing() {
		this.model.start();
		
	}
}