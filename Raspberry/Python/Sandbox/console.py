import curses

screen = curses.initscr() 
curses.noecho() 
#curses.curs_set(0) 
screen.keypad(1) 

screen.addstr("This is a Sample Curses Script\n\n") 
while True: 
   event = screen.getch() 
   if event == ord("q"): break 
    
curses.echo()
curses.endwin()
