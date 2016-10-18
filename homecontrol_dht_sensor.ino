#include "DHT.h"
#include <Ethernet.h>
#include <SPI.h>
#include <Shys_Sensor.h>

#define DHTPIN 2
#define DHTTYPE DHT22   //alternativ:  DHT11, DHT21 or DHT22

/* *********************************** */
/*             CONFIGURE               */
/* *********************************** */
long tempSensorId = 12345;
long humidSensorId = 12346;


byte _piAddress[] =  {192, 168, 1, 99};

byte _mac[]  = {0xBA, 0x6C, 0x4A, 0x36, 0x44, 0xAD  };
byte _ip[]   = { 192, 168, 1, 124 };
byte _dns[]  = { 192, 168, 1, 1  };
byte _gate[] = { 192, 168, 1, 1 };
byte _mask[] = { 255, 255, 255, 0  };

long unsigned int dhtSignalIntervall = 10000;  
/* *********************************** */
/*           END CONFIGURE             */
/* *********************************** */


long unsigned int lastDHTSignal;  

long temp  = -999;
long humid = -999;

DHT dht(DHTPIN, DHTTYPE);

Shys_Sensor sensor  = Shys_Sensor(_mac, _ip, _dns, _gate, _mask, _piAddress);

/**
 *  Basic setup Method
 */
void setup() {
  Serial.begin(9600); 
  delay(700);
  
  Serial.println("HomeControl - Temp and Humidity Sensor");
  Serial.println();
  
  sensor.init();
  
  dht.begin();
  
  delay(50);
}

/**
 *  Basic loop Method
 */
void loop() {
  refreshDHTSensorValues();
  
  if(lastDHTSignal+dhtSignalIntervall<millis()){
    sensor.setSensorValue(tempSensorId, temp);
    sensor.setSensorValue(humidSensorId, humid);
    lastDHTSignal = millis();
    Serial.print("Humidity: "); 
    Serial.print(humid);
    Serial.print(" %\t");
    Serial.print("Temp: "); 
    Serial.print(temp);
    Serial.print(" *C ");
    Serial.println(" ");
  }

  delay(1500);
}


/**
 *  Read values from DHT-Sensor
 */
void refreshDHTSensorValues(){
  humid = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humid) || isnan(temp) ) { //|| isnan(f)
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}



