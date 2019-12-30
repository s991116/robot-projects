createFixture = () => {
  const sendData = jest.fn((cmd,data) => {});
  const sendNavigation = jest.fn((data) => {});

  comMock = {
    sendData: sendData,
    sendNavigation: sendNavigation
  };
  const navigation = require('./navigation')(comMock);
  return  {
    navigation: navigation,
    sendData: sendData,
    sendNavigation: sendNavigation
  }
}

test('Send stop cmd', () => {
  const fixture = createFixture();
  const navigation = fixture.navigation;

  navigation.navigate(navigation.stop, navigation.stop);

  expect(fixture.sendNavigation).toHaveBeenCalledTimes(1);
  expect(fixture.sendNavigation).toHaveBeenCalledWith(0b00000000);
});
  
test('Send forward and left cmd', () => {
  const fixture = createFixture();
  const navigation = fixture.navigation;

  navigation.navigate(navigation.forward,navigation.left);

  expect(fixture.sendNavigation).toHaveBeenCalledTimes(1);
  expect(fixture.sendNavigation).toHaveBeenCalledWith(0b00000101);
});

test('PID Settings updated', () => {
  const fixture = createFixture();
  const navigation = fixture.navigation;
  
  navigation.setPidSetting(1,2,3,0.0125,5);

  expect(fixture.sendData).toHaveBeenCalledTimes(5);
})