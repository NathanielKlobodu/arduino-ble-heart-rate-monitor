#include <ArduinoBLE.h>
#include <Wire.h>
#include "MAX30105.h"
#include "Nicla_System.h"
#include "heartRate.h"


BLEService heartRateService("180D");  //BLE Service Name
BLEUnsignedCharCharacteristic heartRateChar("2A37", BLERead | BLENotify);  // BLE Characteristics

MAX30105 particleSensor;    //MAX30102 pulse oximeter object

const byte RATE_SIZE = 4;   //increase for more averaging. 4 is ok
byte rates[RATE_SIZE];      //array of heart rates
byte rateSpot = 0;          //array indexer
long lastBeat = 0;          //time at which the last beat occurred

float beatsPerMinute;       //instantaneous bpm
int beatAvg;                //average bpm

// LED status for onboard RGB led
int redLED = 0;
int greenLED = 0;
int blueLED = 0;

// declare functions
void getHeartRate();



void setup() {
  nicla::begin();
  nicla::leds.begin();

  if (!BLE.begin()) {
    while (1);
  }

  // initialize sensor
  while (!particleSensor.begin(Wire, I2C_SPEED_FAST));  //use default I2C port, 400kHz speed
  particleSensor.setup(); //configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //turn off Green LED

  // set up BLE communication
  BLE.setLocalName("Arduino Heart Rate Monitor");   //BLE Name
  BLE.setAdvertisedService(heartRateService); //advertisment heart rate service
  heartRateService.addCharacteristic(heartRateChar);  //add heart rate characteristic to heart rate service
  BLE.addService(heartRateService); //add the heart rate service to the BLE stack
  BLE.advertise();  //start advertising

}


void loop() {
  // read bpm
  getHeartRate();

  // check if central device is connected
  BLEDevice central = BLE.central();

  if (central) {  //central is connected
    // indicate central is connected with RGB LED
    redLED = 0;
    greenLED = 40;
    
    while (central.connected()) {
      getHeartRate();
      heartRateChar.writeValue(beatAvg);  //writing values to the characteristic
    }
  }
  else {
    // indicate central is disconnected with RGB LED
    redLED = 40;
    greenLED = 0;
  }
}



void getHeartRate() {
  // write values to RGB led
  nicla::leds.setColor(redLED, greenLED, blueLED);

  //read intensity of IR light
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue)) {  //a beat occured
    blueLED = 255;  //indicate pulses with blue LED

    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20) { //ignore too high or too low bpm, could be caused by removed finger
      rates[rateSpot++] = (byte)beatsPerMinute; //store reading in the array
      rateSpot %= RATE_SIZE; //wrap variable

      //claculate average of readings
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }
  else blueLED = 0;

  // Serial.print("IR: ");
  // Serial.print(irValue);
  // Serial.print("   ");
  
  // Serial.print("BPM: ");
  // Serial.print(beatsPerMinute);
  // Serial.print("   ");

  // Serial.print("Avg BPM: ");
  // Serial.print(beatAvg);

  // if (irValue < 50000) Serial.print(" No finger?");

  // Serial.println();

}