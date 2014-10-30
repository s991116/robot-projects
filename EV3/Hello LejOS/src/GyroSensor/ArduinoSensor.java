package GyroSensor;

import lejos.hardware.port.Port;
import lejos.hardware.sensor.SensorMode;
import lejos.hardware.sensor.UARTSensor;
import lejos.robotics.SampleProvider;

public class ArduinoSensor extends UARTSensor {
	 private static final long SWITCHDELAY = 200;
	 
	 public ArduinoSensor(Port port) {
	   super(port);
	   setModes(new SensorMode[] { new RawMode(), new HeadingMode()});
	 }
	 
	 private class RawMode implements SensorMode {
	   private static final int MODE = 0;
	   private short[] raw = new short[sampleSize()];
	 
	   @Override
	   public int sampleSize() {
	     return 3;
	   }
	 
	   @Override
	   public void fetchSample(float[] sample, int offset) {
	     switchMode(MODE, SWITCHDELAY);
	     port.getShorts(raw,0,sampleSize());
	     for(int i=0;i<sampleSize();i++) 
	    	 sample[offset+i] = raw[i];
	   }
	 
	   @Override
	   public String getName() {
	     return "Raw";
	   }
	 }
	 
	 public SampleProvider getRawMode() {
	   return getMode(0);
	 }
	 
	 private class HeadingMode implements SensorMode {
	   private static final int MODE = 1;
	   private int heading;
	 
	   @Override
	   public int sampleSize() {
	     return 1;
	   }
	 
	   @Override
	   public void fetchSample(float[] sample, int offset) {
	     switchMode(MODE, SWITCHDELAY);
	     heading = port.getShort();
	     sample[offset] = heading;
	   }
	 
	   @Override
	   public String getName() {
	     return "Heading";
	   }
	 }
	 
	 public SampleProvider getHeadingMode() {
	   return getMode(1);
	 }
	}