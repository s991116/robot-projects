	 
import lejos.hardware.port.Port;
import lejos.hardware.sensor.SensorMode;
import lejos.hardware.sensor.UARTSensor;
	
public class ArduinoSensor extends UARTSensor implements SensorMode {
	 
	    private int sampleSize;
		private short[] samples;

		public ArduinoSensor(Port port, int sampleSize) {
	        super(port);
			this.sampleSize = sampleSize;
			samples = new short[sampleSize];
	    }
	 
	    @Override
	    public int sampleSize() {
	        return sampleSize;
	    }
	 
	    @Override
	    public void fetchSample(float[] sample, int offset) {
	    	port.getShorts(samples, 0 ,sampleSize);
	        for(int i=0;i<this.sampleSize;i++)
	        {
	        	sample[offset+i] = samples[i];        	
	        }
	    }
	 
	    @Override
	    public String getName() {
	        return "Smelly";
	    }
}