import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;


public class CalibrateSegway extends EV3View implements IState {

	private Controller controller;

	public CalibrateSegway(Controller controller) {
		this.controller = controller;
		this.resetDisplay();
	}

	@Override
	public void Display() {
		LCD.drawString("  Calibrate", 1,1);
		LCD.drawString(" press Enter", 1,3);
		LCD.drawString("  to start", 1,4);
		LCD.drawString(" Calibration", 1,5);
		
	}

	@Override
	public void keyReleased(int keyCode) {
		switch(keyCode)
		{
		  case Key.ENTER:
			this.controller.Calibrate();
			IState nextState = new Balance(this.controller);
			this.controller.SwitchState(nextState);
			this.controller.StartBalancing();
			break;
		}
	}

	@Override
	public int GetLEDPattern() {
		return LEDPattern.OrangeBlink;
	}

}
