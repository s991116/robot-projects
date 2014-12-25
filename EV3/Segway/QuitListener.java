import lejos.hardware.Key;
import lejos.hardware.KeyListener;


public class QuitListener implements KeyListener {

	private Controller controller;

	public QuitListener(Controller controller) {
		this.controller = controller;
	}

	@Override
	public void keyPressed(Key k) {
	}

	@Override
	public void keyReleased(Key k) {
		this.controller.QuitProgram();
	}

}
