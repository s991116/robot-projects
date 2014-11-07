import lejos.hardware.port.Port;
import lejos.hardware.sensor.SensorMode;
import lejos.hardware.sensor.UARTSensor;

public class MPU6050GyroSensor extends UARTSensor implements SensorMode {
 
	private static final short _SampleSize = 3;
	private short[] gyro = new short[sampleSize()];
	
    public MPU6050GyroSensor(Port port) {
        super(port);
    }
 
    @Override
    public int sampleSize() {
        return _SampleSize;
    }
 
    @Override
    public void fetchSample(float[] sample, int offset) {
        port.getShorts(gyro, 0 ,_SampleSize);
        for(int i=0;i<sampleSize();i++)
        {
        	sample[offset+i] = gyro[i];        	
        }
    }
 
    @Override
    public String getName() {
        return "Gyro";
    }
}