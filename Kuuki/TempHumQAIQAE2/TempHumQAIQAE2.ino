#include "DHT.h"
#include "AirQuality.h"
#include "Arduino.h"
#include <Wire.h>
#include "rgb_lcd.h"

#define DHTPIN A0         // what pin we're connected to for Temperature Humidity sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);
rgb_lcd lcd;

const int colorR = 0;
const int colorG = 3;
const int colorB = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{

  // Gas Sensor Exterior
  float sensor_volt_AQE;
  float RS_gas; // Get value of RS in a GAS
  int ratio; // Get ratio RS_GAS/RS_air
  int sensorValue_AQE = analogRead(A2);
  sensor_volt_AQE=(float)sensorValue_AQE/1024*5.0;
  RS_gas = (5.0-sensor_volt_AQE)/sensor_volt_AQE; // omit *RL

  //Gas sensor interior
  float sensor_volt_AQI; 
  float sensorValue_AQI;

  int h = dht.readHumidity();
  int t = dht.readTemperature();

  
  sensorValue_AQI = analogRead(A1);
  sensor_volt_AQI = sensorValue_AQI/1024*5.0;
  ratio = RS_gas/52;  // ratio = RS/R0 
  /*-----------------------------------------------------------------------*/
  //Temperature & Humidity
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    lcd.print("Failed to read from DHT");
  }
  else
  {
    lcd.print("H:");
    lcd.print(h);
    lcd.print("% ");
    lcd.print("T:");
    lcd.print(t);
    lcd.print("*C               ");
    
    //Serial.print("sensor_volt_AQE = ");
    //Serial.print(sensor_volt_AQE);
    //Serial.print(" V");
    //Serial.print("RS_ratio = ");
    //Serial.print(RS_gas);
    lcd.print("             Rs/R0=");
    lcd.print(ratio);
    
    //lcd.print("  Sens = ");
    //lcd.display(sensor_volt_AQI);
    //lcd.print(" V");
    lcd.print(" V=");
    lcd.print(sensorValue_AQE);
    lcd.print(" ");

    
    
    delay(1500);
    lcd.clear();
  }
  
}
