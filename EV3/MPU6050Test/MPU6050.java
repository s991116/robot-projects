import java.nio.ByteBuffer;
import lejos.hardware.port.Port;
import lejos.hardware.sensor.I2CSensor;
import lejos.hardware.sensor.SensorConstants;
import lejos.utility.Delay;


public class MPU6050 {

	private I2CSensor gyro;
	
	private byte[] i2cBuffer = new byte[6];
	private ByteBuffer i2cDataBufer = ByteBuffer.wrap(i2cBuffer);

	public MPU6050(Port port) {
	     gyro = new I2CSensor(port, 0x68<<1, SensorConstants.TYPE_LOWSPEED);
	      	      
	      gyro.getData(0x75, i2cBuffer, 0, 1);
	      	      
	      Delay.msDelay(5);
	      gyro.sendData(0x6b, (byte) 0x03); // set z axis as clock source
	      gyro.sendData(0x1a, (byte) 0x00); // disables FSYNC, configures DPLF
	      gyro.sendData(0x1b, (byte) 0x18);   //0b11000 set range to 2000*2
	      
	      Delay.msDelay(100);
	      gyro.sendData(0x6b, (byte) 0x00); // reset all register to default
	}
	
	public int ReadAngle() {
		gyro.getData(0x43, i2cBuffer,0, 2); // read only gyro data
		
		return i2cDataBufer.getShort(0);
	}
}
