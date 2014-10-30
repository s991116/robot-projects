package MPU6050;

public interface I2cCommunication {
	
	void WriteBits(int register, int bitStartPosition, int length, int value);

	void WriteBit(int register, int bitPosition, int data);

	int ReadBits(int register, int bitStartPosition, int length);

	int ReadBit(int register, int bitPosition);
			
	int ReadByte(int register);

	void WriteByte(int register, int bank);

	int[] ReadBytes(int register, int length);

	void WriteWord(int register, int data);
	
	void WriteBytes(int register, int length, int[] data);

}
