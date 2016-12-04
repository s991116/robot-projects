#! /usr/bin/python

import curses

screen = curses.initscr()
try:
    curses.noecho()
    #curses.curs_set(0)
    screen.keypad(1)
    screen.addstr("Press a key")
    event = screen.getch()
finally:
    curses.endwin()

if event == curses.KEY_LEFT:
    print("Left Arrow Key pressed")
elif event == curses.KEY_RIGHT:
    print("Right Arrow Key pressed")
else:
    print(event)