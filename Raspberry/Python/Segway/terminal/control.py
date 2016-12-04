import curses

class control(object):
    
    
    def __init__(self, myscreen, segway):
        self.myscreen = myscreen
        self.segway = segway
        self.direction = 0
        return
        
    def display(self):
        escapeKeycode = 27
        while True:
            segwayEnableState = self.segway.segwayControl.isEnabled()
            
            pidGyro = self.segway.pidGyro();
            pidSpeed = self.segway.pidSpeed();
            pidMotorA = self.segway.pidMotorA();
            pidMotorB = self.segway.pidMotorB();
            speedFactor = self.segway.segwayControl.getSpeedFactor();
            self.myscreen.clear()
            
            self.myscreen.addstr(1, 1, "   _____                   _                    _ ")
            self.myscreen.addstr(2, 1, "  / ____|                 | |                  | |")
            self.myscreen.addstr(3, 1, " | |        ___    _ __   | |_   _ __    ___   | |")
            self.myscreen.addstr(4, 1, " | |       / _ \  | '_ \  | __| | '__|  / _ \  | |")
            self.myscreen.addstr(5, 1, " | |____  | (_) | | | | | | |_  | |    | (_) | | |")
            self.myscreen.addstr(6, 1, "  \_____|  \___/  |_| |_|  \__| |_|     \___/  |_|")

            if(self.direction == 1):
                self.myscreen.addstr(1, 55, "    __     ")
                self.myscreen.addstr(2, 55, "   / /     ")
                self.myscreen.addstr(3, 55, "  / /_____ ")
                self.myscreen.addstr(4, 55, " < <______|")
                self.myscreen.addstr(5, 55, "  \ \      ")
                self.myscreen.addstr(6, 55, "   \_\     ")

            if(self.direction == 2):                                          
                self.myscreen.addstr(1, 55, "      ____     ")
                self.myscreen.addstr(2, 55, "     / /\ \    ")
                self.myscreen.addstr(3, 55, "    / /  \ \   ")
                self.myscreen.addstr(4, 55, "   / /    \ \  ")
                self.myscreen.addstr(5, 55, "  / /      \ \ ")
                self.myscreen.addstr(6, 55, " /_/        \_\\")

            if(self.direction == 3):                                          
                self.myscreen.addstr(1, 55, "      __   ")
                self.myscreen.addstr(2, 55, "      \ \  ")
                self.myscreen.addstr(3, 55, "  _____\ \ ")
                self.myscreen.addstr(4, 55, " |______> >")
                self.myscreen.addstr(5, 55, "       / / ")
                self.myscreen.addstr(6, 55, "      /_/  ")

            if(self.direction == 4):                                          
                self.myscreen.addstr(1, 55, "  __          __")
                self.myscreen.addstr(2, 55, "  \ \        / /")
                self.myscreen.addstr(3, 55, "   \ \      / / ")
                self.myscreen.addstr(4, 55, "    \ \    / /  ")
                self.myscreen.addstr(5, 55, "     \ \  / /   ")
                self.myscreen.addstr(6, 55, "      \_\/_/    ")
                
            self.myscreen.addstr(8 , 1, " PID-Gyro (" + str(pidGyro[0]) + " , " + str(pidGyro[1]) + " , " + str(pidGyro[2]) + ")")
            self.myscreen.addstr(9,  1, " PID-Speed (" + str(pidSpeed[0]) + " , " + str(pidSpeed[1]) + " , " + str(pidSpeed[2]) + ")")
            self.myscreen.addstr(10, 1, " Speed-factor: " + str(speedFactor))
            self.myscreen.addstr(11, 1, " PID-Motor A (" + str(pidMotorA[0]) + " , " + str(pidMotorA[1]) + " , " + str(pidMotorA[2]) + ")")
            self.myscreen.addstr(12, 1, " PID-Motor B (" + str(pidMotorB[0]) + " , " + str(pidMotorB[1]) + " , " + str(pidMotorB[2]) + ")")
            
            if(segwayEnableState == 0):
                self.myscreen.addstr(13, 1, " 1. Enable")
            else:
                self.myscreen.addstr(13, 1, " 1. Disable")

            self.myscreen.addstr(14, 1, " 2. Set PID Gyro")
            self.myscreen.addstr(15, 1, " 3. Set PID Speed")
            self.myscreen.addstr(16, 1, " 4. Set Speed Factor")
            self.myscreen.addstr(17, 1, " 5. Set PID Motor A")
            self.myscreen.addstr(18, 1, " 6. Set PID Motor B")
            self.myscreen.addstr(19, 1, " R. Wii Remote")
            self.myscreen.addstr(20, 1, " Arrowkeys controls (Space to stop)")    
            self.myscreen.addstr(21, 1, " Esc. Back")
            
            self.myscreen.addstr(23, 1, " Choice: ")
    
            choise = self.myscreen.getch()
            
            if(choise == escapeKeycode):
                return            
            
