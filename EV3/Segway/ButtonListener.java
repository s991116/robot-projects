import lejos.hardware.Key;
import lejos.hardware.KeyListener;


public class ButtonListener implements KeyListener {

	private int keyCode;
	private Controller controller;

	public ButtonListener(Controller controller, int keyCode) {

		this.controller = controller;
		this.keyCode = keyCode;
	}

	@Override
	public void keyPressed(Key k) {
	}

	@Override
	public void keyReleased(Key k) {
		this.controller.getState().keyReleased(this.keyCode);
	}

}
