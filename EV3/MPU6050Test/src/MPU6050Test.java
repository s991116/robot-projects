import lejos.hardware.Button;
import lejos.hardware.lcd.LCD;
import lejos.hardware.port.SensorPort;

public class MPU6050Test {

	public static void main(String[] args) {
		LCD.drawString("I2C Test", 1,1);

		MPU6050 gyro = new MPU6050(SensorPort.S2);
		
		int measureCounter = 0;
		long startTime = System.currentTimeMillis();
		int angle_speed;
		int angle_absolute = 0;
		int angle_speed0 = -68;

		while(Button.ESCAPE.isUp()) {
			
			angle_speed = gyro.ReadAngle() - angle_speed0;;
     	    angle_speed/=50;
            angle_absolute  += angle_speed;
/*
            int error_angle =  0 - angle_absolute;                 //PD-Regelung: Winkel
            int angle_PTerm = error_angle * angle_P_factor;
            int angle_DTerm = angle_speed * angle_D_factor;


            route = (MotorRotationCount(OUT_B));                   //PD-Regelung: Position
      int error_route = 0 - route;
      int route_PTerm = error_route * route_P_factor;
      int route_DTerm  = (error_route - last_route_error) * route_D_factor;
      last_route_error = error_route;

      int PD = angle_PTerm - angle_DTerm - route_PTerm - route_DTerm;

      if (PD >100) {PD = 100;}     //Begrenzung der Nachregelung auf max. Motorleistung
      if (PD < -100) {PD = -100;}

      OnFwd(OUT_BC, PD);
	*/		
			
			measureCounter++;
			if(measureCounter % 10 == 0)
			{
				long endTime = System.currentTimeMillis();

				LCD.drawString("                         ",0,1);
				LCD.drawString("Angle Speed = " + angle_speed,0,1);		

				LCD.drawString("                         ",0,2);
				LCD.drawString("Angle abs. = " + angle_absolute,0,2);		

				LCD.drawString("                         ",0,7);
				LCD.drawString("Time: " + (endTime-startTime)/10, 0, 7);
				measureCounter = 0;
				startTime = System.currentTimeMillis();
			}
		}	
	}
}
