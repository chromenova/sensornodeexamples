#define LED_INDICATOR 0

#include <Wire.h>
#include "BlueDot_BME280_TSL2591.h"

BlueDot_BME280_TSL2591 bme280;
BlueDot_BME280_TSL2591 tsl2591;

void setup() {
  Serial.begin(9600);
  
  bme280.parameter.I2CAddress = 0x77;
  tsl2591.parameter.I2CAddress = 0x29;
  Wire.begin(21,22);
  tsl2591.parameter.gain = 0b01;
  tsl2591.parameter.integration = 0b000;
  tsl2591.config_TSL2591();
  bme280.parameter.sensorMode = 0b11;
  bme280.parameter.IIRfilter = 0b100;
  bme280.parameter.humidOversampling = 0b101;
  bme280.parameter.tempOversampling = 0b101;
  bme280.parameter.pressOversampling = 0b101;
  bme280.parameter.pressureSeaLevel = 1013.25;
  bme280.parameter.tempOutsideCelsius = 15;
  if (bme280.init_BME280() != 0x60) {        
    Serial.println(F("Ops! BME280 could not be found!"));
    //while(1);
  }
  else {
    Serial.println(F("BME280 detected!"));
  }

  if (tsl2591.init_TSL2591() != 0x50) {        
    Serial.println(F("Ops! TSL2591 could not be found!"));
    //while(1);
  }
  else {
    Serial.println(F("TSL2591 detected!"));
  }
  
  Serial.println();
  Serial.println(); 
}

void loop() { 
  digitalWrite(LED_INDICATOR, HIGH);
  
   
   Serial.print(F("Duration in Seconds:\t\t"));
   Serial.println(float(millis())/1000);
 
   Serial.print(F("Temperature in Celsius:\t\t")); 
   Serial.println(bme280.readTempC());
   
   Serial.print(F("Humidity in %:\t\t\t")); 
   Serial.println(bme280.readHumidity());

   Serial.print(F("Pressure in hPa:\t\t")); 
   Serial.println(bme280.readPressure());

   Serial.print(F("Altitude in Meters:\t\t")); 
   Serial.println(bme280.readAltitudeMeter());

   Serial.print(F("Illuminance in Lux:\t\t")); 
   Serial.println(tsl2591.readIlluminance_TSL2591());

   Serial.println();
   Serial.println();
   
   digitalWrite(LED_INDICATOR, LOW);
   
   delay(1000); 
 
}
