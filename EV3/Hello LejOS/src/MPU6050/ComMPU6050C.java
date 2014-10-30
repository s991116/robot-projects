package MPU6050;

public class ComMPU6050C implements I2cCommunication
{

	private ICommunication Communication;
	
	public ComMPU6050C(ICommunication communication)
	{
		Communication = communication;
	}
	
	/** Read a single bit from an 8-bit device register.
	 * @param regAddr Register regAddr to read from
	 * @param bitNum Bit position to read (0-7)
	 * @return 0 if bit is 0 else greater then 0
	 */
	public int ReadBit(int register, int bitPosition) {
	    int b = ReadByte(register);
	    return (b & (1 << bitPosition));
	}

	/** Write multiple bits in an 8-bit device register.
	 * @param Register to write to
	 * @param bitStopPosition Last bit position to write (0-7)
	 * @param length Number of bits to write (not more than 8)
	 * @param value Right-aligned value to write
	 */
	@Override
	public void WriteBits(int register, int bitStopPosition, int length, int value) {
	    int data = ReadByte(register);

		int bitStartPosition = bitStopPosition - length + 1;
	    
        value = value << bitStartPosition; // shift data into correct position
        int mask = 	CreateMask(bitStartPosition, length); 
        value = value & mask;
        
        int inverseMask = (~mask) & 0xFF;
        
        data = data & inverseMask; // zero all non-important bits in data
        data = data | value; // combine data with existing byte
        WriteByte(register, data);
	}
	
	/** write a single bit in an 8-bit device register.
	 * @param Register to write to
	 * @param Bit position to write (0-7)
	 * @param New bit value to write
	 * @return Status of operation (true = success)
	 */
	@Override
	public void WriteBit(int register, int bitPosition, int value) {
	    int data = ReadByte(register); //bit 00000000 00000000 00000000 XXXXXXXX
	    
	    data = (value != 0) ? (data | (1 << bitPosition)) : (data & ~(1 << bitPosition));
	    
	    WriteByte(register, data);
	}
	
	/** Read multiple bits from an 8-bit device register.
	 * @param Register regAddr to read from
	 * @param bitStopPosition Last bit position to read (0-7)
	 * @param length Number of bits to read (not more than 8)
	 * @return bites read
	 */
	@Override
	public int ReadBits(int register, int bitStopPosition, int length) {
		int data = ReadByte(register);
		int bitStartPosition = bitStopPosition - length + 1;
        int mask = CreateMask(bitStartPosition, length);
		
        data &= mask;
        data = data >> bitStartPosition;
        return data;
	}

	private int CreateMask(int bitStartPosition, int length) 
	{
	  //length = 3 (1-8), startbit = 4 (0-7)
      int mask = 0xFF;                             //00000000 11111111
      mask = mask << (8-length);                   //00011111 11100000
      mask = mask & 0xFF;                          //00000000 11100000
      mask = mask >> ((8-length)-bitStartPosition);//00000000 01110000
      return mask;
    }

    /** Read single byte from an 8-bit device register.
     * @param Register to read from
     * @return data
     */
	@Override
	public int ReadByte(int register) {
		int[] data = Communication.ReadBytes(register, 1);
		return data[0];
	}

    /** Write single byte to an 8-bit device register.
     * @param Register to write to
     * @param data to write
     */
	@Override
	public void WriteByte(int register, int data) {
		int[] buffer = new int[1];
		buffer[0] = data;
		Communication.WriteBytes(register, buffer, 1);
	}

	/** Read multiple bytes from an 8-bit device register.
	 * @param regAddr First register regAddr to read from
	 * @param length Number of bytes to read
	 * @return bytes read
	 */
	@Override
	public int[] ReadBytes(int register, int length) {
		return Communication.ReadBytes(register, length);
	}

	@Override
	public void WriteWord(int register, int data) {
		int[] buffer = new int[2];
		buffer[0] = data & 0xFF;
		buffer[1] = (data >> 8) & 0xFF;
		Communication.WriteBytes(register, buffer, 2);
	}

	@Override
	public void WriteBytes(int register, int length, int[] data) {
		Communication.WriteBytes(register, data, length);
	}
}
