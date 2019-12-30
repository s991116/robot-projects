var serialCommands = require('./serialCommands');

createFixture = () => {
  const sendData = jest.fn((cmd,data) => {});
  const getData = jest.fn((cmd) => {return 0;});
  comMock = {sendData: sendData, getData: getData};
  const headPromise = require('./head')(comMock);
  return  {
    headPromise: headPromise,
    sendData: sendData,
  }
}

test('Start in neutral position', () => {
  const fixture = createFixture();
  const head = fixture.headPromise.then((head) => {
    head.move(0,0);
    expect(fixture.sendData).toHaveBeenCalledTimes(1);
  });
});