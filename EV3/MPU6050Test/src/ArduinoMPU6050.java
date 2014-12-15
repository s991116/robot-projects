import lejos.hardware.port.Port;


public class ArduinoMPU6050 {

	private SimpleArduinoSensor sensor;
	private static final int SAMPLE_SIZE = 2;
	private float[] sample = new float[SAMPLE_SIZE];

	public ArduinoMPU6050(Port port) {
		sensor = new SimpleArduinoSensor(port, SAMPLE_SIZE);
	}
	
	public GyroData ReadGyro() {
		
		sensor.fetchSample(sample, 0);		
		return new GyroData((int)sample[0], (int)sample[1]);				
	}
	
}
