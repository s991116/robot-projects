import lejos.hardware.Button;
import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;
import lejos.hardware.motor.Motor;
import lejos.hardware.port.SensorPort;

public class Controller {

	private IState stateView;
	private boolean quitProgram = false;
	private Model model;

	public Controller()
	{
		LCD.drawString("*", 1,2);
		MPU6050GyroSensor gyroSensor = new MPU6050GyroSensor(SensorPort.S2);		
		LCD.drawString("**", 1,2);
		model = new Model(gyroSensor, Motor.C, Motor.B);
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
    		stateView.Display();
    		model.Balance();
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
		
	public void Adjust() {
		this.model.AdjustCenterValue();
	}
	
	public int getCenterValue() {
		return this.model.getCenterValue();
	}

	public int getCurrentValue() {
		return this.model.getCurrentPosition();
	}
}
