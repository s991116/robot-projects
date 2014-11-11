import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;

public class Paused extends EV3View implements IState {

	private Controller controller;

	public Paused(Controller controller) {
		this.controller = controller;
		this.resetDisplay();
	}

	@Override
	public void keyReleased(int keyCode) {

		AdjustBalanceModel(this.controller, keyCode);

		switch(keyCode)
		{
		  case Key.ENTER:
			IState nextState = new Balance(this.controller);
			this.controller.SwitchState(nextState);
			this.controller.StartBalancing();
			break;
		}
	}

	@Override
	public void Display() {
		LCD.drawString("   Paused", 1,1);
		DisplayBalanceSettings(this.controller);
	}

	@Override
	public int GetLEDPattern() {
		return LEDPattern.Green;
	}
}
