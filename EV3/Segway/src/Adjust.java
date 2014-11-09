import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;


public class Adjust implements IState {

	private Controller controller;

	public Adjust(Controller controller) {
		this.controller = controller;
		
	}
	
	@Override
	public void Display() {
		LCD.drawString(" Position Robot", 1,2);
		LCD.drawString(" and press Enter", 1,4);		
	}
	
	@Override
	public void keyReleased(int keyCode) {
		switch(keyCode)
		{
		  case Key.ENTER:
			this.controller.Adjust();
			this.controller.SwitchState(new Balance(this.controller));
			break;
		}
	}

	@Override
	public int GetLEDPattern() {
		return LEDPattern.OrangeBlink;
	}

}
