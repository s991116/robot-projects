import subprocess

def Play(filename):
    subprocess.Popen(['omxplayer',filename], stdout=subprocess.PIPE)
