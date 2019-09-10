
createFixture = () => {
  const sendData = jest.fn((cmd,data) => {});
  comMock = {sendData: sendData};
  const navigation = require('./navigation')(comMock);
  return  {
    navigation: navigation,
    sendData: sendData,
  }
}

test('Send stop cmd', () => {
  const fixture = createFixture();
  const navigation = fixture.navigation;

  navigation.navigate(navigation.stop, navigation.stop);

  expect(fixture.sendData).toHaveBeenCalledTimes(1);
  expect(fixture.sendData).toHaveBeenCalledWith(0x11, 0x00);
});
  
test('Send forward and left cmd', () => {
  const fixture = createFixture();
  const navigation = fixture.navigation;

  navigation.navigate(navigation.forward,navigation.left);

  expect(fixture.sendData).toHaveBeenCalledTimes(1);
  expect(fixture.sendData).toHaveBeenCalledWith(0x11, 0b00000101);
});

test('PID Settings updated', () => {
  const fixture = createFixture();
  const navigation = fixture.navigation;
  
  navigation.pidSetting(1,2,3);

  expect(fixture.sendData).toHaveBeenCalledTimes(3);
})