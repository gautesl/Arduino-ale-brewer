#include <OneWire.h> 
#include <DallasTemperature.h>

#define TEMP_SCAN 12

OneWire oneWire(TEMP_SCAN); 
DallasTemperature sensors(&oneWire);

uint16_t curr_temp = 0;
uint16_t mask = B11111111;

void setup() {
  pinMode(TEMP_SCAN, INPUT);
  sensors.begin(); 
  Serial.begin(9600);
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0) * 10;
  curr_temp = (uint16_t) temp;

  Serial.write(curr_temp >> 8);    //Serial.write(highByte(curr_temp));
  Serial.write(curr_temp & mask);  //Serial.write(lowByte(curr_temp));
}
