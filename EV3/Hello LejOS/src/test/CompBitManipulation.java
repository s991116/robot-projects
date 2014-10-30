package test;

import static org.junit.Assert.*;
import org.junit.Test;

import MPU6050.*;


public class CompBitManipulation {

	private static final int testRegister = 0;
	private CommunicationMock cMock = new CommunicationMock();
	private ComMPU6050C sut = new ComMPU6050C(cMock);

	@Test
	public void ReadByte() {
		
		int expectedValue = 123;
		cMock.SetData(new int[] {expectedValue});

		int result = sut.ReadByte(testRegister);
		
		assertEquals(expectedValue, result);
	}
	
	@Test
	public void ReadBits() {
	    // 01101001 read byte
	    // 76543210 bit numbers
	    //    xxx   args: bitStart=4, length=3
	    //    010   masked
	    //   -> 010 shifted
		
		int numberOfBitsToRead = 3;
		int bitStopPosition = 4;
		int byteToRead = 0x69; //0110 1001
        int expected = 0x02; //0000 0010

		cMock.SetData(new int[] {byteToRead});

		int result = sut.ReadBits(testRegister, bitStopPosition, numberOfBitsToRead);
		
		assertEquals(expected, result);
	}
	
	@Test
	public void ReadBit() {
                            //7654 3210
		int bit6Set = 0x5F; //0101 1111
		int bitPosition = 6;
		int expected = 0x40; //0100 0000

		cMock.SetData(new int[] {bit6Set});

		int result = sut.ReadBit(testRegister, bitPosition);
		
		assertEquals(expected, result);
	}
	
	@Test
	public void WriteBits() {
        
		int valueToWrite = 0x02; //0000 0010;
        int bitStopPosition = 4;
        int numberOfBitsToWrite = 3;
        int originalValue = 0xAF; //1010 1111
        
	//    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
		
		int expected = 0xAB;//  1010 1011
		
		cMock.SetData(new int[] {originalValue});
        				
		//writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {

		sut.WriteBits(testRegister, bitStopPosition, numberOfBitsToWrite, valueToWrite);
		
		int result = cMock.GetData()[0];
		assertEquals(expected, result);
	}
	
	@Test
	public void WriteBit() {
		int bitToWrite = 0x01; //0000 0001;
        int bitPosition = 5;
        int originalValue = 0x8F; //1000 1111
        		
		int expected = 0xAF;//  1010 1111
		
		cMock.SetData(new int[] {originalValue});

		sut.WriteBit(testRegister, bitPosition, bitToWrite);
		
		int result = cMock.GetData()[0];
		assertEquals(expected, result);
	}

}
