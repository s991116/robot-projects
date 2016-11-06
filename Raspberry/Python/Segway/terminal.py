import curses
from terminal.main import main
from terminal.control import control
from terminal.servo import servo
from segway import segway


segway = segway()

myscreen = curses.initscr()

control = control(myscreen, segway)
servo = servo(myscreen, segway.servo)

displayStates = {'control': control, 'servo': servo}

main = main(myscreen, displayStates)
main.display()

curses.endwin()
