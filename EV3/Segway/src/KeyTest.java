import lejos.hardware.Button;
import lejos.hardware.Key;
import lejos.hardware.KeyListener;

public class KeyTest implements KeyListener {

	public boolean quit = false;
	
	private int ledMode = 0;

	private int keyCode;
	
	public KeyTest(int keyCode)
	{
		this.keyCode = keyCode;
	}
	
	
	@Override
	public void keyPressed(Key k) {			
	}

	@Override
	public void keyReleased(Key k) {
		if(keyCode == Key.ESCAPE)
		  quit = true;
		else
			ledMode++;
		Button.LEDPattern(ledMode);
	}

}

