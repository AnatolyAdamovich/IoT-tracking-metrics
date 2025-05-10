#include "DHTesp.h"

// пины для всех датчиков
const int DHT_PIN_1 = 15;
const int DHT_PIN_2 = 12;
const int DHT_PIN_3 = 16;

// инициализация датчиков
DHTesp dhtSensor1;
DHTesp dhtSensor2;
DHTesp dhtSensor3;

void setup() {
  Serial.begin(115200);
  dhtSensor1.setup(DHT_PIN_1, DHTesp::DHT22);
  dhtSensor2.setup(DHT_PIN_2, DHTesp::DHT22);
  dhtSensor3.setup(DHT_PIN_3, DHTesp::DHT22);
}

void loop() {
  TempAndHumidity data1 = dhtSensor1.getTempAndHumidity();
  TempAndHumidity data2 = dhtSensor2.getTempAndHumidity();
  TempAndHumidity data3 = dhtSensor3.getTempAndHumidity();
  
  Serial.print("{\"sensor1\":{\"temperature\":" + String(data1.temperature, 2));
  Serial.print(",\"humidity\":" + String(data1.humidity, 1) + "},");

  Serial.print("\"sensor2\":{\"temperature\":" + String(data2.temperature, 2));
  Serial.print(",\"humidity\":" + String(data2.humidity, 1) + "},");
  
  Serial.print("\"sensor3\":{\"temperature\":" + String(data3.temperature, 2));
  Serial.print(",\"humidity\":" + String(data3.humidity, 1) + "}");
  Serial.println("}");
  
  delay(10000); // Wait for a new reading from the sensor (DHT22 has ~0.5Hz sample rate)
}