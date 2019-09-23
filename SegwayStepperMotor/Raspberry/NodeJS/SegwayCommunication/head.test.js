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

test('Send neutral position', () => {
  const fixture = createFixture();
  const head = fixture.head;

  head.move(0,0);

  expect(fixture.sendData).toHaveBeenCalledTimes(2);
  expect(fixture.sendData).toHaveBeenCalledWith(serialCommands.CMD_SET_SERVO_1_POSITION, 127);
  expect(fixture.sendData).toHaveBeenCalledWith(serialCommands.CMD_SET_SERVO_2_POSITION, 127);
});

test('Send maximum position', () => {
  const fixture = createFixture();
  const head = fixture.head;

  head.move(100,100);

  expect(fixture.sendData).toHaveBeenCalledTimes(2);
  expect(fixture.sendData).toHaveBeenCalledWith(serialCommands.CMD_SET_SERVO_1_POSITION, 255);
  expect(fixture.sendData).toHaveBeenCalledWith(serialCommands.CMD_SET_SERVO_2_POSITION, 255);
});

test('Send minimum position', () => {
  const fixture = createFixture();
  const head = fixture.head;

  head.move(-100,-100);

  expect(fixture.sendData).toHaveBeenCalledTimes(2);
  expect(fixture.sendData).toHaveBeenCalledWith(serialCommands.CMD_SET_SERVO_1_POSITION, 0);
  expect(fixture.sendData).toHaveBeenCalledWith(serialCommands.CMD_SET_SERVO_2_POSITION, 0);
});