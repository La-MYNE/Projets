// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include <Wire.h>
#include "rgb_lcd.h"
#define DHTPIN A0     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

rgb_lcd lcd;

const int colorR = 0;
const int colorG = 500;
const int colorB = 0;
 
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    dht.begin();
    
    lcd.setRGB(colorR, colorG, colorB);
    
    lcd.print("DHTxx test!");

}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    lcd.print("Failed to read from DHT");
  }
  else
  {
    lcd.display("Humi: ");
    lcd.display(h);
    lcd.display(" % ");
    lcd.display("Temp: ");
    lcd.display(t);
    lcd.display(" C ");

   
  }
}
