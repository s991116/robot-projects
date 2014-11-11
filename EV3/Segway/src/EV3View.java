import lejos.hardware.Key;
import lejos.hardware.lcd.LCD;


public class EV3View {
	private static final int AdjustmentViewFactor = 100;
	private static final double AdjustStepSize = 0.02;

	public void resetDisplay() {
		for(int y=1; y<8; y++)
			LCD.clear(1, y, 20);
	}
	
	protected void DisplayBalanceSettings(Controller c) {
		LCD.drawString("Center:", 1,2);
		LCD.drawInt(c.getCenterValue(), 5, 8, 2);
		LCD.drawString("Current:", 1,3);
		LCD.drawInt(c.getCurrentValue(), 5, 8, 3);		
		LCD.drawString("PCorr:", 1,4);
		LCD.drawInt((int) (c.getPValue()*AdjustmentViewFactor), 5, 8, 4);
		LCD.drawString("DCorr:", 1,5);
		LCD.drawInt((int) (c.getDValue()*AdjustmentViewFactor), 5, 8, 5);
		LCD.drawString("Corr.:", 1,6);
		LCD.drawInt((int) (c.getCorrection()), 5, 8, 6);
	}
	
	protected void AdjustBalanceModel(Controller c, int keyCode) {
		switch(keyCode)
		{
			case Key.LEFT:
				c.DCorrAdjust(-AdjustStepSize);
				break;

			case Key.RIGHT:
				c.DCorrAdjust(AdjustStepSize);
				break;	

			case Key.UP:
				c.PCorrAdjust(AdjustStepSize);
				break;

			case Key.DOWN:
				c.PCorrAdjust(-AdjustStepSize);
				break;
		}
	}
}