#            if(choise == escapeKeycode):
#                self.myscreen.getch()
#                keyDirection = self.myscreen.getch()
            keyDirection = choise
            if(keyDirection == curses.KEY_LEFT):
                self.direction = 1
                self.segway.segwayControl.setSegwayTurnSpeed(5)

            if(keyDirection == curses.KEY_UP):
                self.direction = 2
                self.segway.segwayControl.setSegwaySpeed(5)

            if(keyDirection == curses.KEY_RIGHT):
                self.direction = 3
                self.segway.segwayControl.setSegwayTurnSpeed(-5)

            if(keyDirection == curses.KEY_DOWN):
                self.direction = 4
                self.segway.segwayControl.setSegwaySpeed(-5)

            if(choise == ord(' ')):
                self.direction = 0
                self.segway.segwayControl.setSegwaySpeed(0)
                self.segway.segwayControl.setSegwayTurnSpeed(0)

                
            if(choise == ord('1')):
                if(segwayEnableState == 0):
                    self.segway.segwayControl.enable()
                else:
                    self.segway.segwayControl.disable()

            if(choise == ord('2')):
                self.myscreen.addstr(25,1, " Gyro P-Corr: ")
                p = self.myscreen.getstr(25,14, 5)                
                self.myscreen.addstr(26,1, " Gyro I-Corr: ")
                i = self.myscreen.getstr(26,14, 5)                
                self.myscreen.addstr(27,1, " Gyro D-Corr: ")
                d = self.myscreen.getstr(27,14, 5)                
                self.segway.SetGyroPid(int(p),int(i),int(d))

            if(choise == ord('3')):
                self.myscreen.addstr(25,1, " Speed factor:")
                speedFactor = self.myscreen.getstr(25,14, 5)                
                self.segway.segwayControl.setSpeedFactor(int(speedFactor))
                
            if(choise == ord('4')):
                self.myscreen.addstr(25,1, " Speed P-Corr: ")
                p = self.myscreen.getstr(25,15, 5)                
                self.myscreen.addstr(26,1, " Speed I-Corr: ")
                i = self.myscreen.getstr(26,15, 5)                
                self.myscreen.addstr(27,1, " Speed D-Corr: ")
                d = self.myscreen.getstr(27,15, 5)                
                self.segway.SetSpeedPid(int(p),int(i),int(d))

            if(choise == ord('5')):
                self.myscreen.addstr(25,1, " Motor A P-Corr: ")
                p = self.myscreen.getstr(25,17, 5)                
                self.myscreen.addstr(26,1, " Motor A I-Corr: ")
                i = self.myscreen.getstr(26,17, 5)                
                self.myscreen.addstr(27,1, " Motor A D-Corr: ")
                d = self.myscreen.getstr(27,17, 5)                
                self.segway.setMotorAPid(int(p),int(i),int(d))

            if(choise == ord('6')):
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
                