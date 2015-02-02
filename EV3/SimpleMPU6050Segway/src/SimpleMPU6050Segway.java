import lejos.hardware.Button;
import lejos.hardware.lcd.LCD;
import lejos.hardware.motor.NXTMotor;
import lejos.hardware.port.I2CPort;
import lejos.hardware.port.MotorPort;
import lejos.hardware.port.SensorPort;
import lejos.hardware.sensor.I2CSensor;
import lejos.hardware.sensor.SensorConstants;
import lejos.utility.Delay;
import lejos.utility.EndianTools;


public class SimpleMPU6050Segway {
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
   
   private static byte [] buf = new byte[6];
   private static int angle_speed0 = 200;
   
   public static void main(String[] args) {
      
      I2CSensor gyro = new I2CSensor(SensorPort.S3,0x68<<1,SensorConstants.TYPE_LOWSPEED);
      
      
      gyro.getData(0x75, buf,0, 1);
      LCD.drawString("who am I: " + buf[0],0,1);
      
      gyro.sendData(0x6b, (byte) 0x80); // reset all register to default
      
      Delay.msDelay(5);
      gyro.sendData(0x6b, (byte) 0x03); // set z axis as clock source
      gyro.sendData(0x1a, (byte) 0x00); // disables FSYNC, configures DPLF
      gyro.sendData(0x1b, (byte) 0x18);   //0b11000 set range to 2000*2
      
      Delay.msDelay(100);
      
      int angle_absolute=0;
      long cloop = 0;
      int angle_P_factor = 12;
      int angle_D_factor = 100;
      int last_angle_error = 0;
      int target_angle = 0;
      
      
      int route = 0;
      int route_P_factor = -10;
      int route_D_factor = -250;
      int last_route_error = 0;
      
      
      leftMotor = new NXTMotor(MotorPort.C);
      rightMotor = new NXTMotor(MotorPort.B);
      
      leftMotor.resetTachoCount();
      rightMotor.resetTachoCount();
      
      
      while(Button.ESCAPE.isUp()) {
         calcInterval(cloop);
         gyro.getData(0x43, buf,0, 6); // read only gyro data
         int angle_speed = EndianTools.decodeShortBE(buf,0)*10 + angle_speed0;
         int true_angle_speed = (int) (angle_speed / 655.536);
         //int angle_speed =  (((int)buf[0]) << 8) | buf[1];
         angle_absolute +=  true_angle_speed;
         
         int error_angle = target_angle - angle_absolute;
         int angle_PTerm = (int) (error_angle*angle_P_factor);
         int angle_DTerm = (int) (true_angle_speed*angle_D_factor);
         
         route = TachoCount();
         int error_route = 0 - route;
         int route_PTerm = (int) (error_route*route_P_factor);
         int route_DTerm = (int) ((error_route - last_route_error)*route_D_factor);
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
         if(Button.LEFT.isDown()) target_angle-=1;
         if(Button.RIGHT.isDown()) target_angle+=1;
         
         //Delay.msDelay(10);
         cloop++;
      }
   }

}