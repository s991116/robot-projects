import lejos.hardware.port.Port;
import lejos.hardware.sensor.SensorMode;
import lejos.hardware.sensor.UARTSensor;


public class GyroMode extends UARTSensor implements SensorMode {
	
	private short[] samples;
	private final int sampleSize = 2;

	public GyroMode(Port port) {
		super(port);
		samples = new short[sampleSize()];
	}
	
    @Override
    public int sampleSize() {
        return sampleSize;
    }
 
    @Override
    public void fetchSample(float[] sample, int offset) {
        port.getShorts(samples, 0 ,sampleSize);
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
