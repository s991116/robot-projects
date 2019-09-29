var serialCommands = require('./serialCommands');

createFixture = () => {
  const sendData = jest.fn((cmd,data) => {});
  const getData = jest.fn((cmd) => {return 0;});
  comMock = {sendData: sendData, getData: getData};
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
});