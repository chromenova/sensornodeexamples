#define LED_INDICATOR 0

#include <SPI.h>
#include <SD.h>

#include <Wire.h>
#include "BlueDot_BME280_TSL2591.h"

BlueDot_BME280_TSL2591 bme280;
BlueDot_BME280_TSL2591 tsl2591;

const int chipSelect = 15;



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

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }

  
}

void loop() { 
  
    String dataString = "";

    digitalWrite(LED_INDICATOR, HIGH);
  
    File dataFile = SD.open("sensorlog.txt", FILE_WRITE);  
    
    dataString += "Time:";
    dataString += String(float(millis())/1000);
    dataString += ",";
    
    dataString += "Temp:";
    dataString += String(bme280.readTempC());
    dataString += ",";
    
    dataString += "Humidity:";
    dataString += String(bme280.readHumidity());
    dataString += ",";
    
    dataString += "Pressure:";
    dataString += String(bme280.readPressure());
    dataString += ",";
    
    dataString += "Altitude:";
    dataString += String(bme280.readAltitudeMeter());
    dataString += ",";
    
    dataString += "Altitude:";
    dataString += String(tsl2591.readIlluminance_TSL2591());

    if (dataFile) {
      dataFile.println(dataString);
      Serial.println(dataString);
      dataFile.close();
    } else {
      Serial.println("error opening logging file");
    }
  
    digitalWrite(LED_INDICATOR, LOW);
    
    delay(1000);
 
}
