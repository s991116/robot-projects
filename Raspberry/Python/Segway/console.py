import curses

try:
    screen = curses.initscr() 
    curses.noecho() 
    screen.keypad(1) 
    
    screen.addstr("Press q to quit.\n\n") 
    while True: 
       event = screen.getch() 
       if event == ord("q"): break 
        
finally:
    curses.endwin()
