import lejos.hardware.lcd.LCD;


public class Balance implements IState {

	private Controller controller;

	public Balance(Controller controller) {
		this.controller = controller;
	}

	@Override
	public void Display() {
		LCD.drawString("Balancing", 1,2);
		LCD.drawString("Center:", 1,4);
		LCD.drawInt(this.controller.getCenterValue(), 5, 8, 4);
		LCD.drawString("Current:", 1,5);
		LCD.drawInt(this.controller.getCurrentValue(), 5, 8, 5);
	}

	@Override
	public void keyReleased(int keyCode) {
	}

	@Override
	public int GetLEDPattern() {
		return LEDPattern.GreenBlink;
	}

}
