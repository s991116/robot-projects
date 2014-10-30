package test;

import MPU6050.*;

public class CommunicationMock implements ICommunication{

	private int[] data;
	
	public void SetData(int[] data)
	{
		this.data = data;
	}

	public int[] GetData()
	{
		return this.data;
	}

	@Override
	public int[] ReadBytes(int register, int length) {
		int[] result = new int[length];
		for(int i=0; i<length; i++)
		{
			result[i] = data[i];
		}
		return result;
	}

	@Override
	public void WriteBytes(int register, int[] buffer, int length) {
		data = new int[length];
		for(int i=0; i<length; i++)
		{
			data[i] = buffer[i];
		}
	}
}
