
#include "DHT.h"
 
#define DHTPIN A0 
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302)
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
 
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
 
DHT dht(DHTPIN, DHTTYPE);
 
void setup()
{
    Serial.begin(9600);
    Serial.println("DHTxx test!");
 
    dht.begin();
}
 
void loop()
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to A0 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    
    int sensorValue = analogRead(A2);
    sensor_volt=(float)sensorValue/1024*5.0;
    
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
    ratio = RS_gas/26; 
    
    if (isnan(t) || isnan(h))
    
    {
        Serial.println("Failed to read from DHT");
    }
    else
    
    {
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.print(" °C");
        Serial.print("     Humidity: ");
        Serial.print(h);
        Serial.print(" %");
        Serial.print("     Rs/R0 = ");
        Serial.println(ratio);
        delay(1000);
    }
}
