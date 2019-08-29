import unittest
import Arduino
import CommunicationStub
import Commands

class TestNavigation(unittest.TestCase):

    def setUp(self):
        self.communication = CommunicationStub.CommunicationStub()
        self.Fixture = Arduino.Arduino(self.communication)

    def test_StandStill(self):
        self.Fixture.Direction(0,0)
        self.assertEqual(self.communication.cmd, Commands.CMD_SET_MOVEMENT)
        self.assertEqual(self.communication.data, 0)

    def test_MoveForward(self):
        self.Fixture.Direction(1,0)
        self.assertEqual(self.communication.cmd, Commands.CMD_SET_MOVEMENT)
        self.assertEqual(self.communication.data, 0x04)

    def test_MoveBackwards(self):
        self.Fixture.Direction(-1,0)
        self.assertEqual(self.communication.cmd, Commands.CMD_SET_MOVEMENT)
        self.assertEqual(self.communication.data, 0x08)

    def test_MoveLeft(self):
        self.Fixture.Direction(0,-1)
        self.assertEqual(self.communication.cmd, Commands.CMD_SET_MOVEMENT)
        self.assertEqual(self.communication.data, 0x01)

    def test_MoveRight(self):
        self.Fixture.Direction(0,1)
        self.assertEqual(self.communication.cmd, Commands.CMD_SET_MOVEMENT)
        self.assertEqual(self.communication.data, 0x02)

    def test_MoveForwardRight(self):
        self.Fixture.Direction(1,1)
        self.assertEqual(self.communication.cmd, Commands.CMD_SET_MOVEMENT)
        self.assertEqual(self.communication.data, 0x06)

    def test_MoveBackwardsLeft(self):
        self.Fixture.Direction(-1,-1)
        self.assertEqual(self.communication.cmd, Commands.CMD_SET_MOVEMENT)
        self.assertEqual(self.communication.data, 0x09)
