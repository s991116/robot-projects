class control(object):
    
    
    def __init__(self, myscreen, segway):
        self.myscreen = myscreen
        self.segway = segway
        return
        
    def display(self):
        escapeKeycode = 27
        while True:
            segwayEnableState = self.segway.isEnabled()
            
            pidGyro = self.segway.pidGyro();
            pidSpeed = self.segway.pidSpeed();
            pidMotorA = self.segway.pidMotorA();
            pidMotorB = self.segway.pidMotorB();
            self.myscreen.clear()
            
            self.myscreen.addstr(1, 1, "   _____                   _                    _ ")
            self.myscreen.addstr(2, 1, "  / ____|                 | |                  | |")
            self.myscreen.addstr(3, 1, " | |        ___    _ __   | |_   _ __    ___   | |")
            self.myscreen.addstr(4, 1, " | |       / _ \  | '_ \  | __| | '__|  / _ \  | |")
            self.myscreen.addstr(5, 1, " | |____  | (_) | | | | | | |_  | |    | (_) | | |")
            self.myscreen.addstr(6, 1, "  \_____|  \___/  |_| |_|  \__| |_|     \___/  |_|")
                                                      
            
            self.myscreen.addstr(8 , 1, " TERMINAL")
            self.myscreen.addstr(9 , 1, " PID-Gyro (" + str(pidGyro[0]) + " , " + str(pidGyro[1]) + " , " + str(pidGyro[2]) + ")")
            self.myscreen.addstr(10, 1, " PID-Speed (" + str(pidSpeed[0]) + " , " + str(pidSpeed[1]) + " , " + str(pidSpeed[2]) + ")")
            self.myscreen.addstr(11, 1, " PID-Motor A (" + str(pidMotorA[0]) + " , " + str(pidMotorA[1]) + " , " + str(pidMotorA[2]) + ")")
            self.myscreen.addstr(12, 1, " PID-Motor B (" + str(pidMotorB[0]) + " , " + str(pidMotorB[1]) + " , " + str(pidMotorB[2]) + ")")
            
            if(segwayEnableState == 0):
                self.myscreen.addstr(13, 1, " 1. Enable")
            else:
                self.myscreen.addstr(13, 1, " 1. Disable")

            self.myscreen.addstr(14, 1, " 2. Set PID Gyro")
            self.myscreen.addstr(15, 1, " 3. Set PID Speed")
            self.myscreen.addstr(16, 1, " 4. Set PID Motor A")
            self.myscreen.addstr(17, 1, " 5. Set PID Motor B")
            self.myscreen.addstr(18, 1, " R. Wii Remote")
                
            self.myscreen.addstr(20, 1, " Esc. Back")
            
            self.myscreen.addstr(22, 1, " Choice: ")
    
            choise = self.myscreen.getch()
            
            if(choise == escapeKeycode):
                return
            
            if(choise == ord('1')):
                if(segwayEnableState == 0):
                    self.segway.enable()
                else:
                    self.segway.disable()

            if(choise == ord('2')):
                self.myscreen.addstr(25,1, " Gyro P-Corr: ")
                p = self.myscreen.getstr(25,14, 5)                
                self.myscreen.addstr(26,1, " Gyro I-Corr: ")
                i = self.myscreen.getstr(26,14, 5)                
                self.myscreen.addstr(27,1, " Gyro D-Corr: ")
                d = self.myscreen.getstr(27,14, 5)                
                self.segway.SetGyroPid(int(p),int(i),int(d))
                
            if(choise == ord('3')):
                self.myscreen.addstr(25,1, " Speed P-Corr: ")
                p = self.myscreen.getstr(25,15, 5)                
                self.myscreen.addstr(26,1, " Speed I-Corr: ")
                i = self.myscreen.getstr(26,15, 5)                
                self.myscreen.addstr(27,1, " Speed D-Corr: ")
                d = self.myscreen.getstr(27,15, 5)                
                self.segway.SetSpeedPid(int(p),int(i),int(d))

            if(choise == ord('4')):
                self.myscreen.addstr(25,1, " Motor A P-Corr: ")
                p = self.myscreen.getstr(25,17, 5)                
                self.myscreen.addstr(26,1, " Motor A I-Corr: ")
                i = self.myscreen.getstr(26,17, 5)                
                self.myscreen.addstr(27,1, " Motor A D-Corr: ")
                d = self.myscreen.getstr(27,17, 5)                
                self.segway.setMotorAPid(int(p),int(i),int(d))

            if(choise == ord('5')):
                self.myscreen.addstr(25,1, " Motor B P-Corr: ")
                p = self.myscreen.getstr(25,17, 5)                
                self.myscreen.addstr(26,1, " Motor B I-Corr: ")
                i = self.myscreen.getstr(26,17, 5)                
                self.myscreen.addstr(27,1, " Motor B D-Corr: ")
                d = self.myscreen.getstr(27,17, 5)                
                self.segway.setMotorBPid(int(p),int(i),int(d))
                
            if(choise == ord('r')):
                self.myscreen.addstr(25,1, "Press 1 + 2 on Wii to connect")
                self.myscreen.addstr(26,1, "Press '-' and '+' to disconnect")
                self.myscreen.addstr(27,1, "")

                self.myscreen.refresh()
                self.segway.wiiControl()
                