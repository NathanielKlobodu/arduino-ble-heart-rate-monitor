<!--
  * Create links to hardware and software
  * Add about me section



-->






# Arduino Pulse Oximeter with BLE

add serial monitor debugging


  <img src="images/setup.jpg" alt = "setup" width="780">
  This project demonstrates how to use the MAX30102 pulse oximeter and an Arduino board to measure the user's heart rate and blood oxygen saturation (SpO2) level. The readings are transmitted over Bluetooth Low Energy (BLE) to a central device, such as a smartphone or tablet.
  The project consists of an Arduino sketch that reads the sensor data and communicates with the BLE module, as well as a wiring diagram that shows how to connect the MAX30102 sensor to the Arduino board.

## Technical Specifications
### Hardware
  * Arduino Nicla Sense ME
  * MAX30102 pulse oximeter and heart rate sensor
  * 3.7V LiPo battery
  * Jumper wires
  
### Software
  * [Arduino IDE](https://www.arduino.cc/en/software)

## Getting Started
### Wiring
Connect the MAX30102 sensor to the Arduino Nicla Sense ME as follows:
  * SDA pin to ////////////
  * SCL pin to /////////
  * VCC pin to ///////////
  * GND pin to GND
connext battery as follows

### Installation
  * Clone or download this repository to your computer.
  * Open the pulse_oximeter_ble.ino sketch in the Arduino IDE.
  *install board manager
  * Install the following libraries using the Library Manager (Tools > Manage Libraries):
    1. ArduinoBLE
    2. Wire
    3. MAX30105 by sparkfun
    4. Nicla_System
  * Connect your Arduino board to your computer via USB.
  * Select your board and port in the Arduino IDE (Tools > Board and Tools > Port).
  * Upload the sketch to the Arduino board (Sketch > Upload).
Open the Serial Monitor (Tools > Serial Monitor) to view the sensor data and BLE status if enabled.
nb: comment out serial communication code when deploying to make the execution more efficient and accurate

### Usage
Turn on the Arduino board and the central device.
Scan for available BLE devices on the central device and connect to the Arduino board.
The heart rate and SpO2 readings will be displayed on the central device in real-time.



Contributing
If you have any suggestions, bug reports, or contributions, please feel free to open an issue or a pull request.


Acknowledgments
This project was inspired by the SparkFun MAX3010x Pulse and Proximity Sensor Library and the Arduino Heart Rate Monitor with Bluetooth Low Energy (BLE) project by RoGeorge.
