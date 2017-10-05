// Test code Temperature Humidity Air Quaity

#include "DHT.h"
#include "AirQuality.h"
#include "Arduino.h"

#define DHTPIN A0         // what pin we're connected to for Temperature Humidity sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
}

void loop()
{

  // Gas Sensor Exterior
  float sensor_volt_AQE;
  float RS_gas; // Get value of RS in a GAS
  float ratio; // Get ratio RS_GAS/RS_air
  float sensorValue_AQE = analogRead(A2);
  sensor_volt_AQE=(float)sensorValue_AQE/1024*5.0;
  RS_gas = (5.0-sensor_volt_AQE)/sensor_volt_AQE; // omit *RL
 
  /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
  ratio = RS_gas/26;  // ratio = RS/R0 
  /*-----------------------------------------------------------------------*/
 
  Serial.print("sensor_volt_AQE = ");
  Serial.print(sensor_volt_AQE);
  Serial.print("V");
  Serial.println("RS_ratio = ");
  Serial.print(RS_gas);
  Serial.println("Rs/R0 = ");
  Serial.print(ratio);
 
  Serial.print("\n");
 
  delay(1000);

 //Gas sensor interior
  float sensor_volt_AQI; 
  float sensorValue_AQI;
 
  sensorValue_AQI = analogRead(A1);
  sensor_volt_AQI = sensorValue_AQI/1024*5.0;
 
  Serial.print("sensor_volt_AQI = ");
  Serial.print(sensor_volt_AQI);
  Serial.println("V");
  delay(1000);


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
    Serial.print(" %3");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" °C");
  }
  
}
