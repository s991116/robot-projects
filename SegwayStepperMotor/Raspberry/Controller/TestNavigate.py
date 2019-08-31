import curses
from curses import wrapper
import time
from Arduino import Arduino

def main(stdscr):
    # Clear screen
    stdscr.clear()
    stdscr.nodelay(1)
    ctrl = Arduino.GetArduinoController()
    
    while True:
        time.sleep(0.05)
        char = stdscr.getch()
        if char == ord('q'):
            break
        elif char == curses.KEY_RIGHT:
            ctrl.Direction(0,1)            
            stdscr.addstr(0, 0, 'right')
        elif char == curses.KEY_LEFT:
            ctrl.Direction(0,-1)
            stdscr.addstr(1, 0, 'left ')       
        elif char == curses.KEY_UP:
            ctrl.Direction(1,0)
            stdscr.addstr(2, 0, 'up   ')       
        elif char == curses.KEY_DOWN:
            ctrl.Direction(-1,0)
            stdscr.addstr(3, 0, 'down ')
        else:
            stdscr.clear()

wrapper(main)