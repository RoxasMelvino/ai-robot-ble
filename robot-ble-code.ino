
#include <ArduinoBLE.h>
#include "CustomFunctions.h"

// There are redundant comments for our sanity, in case we forget what this code does
// The peripheral device here is the Arduino board

BLEService RobotControlService("d9983f88-e3f4-4160-827f-5b9f36a070dd");                                   // Custom Service UUID
BLEStringCharacteristic driveCmdChrstic("d9983f88-e3f4-4160-827f-5b9f36a070de", BLERead | BLEWrite, 20);  // enable read write permissions on this characteristic. changed the last character of uuid from a 'd' to an 'e'
float x = 0.0, y = 0.0, w = 0.0; 

void setup() {
  Serial.begin(9600);
  lcdInit();

  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1)
      ;  // denial of service
  }

  // Set advertising packetes
  BLE.setLocalName("Clanker");                    // this is what the central device (iPhone in this case for now) will see in the bluetooth list
  BLE.setAdvertisedService(RobotControlService);  // specific service the peripheral device (the board) will provide

  // Add characteristics to service
  RobotControlService.addCharacteristic(driveCmdChrstic);

  // Add the service
  BLE.addService(RobotControlService);

  // Set an initial value for the characteristic  
  driveCmdChrstic.writeValue("0, 0, 0");  // "velocity x, velocity y, rotational velocity ω", where (x, y, and ω) ∈ [-1.0, 1.0]

  // Send the advertising packets. You should now see the arduino on the central (or client) device bluetooth list
  BLE.advertise();
}

void loop() {
  BLEDevice central = BLE.central(); // listen for central devices. 

  String driveCmds = driveCmdChrstic.value();

  if (central) {
    // lcdPrintVals(x, y, w);
  }
  
  while (central.connected()) {
    if (driveCmdChrstic.written()) {
      driveCmds = driveCmdChrstic.value(); 
      
      if (driveCmds.startsWith("X:"))      { x = driveCmds.substring(driveCmds.indexOf(":") + 1).toFloat(); } // starting index is inclusive      
      else if (driveCmds.startsWith("Y:")) { y = driveCmds.substring(driveCmds.indexOf(":") + 1).toFloat(); }
      else if (driveCmds.startsWith("W:")) { w = driveCmds.substring(driveCmds.indexOf(":") + 1).toFloat(); }
      lcdPrintVals(x, y, w); 
    }
  }
}
