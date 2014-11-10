import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;


public class Balance implements IState {

	private Controller controller;

	public Balance(Controller controller) {
		this.controller = controller;
		this.controller.StartBalancing();
		
	}

	@Override
	public void Display() {
		LCD.drawString("Balancing", 1,1);
		LCD.drawString("Center:", 1,2);
		LCD.drawInt(this.controller.getCenterValue(), 5, 8, 2);
		LCD.drawString("Current:", 1,3);
		LCD.drawInt(this.controller.getCurrentValue(), 5, 8, 3);		
		LCD.drawString("PCorr:", 1,4);
		LCD.drawInt((int) (this.controller.getPValue()*10), 5, 8, 4);
		LCD.drawString("DCorr:", 1,5);
		LCD.drawInt((int) (this.controller.getDValue()*10), 5, 8, 5);
		LCD.drawString("Corr.:", 1,6);
		LCD.drawInt((int) (this.controller.getCorrection()*10), 5, 8, 6);
	}

	@Override
	public void keyReleased(int keyCode) {
		switch(keyCode)
		{
	  case Key.LEFT:
		this.controller.DCorrDown();
		break;

	  case Key.RIGHT:
		this.controller.DCorrUp();
		break;

	  case Key.UP:
		this.controller.PCorrUp();
		break;

	  case Key.DOWN:
		this.controller.PCorrDown();
		break;
		}
	}

	@Override
	public int GetLEDPattern() {
		return LEDPattern.GreenBlink;
	}

}
