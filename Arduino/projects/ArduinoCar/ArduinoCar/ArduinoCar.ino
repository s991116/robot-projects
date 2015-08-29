const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

byte colorValueRed = 255;
byte colorValueBlue = 255;
byte colorValueGreen = 255;


void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
 
void loop()
{
  if(colorValueRed > 0)
  {
    colorValueRed--;
  }
  else if(colorValueBlue > 0)
  {
    colorValueBlue--;
  }
  else if(colorValueGreen > 0)
  {
    colorValueGreen--;
  }
  else
  {
    colorValueRed = 255;
    colorValueBlue = 255;
    colorValueGreen = 255;
  }

// Write the color to each pin using PWM and the value gathered above
  analogWrite(redPin, colorValueRed);
  analogWrite(bluePin, colorValueBlue);
  analogWrite(greenPin, colorValueGreen);
  delay(3);
}
