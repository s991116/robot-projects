class numericalConverter(object):
    @staticmethod
    def ToSignedShort(number):
        return number-65536 if (number > 32768) else number