import lejos.hardware.port.Port;
import lejos.hardware.sensor.SensorMode;


public class GyroMode implements SensorMode {
	
	private short[] samples;
	private final int sampleSize = 2;
	private Port port;

	public GyroMode(Port port) {
		this.port = port;
		samples = new short[sampleSize()];
	}
	
    @Override
    public int sampleSize() {
        return sampleSize;
    }
 
    @Override
    public void fetchSample(float[] sample, int offset) {
        this.port.getShorts(samples, 0 ,sampleSize);
        for(int i=0;i<sampleSize();i++)
        {
        	sample[offset+i] = samples[i];        	
        }
    }
 
    @Override
    public String getName() {
        return "SimpleArduinoSensor";
    }
}
