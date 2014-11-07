import lejos.hardware.Button;
import lejos.hardware.lcd.LCD;
import lejos.hardware.port.SensorPort;
import lejos.utility.Delay;
 
public class Main {
 
    public static void main(String[] args) {
    	
    	LCD.drawString("Starting.",0,2);
        MPU6050GyroSensor gyroSensor = new MPU6050GyroSensor(SensorPort.S2);
        int sampleSize = gyroSensor.sampleSize();
		float[] sample = new float[sampleSize];
        LCD.drawString("Yaw:   ", 0, 3);
        LCD.drawString("Pitch: ", 0, 4);
        LCD.drawString("Roll:  ", 0, 5);
                
        while(Button.ESCAPE.isUp()) {
        	gyroSensor.fetchSample(sample,0);
       	
        	for(int i=0; i<sampleSize; i++)
        	{
                LCD.drawInt((int) sample[i],6,8,3+i);	
        	}
            Delay.msDelay(300);
        }   
        gyroSensor.close();
    }
}