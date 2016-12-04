class gyro(object):
    
    
    def __init__(self, myscreen, segway):
        self.myscreen = myscreen
        self.segway = segway
        return
        
    def display(self):
        escapeKeycode = 27
        while True:
            gyroAngleTick = self.segway.gyro.measure();
            gyroAngleRadian = self.segway.gyro.measureAngle();

            self.myscreen.clear()
            
            self.myscreen.addstr(1, 1, "   _____                        ")
            self.myscreen.addstr(2, 1, "  / ____|                       ")
            self.myscreen.addstr(3, 1, " | |  __   _   _   _ __    ___  ")
            self.myscreen.addstr(4, 1, " | | |_ | | | | | | '__|  / _ \ ")
            self.myscreen.addstr(5, 1, " | |__| | | |_| | | |    | (_) |")
            self.myscreen.addstr(6, 1, "  \_____|  \__, | |_|     \___/ ")
            self.myscreen.addstr(7, 1, "            __/ |               ")
            self.myscreen.addstr(8, 1, "           |___/                ")
                                                                  
            self.myscreen.addstr(10, 1, " Angle Tick: " + str(gyroAngleTick[0]))
            self.myscreen.addstr(11, 1, " Angle Radian: " + str(gyroAngleRadian))
                            
            self.myscreen.addstr(17, 1, " Esc. Back")
            
            self.myscreen.addstr(20, 1, " Choice: ")
    
            choice = self.myscreen.getch()
            
            if(choice == escapeKeycode):
                return
