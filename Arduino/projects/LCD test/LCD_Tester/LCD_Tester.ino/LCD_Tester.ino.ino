#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.autoscroll();
}
bool star;

void loop()
{
  delay(300);
  if(star)
    lcd.print("*");
  else
    lcd.print("-");
  star = !star;
}
