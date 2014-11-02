package GyroSensor;

import lejos.hardware.port.Port;
import lejos.hardware.sensor.SensorMode;
import lejos.hardware.sensor.UARTSensor;

public class NoseSensor extends UARTSensor implements SensorMode {
 
    public NoseSensor(Port port) {
        super(port);
    }
 
    @Override
    public int sampleSize() {
        return 1;
    }
 
    @Override
    public void fetchSample(float[] sample, int offset) {
        sample[offset] = port.getShort();   
    }
 
    @Override
    public String getName() {
        return "ArduinoTest";
    }
}