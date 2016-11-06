class servo(object):
    
    
    def __init__(self, myscreen, servo):
        self.myscreen = myscreen
        self.servo = servo
        return
        
    def display(self):
        escapeKeycode = 27
        while True:
            servoVertical   = self.servo.getVerticalPosition()
            servoHorizontal = self.servo.getHorizontalPosition()
            servoVerticalSpeed   = self.servo.getVerticalSpeed()
            servoHorizontalSpeed = self.servo.getHorizontalSpeed()

            self.myscreen.clear()
            
            self.myscreen.addstr(1, 1, "   _____                               ")
            self.myscreen.addstr(2, 1, "  / ____|                              ")
            self.myscreen.addstr(3, 1, " | (___     ___   _ __  __   __   ___  ")
            self.myscreen.addstr(4, 1, "  \___ \   / _ \ | '__| \ \ / /  / _ \ ")
            self.myscreen.addstr(5, 1, "  ____) | |  __/ | |     \ V /  | (_) |")
            self.myscreen.addstr(6, 1, " |_____/   \___| |_|      \_/    \___/ ")
            
            self.myscreen.addstr(8, 1, "Vertical position: " + str(servoVertical))
            self.myscreen.addstr(9, 1, "Vertical speed: "+ str(servoVerticalSpeed))
            self.myscreen.addstr(10, 1, "Horizontal position: " + str(servoHorizontal))
            self.myscreen.addstr(11, 1, "Horizontal speed: "+ str(servoHorizontalSpeed))
            
            self.myscreen.addstr(13, 1, " 1. Set Vertical position")
            self.myscreen.addstr(14, 1, " 2. Set Horizontal position")
            self.myscreen.addstr(15, 1, " 3. Set Vertical and Horizontal move speed")

            self.myscreen.addstr(17, 1, " Esc. Back")
            
            self.myscreen.addstr(20, 1, " Choice: ")
    
            choise = self.myscreen.getch()
            
            if(choise == escapeKeycode):
                return
            
            if(choise == ord('1')):
                self.myscreen.addstr(22,1, " Vertical: ")
                input = self.myscreen.getstr(22,11, 5)                
                self.servo.setVerticalPosition(int(input))
                
            if(choise == ord('2')):
                self.myscreen.addstr(22,1, " Horizontal: ")
                input = self.myscreen.getstr(22,13, 5)                
                self.servo.setHorizontalPosition(int(input))

            if(choise == ord('3')):
                self.myscreen.addstr(22,1, " Vertical speed: ")
                vertical = self.myscreen.getstr(22,17, 5)                
                self.myscreen.addstr(23,1, " Horizontal speed: ")
                horizontal = self.myscreen.getstr(23,19, 5)                
                
                self.servo.setServoSpeed(int(vertical),int(horizontal))
