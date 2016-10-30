#Python readme notes
#Set virtual environment
workon cv

#Run all test in folder (Remember to delete all pyc that are not used any more)
python -m unittest discover -v #cannot get '-p test_*.py' to work 

#Run single test by with
python -m unittest -v testing testCamera

#Problems with terminal (not echo input) can be solved by running 'reset'
#from terminal 
