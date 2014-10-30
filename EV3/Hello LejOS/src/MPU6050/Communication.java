package MPU6050;

import lejos.hardware.sensor.I2CSensor;

public class Communication implements ICommunication{

	private I2CSensor i2csensor;

	public Communication(I2CSensor i2csensor)
	{
		this.i2csensor = i2csensor;
	}
	
	@Override
	public int[] ReadBytes(int register, int length) {
		
		byte[] buf = new byte[length];
		int[] bufInt = new int[length];
		i2csensor.getData(register, buf, length);
		
		for(int i=0; i< length; i++)
			bufInt[i] = buf[i] & (0xFF);
		
		return bufInt;
	}

	@Override
	public void WriteBytes(int register, int[] buffer, int length) {
		byte[] bufByte = new byte[length];
		for(int i=0; i< length; i++)
			bufByte[i] = (byte)buffer[i];
		
		i2csensor.sendData(register, bufByte, length);
	}
}
