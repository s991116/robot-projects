import lejos.hardware.Button;
import lejos.hardware.port.SensorPort;
import lejos.utility.Delay;
 
public class ArduinoSensorTest {

    public static void main(String[] args) {
    	ArduinoSensor arduinoSensor = new ArduinoSensor(SensorPort.S3, 2);
        float[] sample = new float[arduinoSensor.sampleSize()];
         
        while(Button.ESCAPE.isUp()) {
        	Delay.msDelay(200);
            arduinoSensor.fetchSample(sample,0);
            System.out.println("X: " + sample[0] + " , " + sample[1]);
        }   
        arduinoSensor.close();
    }
}
