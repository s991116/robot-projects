class main(object):

    def __init__(self, myscreen, displayStates):
        self.myscreen = myscreen
        self.displayStates = displayStates
        return
        
    def display(self):
        escapeKeycode = 27
        choices = {ord('1') : self.displayStates['control'].display,
                   ord('2') : self.displayStates['servo'].display }
                   ord('3') : self.displayStates['motor'].display }
        
        while True:

            self.myscreen.clear()
            
            self.myscreen.addstr(1, 1, "   _____                                           ")
            self.myscreen.addstr(2, 1, "  / ____|                                          ")
            self.myscreen.addstr(3, 1, " | (___     ___    __ _  __      __   __ _   _   _ ")
            self.myscreen.addstr(4, 1, "  \___ \   / _ \  / _` | \ \ /\ / /  / _` | | | | |")
            self.myscreen.addstr(5, 1, "  ____) | |  __/ | (_| |  \ V  V /  | (_| | | |_| |")
            self.myscreen.addstr(6, 1, " |_____/   \___|  \__, |   \_/\_/    \__,_|  \__, |")
            self.myscreen.addstr(7, 1, "                   __/ |                      __/ |")
            self.myscreen.addstr(8, 1, "                  |___/                      |___/ ")
            
            self.myscreen.addstr(11, 1, " 1. Control")
            self.myscreen.addstr(12, 1, " 2. Servo")
            self.myscreen.addstr(13, 1, " 3. Motor")

            self.myscreen.addstr(16, 1, " Esc. Exit")
            
            self.myscreen.addstr(20, 1, " Choice: ")

            choice = self.myscreen.getch()
        
            if(choice == escapeKeycode):
                break
            
            if choice in choices:
                choices[choice]()