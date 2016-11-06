import subprocess

class sound(object):
    @staticmethod
    def play(filename):
        proc = subprocess.Popen(['omxplayer',filename], stdout=subprocess.PIPE)

    @staticmethod
    def hello():
        sound.play('hello.wav')
        
    @staticmethod
    def ridin():
        sound.play('ridin.mp3')