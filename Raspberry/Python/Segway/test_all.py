import unittest
import arduinoCom.test_arduino
import arduinoCom.test_serialProtocol
import camera.test_LineDetect

suiteList = []
suiteList.append(arduinoCom.test_serialProtocol.TestSuite())
#suiteList.append(arduinoCom.test_arduino.TestSuite())
suiteList.append(camera.test_LineDetect.TestSuite())


comboSuite = unittest.TestSuite(suiteList)
unittest.TextTestRunner(verbosity=2).run(comboSuite)
