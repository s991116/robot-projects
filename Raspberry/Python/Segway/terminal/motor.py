class motor(object):
    
    
    def __init__(self, myscreen, segway):
        self.myscreen = myscreen
        self.segway = segway
        return
        
    def display(self):
        escapeKeycode = 27
        while True:
            wheelDistanceTotal = self.segway.wheelDistance.getDistance();

            self.myscreen.clear()
            
            self.myscreen.addstr(1, 1, " __  __           _                  ")
            self.myscreen.addstr(2, 1, "|  \/  |         | |                 ")
            self.myscreen.addstr(3, 1, "| \  / |   ___   | |_    ___    _ __ ")
            self.myscreen.addstr(4, 1, "| |\/| |  / _ \  | __|  / _ \  | '__|")
            self.myscreen.addstr(5, 1, "| |  | | | (_) | | |_  | (_) | | |   ")
            self.myscreen.addstr(6, 1, "|_|  |_|  \___/   \__|  \___/  |_|   ")
                                                                  
            self.myscreen.addstr(10, 1, " Distance ( " + str(wheelDistanceTotal[0]) + " , " + str(wheelDistanceTotal[1]) + " )")
            self.myscreen.addstr(12, 1, " 1. Update Mesaure")
            self.myscreen.addstr(13, 1, " 2. Reset and update Mesaure")
                            
            self.myscreen.addstr(17, 1, " Esc. Back")
            
            self.myscreen.addstr(20, 1, " Choice: ")
    
            choise = self.myscreen.getch()
            
            if(choise == escapeKeycode):
                return
                                
            if(choise == ord('2')):
                self.segway.wheelDistance.getDistanceAndReset()