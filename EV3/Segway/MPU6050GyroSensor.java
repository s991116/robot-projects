import lejos.hardware.port.Port;

public class MPU6050GyroSensor {
 
    private static final int ROLL = 2;//1;
	private static final int ROLL_ACCELRATION = 5;//4;
	private static final int SAMPLE_SIZE = 6;
	private SimpleArduinoSensor sensor;
	private float[] sample = new float[SAMPLE_SIZE];

    
	public MPU6050GyroSensor(Port port) {
    	sensor = new SimpleArduinoSensor(port, SAMPLE_SIZE);
    }
 
	public void recalibrateOffset() {
		
	}

	public int getAngularVelocity() {
//		sensor.fetchSample(sample, 0);
		return (int)(sample[ROLL_ACCELRATION]);
	}


	public int getAngular() {
		sensor.fetchSample(sample, 0);
		return (int)(sample[ROLL]);
	}
}