import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;


public class Balance extends EV3View implements IState {

	private Controller controller;

	public Balance(Controller controller) {
		this.controller = controller;
		this.resetDisplay();
	}

	@Override
	public void Display() {		
		LCD.drawString("Balancing", 1,1);		
		DisplayBalanceSettings(this.controller);
	}

	@Override
	public void keyReleased(int keyCode) {
		AdjustBalanceModel(this.controller, keyCode);

		switch(keyCode)
		{
			case Key.ENTER:
				this.controller.PauseBalancing();
				this.controller.SwitchState(new Paused(this.controller));
		}
	}

	@Override
	public int GetLEDPattern() {
		return LEDPattern.GreenBlink;
	}

}
