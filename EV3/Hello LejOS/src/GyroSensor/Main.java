package GyroSensor;
import MPU6050.GravetyPoint;
import lejos.hardware.Button;
import lejos.hardware.lcd.LCD;
import lejos.hardware.port.SensorPort;
import lejos.robotics.SampleProvider;
import lejos.utility.Delay;


import lejos.hardware.Button;
import lejos.hardware.port.SensorPort;
 
public class Main {
 
    public static void main(String[] args) {
        NoseSensor nose = new NoseSensor(SensorPort.S1);
        float[] sample = new float[nose.sampleSize()];
        LCD.drawString("SensorValue: ", 0, 3);
        
        while(Button.ESCAPE.isUp()) {
            nose.fetchSample(sample,0);
            LCD.drawInt((int)sample[0],0,4);
            Delay.msDelay(500);
        }   
        nose.close();
    }
}

/*
public class Main {

   public static void main(String[] args) throws Throwable {    
	   //ArduinoSensor sensor = new ArduinoSensor(SensorPort.S2);
       ArduinoSensor sensor = new ArduinoSensor(SensorPort.S2);
	   SampleProvider raw = sensor.getRawMode();
       SampleProvider heading = sensor.getHeadingMode();
       float[] sample = new float[raw.sampleSize()];

       float[] sample = new float[raw.sampleSize()];

       float[] degrees = new float[1];
       LCD.drawString("Raw:", 3, 0);
       LCD.drawString("X:",0, 3);
       LCD.drawString("Y:",0, 4);
       LCD.drawString("Z:",0, 5);
       LCD.drawString("Heading:", 0, 7);

       while(Button.ESCAPE.isUp()) {
           raw.fetchSample(sample,0);
    	   
           for (int i=0;i<3;i++) 
             LCD.drawInt((int)sample[i],5,4,3+i);
           heading.fetchSample(degrees, 0);
           LCD.drawInt((int) degrees[0], 3, 10, 7);
           Delay.msDelay(1000);
       }
       sensor.close();     
  }
}
*/