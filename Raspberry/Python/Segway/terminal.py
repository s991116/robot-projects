import curses
from terminal.main import main
from terminal.control import control
from terminal.servo import servo
from terminal.motor import motor
from terminal.gyro import gyro
from segway import segway

segway = segway()

myscreen = curses.initscr()
myscreen.keypad(1)
control = control(myscreen, segway)
servo = servo(myscreen, segway.servo)
motor = motor(myscreen, segway)
gyro = gyro(myscreen, segway)

displayStates = {'control': control, 'servo': servo, 'motor': motor, 'gyro': gyro}

main = main(myscreen, displayStates)
main.display()

curses.endwin()
