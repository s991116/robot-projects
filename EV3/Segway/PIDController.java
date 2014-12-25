
public class PIDController {
	
	private int pCorr;
	private int dCorr;
	
	private int privieusError = 0;
	private int maxCorrection;
	private int minCorrection;

	public PIDController(int pCorr, int dCorr, int maxCorrection, int minCorrection) {
		this.setPCorr(pCorr);
		this.setDCorr(dCorr);
		this.maxCorrection = maxCorrection;
		this.minCorrection = minCorrection;
	}
	
	public int getCorrection(int error) {
		int diffError = error - this.privieusError;
		this.privieusError  = error;
		
		int correction = getPCorr() * error + diffError * getDCorr();
		
		correction = limitCorrectionxtracted(correction);
		
		return correction;
	}

	private int limitCorrectionxtracted(int correction) {
		if(correction > maxCorrection)
			correction = maxCorrection;
		else if (correction < minCorrection)
			correction = minCorrection;
		return correction;
	}

	public int getPCorr() {
		return pCorr;
	}

	public void setPCorr(int pCorr) {
		this.pCorr = pCorr;
	}

	public int getDCorr() {
		return dCorr;
	}

	public void setDCorr(int dCorr) {
		this.dCorr = dCorr;
	}
}
