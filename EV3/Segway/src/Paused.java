import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;

public class Paused implements IState {

	private Controller controller;

	public Paused(Controller controller) {
		this.controller = controller;
	}

	@Override
	public void keyReleased(int keyCode) {

		switch(keyCode)
		{
		  case Key.ENTER:
			IState nextState = new CalibrateSegway(this.controller);
			this.controller.SwitchState(nextState);
			break;
		}
	}

	@Override
	public void Display() {
		LCD.drawString("   Press Enter", 1,2);
		LCD.drawString("    to begin"  , 1,4);		
		LCD.drawString("   Calibration." , 1,6);
	}

	@Override
	public int GetLEDPattern() {
		return LEDPattern.Green;
	}
}
