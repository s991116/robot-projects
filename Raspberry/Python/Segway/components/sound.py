import subprocess

class sound(object):
    @staticmethod
    def play(filename):
        proc = subprocess.Popen(['omxplayer',filename], stdout=subprocess.PIPE)