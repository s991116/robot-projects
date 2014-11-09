import lejos.hardware.port.Port;
import lejos.hardware.sensor.SensorMode;
import lejos.hardware.sensor.UARTSensor;

public class SimpleArduinoSensor extends UARTSensor implements SensorMode {
 
	private short[] samples;
	private int sampleSize;
	
    public SimpleArduinoSensor(Port port, int sampleSize) {
        super(port);
		this.sampleSize = sampleSize;
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