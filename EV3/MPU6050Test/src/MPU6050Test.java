import lejos.hardware.Button;
import lejos.hardware.lcd.LCD;
import lejos.hardware.motor.NXTMotor;
import lejos.hardware.port.MotorPort;
import lejos.hardware.port.SensorPort;
import lejos.utility.Delay;

public class MPU6050Test {

	private static NXTMotor leftMotor;
	private static NXTMotor rightMotor;

	public static int TachoCount()
	{
		return ( leftMotor.getTachoCount() +  rightMotor.getTachoCount()) / 2;
	}
	
	   private static double tInterval;
	   private static long tCalcStart;
	   
	   public static void calcInterval(long cLoop) {
	      if (cLoop == 0) {
	         // First time through, set an initial tInterval time and
	         // record start time
	         tInterval = 0.0055;
	         tCalcStart = System.currentTimeMillis();
	      } else {
	         // Take average of number of times through the loop and
	         // use for interval time.
	         tInterval = (System.currentTimeMillis() - tCalcStart)/(cLoop*1000.0);
	      }
	   }


	public static void main(String[] args) {
		LCD.drawString("I2C Test", 1,1);

		ArduinoMPU6050 gyro = new ArduinoMPU6050(SensorPort.S2);
		
		int angle_speed;
		int angle_absolute = 0;
		int angle_staight = -68;

		long cloop = 0;
		int angle_P_factor = 12;
		int angle_D_factor = 100;
		int route = 0;

		int route_P_factor = 10;//-10;
		int route_D_factor = 250;//-250;
		int last_route_error = 0;

		leftMotor = new NXTMotor(MotorPort.B);
		rightMotor = new NXTMotor(MotorPort.C);

		leftMotor.resetTachoCount();
		rightMotor.resetTachoCount();

		while(Button.ESCAPE.isUp()) {
			calcInterval(cloop);
			
			GyroData gd = gyro.ReadGyro();
			angle_absolute = gd.angle;
			angle_speed = gd.accelration;

			int error_angle =  angle_staight - angle_absolute;                 //PD-Regelung: Winkel
			int angle_PTerm = error_angle * angle_P_factor;
			int angle_DTerm = angle_speed * angle_D_factor;

			route = TachoCount();                   //PD-Regelung: Position
			int error_route = 0 - route;
			int route_PTerm = (int) (error_route * route_P_factor);
			int route_DTerm = (int) ((error_route - last_route_error) * route_D_factor);
			last_route_error = error_route;

			int PD = angle_PTerm-angle_DTerm-route_PTerm-route_DTerm;
			PD/=10;

			if(PD>100) PD = 100;
			if(PD<-100) PD = -100;

			int PD_abs = Math.abs(PD);
			leftMotor.setPower((int)(PD_abs));
			rightMotor.setPower((int)(PD_abs));
			if (PD > 0) {
				leftMotor.backward();
				rightMotor.backward();
			} else if (PD < 0) {
				leftMotor.forward();
				rightMotor.forward();
			} else {
				leftMotor.stop();
				rightMotor.stop();
			}

			if(cloop%200==0) {
				LCD.drawString("gyr sp x: " + angle_speed + "     ", 0, 2);
				LCD.drawString("angle x: " + angle_absolute+"   ", 0, 3);
				LCD.drawString("loop_time ms: " + (int) (tInterval*1000)+"   ", 0, 4);
				LCD.drawString("power: "+PD+"   ",0,5);
				LCD.drawString("err angle: " + error_angle + "     ", 0, 5);
				LCD.drawString("err route: " + error_route +"   ", 0, 6);
			}
			if(Button.LEFT.isDown()) {
			}
			if(Button.RIGHT.isDown()) {
			}

			Delay.msDelay(50);
			cloop++;
		}	
	}
}
