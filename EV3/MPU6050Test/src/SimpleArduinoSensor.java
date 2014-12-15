import lejos.hardware.port.Port;
import lejos.hardware.sensor.SensorMode;
import lejos.hardware.sensor.UARTSensor;

public class SimpleArduinoSensor extends UARTSensor {
 
	
    public SimpleArduinoSensor(Port port, int sampleSize) {
        super(port);
        setModes(new SensorMode[]{new GyroMode(port)});
    } 
}