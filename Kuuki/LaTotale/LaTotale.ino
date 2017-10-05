#include <Wire.h>
#include <rgb_lcd.h>
#include "AirQuality.h"
#include "Arduino.h"
#include "DHT.h"
#define DHTPIN A0     // what pin the DHT is connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

AirQuality airqualitysensor;
int current_quality =-1;
#define BUZZER 10
void setup()
{
  Wire.begin();    // initialize i2c
  rgb_lcd.init();  //initialze SEEED OLED display
  rgb_lcd.clearDisplay();          //clear the screen and set start position to top left corner
  rgb_lcd.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  rgb_lcd.setVerticalMode();    
  //SeeedGrayOled.setPageMode();           //Set addressing mode to Page Mode
  rgb_lcd.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
  rgb_lcd.putString("Initializing"); //Print the String

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  airqualitysensor.init(14);
  dht.begin();
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  rgb_lcd.setTextXY(8,0);
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) 
  {
      rgb_lcd.putString("DHT ERROR");
  } 
  else 
  {
      rgb_lcd.putString("Humid: "); 
      rgb_lcd.setTextXY(9,0);
      rgb_lcd.putString("   "); 
      rgb_lcd.putFloat(h);
      rgb_lcd.putString("%"); 
      rgb_lcd.setTextXY(10,0);
      rgb_lcd.putString("Temp.: "); 
      rgb_lcd.setTextXY(11,0);
      rgb_lcd.putString("   "); 
      rgb_lcd.putFloat(t);
      rgb_lcd.putString("C");
  }

  current_quality=airqualitysensor.slope();
  if (current_quality >= 0) {
    if (current_quality <= 1)
      // Air quality is bad. Let's revert display to make some light !
      rgb_lcd.setInverseDisplay();
    else
      rgb_lcd.setNormalDisplay();

    rgb_lcd.setTextXY(1,0);
    rgb_lcd.putString("Air Quality:"); //Print the String
    rgb_lcd.setTextXY(2,0);
    rgb_lcd.putString("   "); // Empty the number line
    rgb_lcd.setTextXY(2,0);
    rgb_lcd.putNumber(airqualitysensor.first_vol); //Print the String

    rgb_lcd.setTextXY(0,0);
    if (current_quality==0)
    rgb_lcd.putString("Emergency   ");
    else if (current_quality==1)
    rgb_lcd.putString("Hi Pollution");
    else if (current_quality==2)
    rgb_lcd.putString("Lo Pollution");
    else if (current_quality ==3)
    rgb_lcd.putString("Fresh air   ");

    if (current_quality<1)
      digitalWrite(BUZZER, HIGH);
    else
      digitalWrite(BUZZER, LOW);
  }
}

ISR(TIMER2_OVF_vect)
{
if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
{

airqualitysensor.last_vol=airqualitysensor.first_vol;
airqualitysensor.first_vol=analogRead(A1);
airqualitysensor.counter=0;
airqualitysensor.timer_index=1;
//PORTB=PORTB^0x20;
}
else
{
airqualitysensor.counter++;
}
}
