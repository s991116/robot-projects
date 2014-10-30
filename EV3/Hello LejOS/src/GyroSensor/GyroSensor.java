package GyroSensor;

import MPU6050.ComMPU6050C;
import MPU6050.Communication;
import MPU6050.GravetyPoint;
import MPU6050.I2cCommunication;
import MPU6050.MPU6050;
import MPU6050.MPU6050Motion;
import MPU6050.Quaternion;
import MPU6050.RegisterConstant;
import lejos.hardware.port.Port;
import lejos.hardware.sensor.I2CSensor;


public class GyroSensor
{
	public static final int DEFAULT_I2C_ADDRESS = 0xD0; //0xD0 or 0x68
	public static final int MPU6050_RA_WHO_AM_I = 0x75;
	public static final int READ_GYRO = 0x01;
	
	private MPU6050Motion mpu6050;
	private int packetSize;
	private I2CSensor sensor;
	private final int Enabled = 1;
	private final int Disabled = 0;

	private ComMPU6050C compMPU;
	
	public GyroSensor(Port port, int address) throws Throwable {
		sensor = new I2CSensor(port, address);
		Communication i2c = new Communication(sensor);
		compMPU = new ComMPU6050C(i2c);
		mpu6050 = new MPU6050Motion(compMPU);
		
		mpu6050.initialize();
		// load and configure the DMP
		if(!mpu6050.TestConnection())
		{
			throw new Exception("MPU6050 Sensor not connected.");
		}
		
		compMPU.WriteByte(RegisterConstant.MPU6050_RA_PWR_MGMT_1, 0);
		InitialiazeMPU6050();
	}
	
	private void InitialiazeMPU6050() throws Throwable {
		mpu6050.DmpInitialize();


	    // supply your own gyro offsets here, scaled for min sensitivity
	    mpu6050.SetXGyroOffset((byte) 220);
	    mpu6050.SetYGyroOffset((byte) 76);
	    mpu6050.SetZGyroOffset((byte) -85);
	    mpu6050.SetZAccelOffset(1788); // 1688 factory default for my test chip

		
	    // supply your own gyro offsets here, scaled for min sensitivity
	    mpu6050.SetXGyroOffset((byte) 220);
	    mpu6050.SetYGyroOffset((byte) 76);
	    mpu6050.SetZGyroOffset((byte) -85);
	    mpu6050.SetZAccelOffset(1788); // 1688 factory default for my test chip

        mpu6050.SetDMPEnabled(Enabled);

        mpu6050.GetIntStatus();
	    // get expected DMP packet size for later comparison
	    packetSize = mpu6050.dmpGetFIFOPacketSize();
	}

	public GyroSensor(Port port) throws Throwable {
		this(port, DEFAULT_I2C_ADDRESS);
	}
		
	public GravetyPoint GetAngle() throws Exception {
		    int mpuIntStatus = mpu6050.GetIntStatus();

		    // get current FIFO count
		    int fifoCount = mpu6050.GetFIFOCount();

		    // check for overflow (this should never happen unless our code is too inefficient)
		    if ((mpuIntStatus & 0x10) != 0 || fifoCount == 1024) {
		        // reset so we can continue cleanly
		        mpu6050.ResetFIFO();
		        throw new Exception("check for overflow (this should never happen unless our code is too inefficient)");

		    // otherwise, check for DMP data ready interrupt (this should happen frequently)
		    } 
		    if ((mpuIntStatus & 0x02) != 0) {
		    	throw new Exception("otherwise, check for DMP data ready interrupt (this should happen frequently)");
		    }
		        // wait for correct available data length, should be a VERY short wait
		        while (fifoCount < packetSize) 
		        	fifoCount = mpu6050.GetFIFOCount();

		        // read a packet from FIFO
		        int[] fifoBuffer = mpu6050.GetFIFOBytes(packetSize);
		        
		        // track FIFO count here in case there is > 1 packet available
		        // (this lets us immediately read more without waiting for an interrupt)
		        fifoCount -= packetSize;

		        // display quaternion values in easy matrix form: w x y z
		        Quaternion q = mpu6050.dmpGetQuaternion(fifoBuffer);

               // display Euler angles in degrees
	           GravetyPoint gravity = mpu6050.dmpGetGravity(q);
	           return mpu6050.dmpGetYawPitchRoll(q, gravity);
	}

	public void close() {
		sensor.close();
	}	
}