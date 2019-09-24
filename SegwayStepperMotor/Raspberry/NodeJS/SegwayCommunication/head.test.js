var serialCommands = require('./serialCommands');

createFixture = () => {
  const sendData = jest.fn((cmd,data) => {});
  comMock = {sendData: sendData};
  const head = require('./head')(comMock);
  return  {
    head: head,
    sendData: sendData,
  }
}

test('Start in neutral position', () => {
  const fixture = createFixture();
  const head = fixture.head;

  head.move(0,0);

  expect(fixture.sendData).toHaveBeenCalledWith(serialCommands.CMD_SET_SERVO_1_POSITION, 90);
  expect(fixture.sendData).toHaveBeenCalledWith(serialCommands.CMD_SET_SERVO_2_POSITION, 90);
});