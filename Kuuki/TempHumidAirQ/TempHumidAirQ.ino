// Test code Temperature Humidity Air Quaity

#include "DHT.h"
#include "AirQuality.h"
#include "Arduino.h"

#define DHTPIN A0         // what pin we're connected to for Temperature Humidity sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

AirQuality airqualitysensor;
DHT dht(DHTPIN, DHTTYPE);

int current_quality = -1;

void setup()
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  airqualitysensor.init(14);
}

void loop()
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //Temperature & Humidity
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
  }

  //Air Quality
  current_quality = airqualitysensor.slope();
  if (current_quality >= 0) // if a valid data returned.
  {
    if (current_quality == 0)
      Serial.println("High pollution! Force signal active");
    else if (current_quality == 1)
      Serial.println("High pollution!");
    else if (current_quality == 2)
      Serial.println("Low pollution!");
    else if (current_quality == 3)
      Serial.println("Fresh air");
  }

}

ISR(TIMER2_OVF_vect)
{
  if (airqualitysensor.counter == 122) //set 2 seconds as a detected duty
  {

    airqualitysensor.last_vol = airqualitysensor.first_vol;
    airqualitysensor.first_vol = analogRead(A1);
    airqualitysensor.counter = 0;
    airqualitysensor.timer_index = 1;
    PORTB = PORTB ^ 0x20;
  }
  else
  {
    airqualitysensor.counter++;
  }
}

