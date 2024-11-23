#include <ArduinoBLE.h>

BLEService commandService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Custom service UUID
BLEStringCharacteristic commandCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 10); // Command characteristic

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // Initialize Serial1 for communication with the Secondary Arduino
    Serial1.begin(9600);

    BLE.setLocalName("PrimaryArduino");
    BLE.setAdvertisedService(commandService);
    commandService.addCharacteristic(commandCharacteristic);
    BLE.addService(commandService);

    BLE.advertise();
    Serial.println("The primary Arduino ");
}

void loop() {
    // Wait for a BLE central to connect
    BLEDevice central = BLE.central();

    if (central) {
        Serial.print("Connected to the app!"); // runs if device is connected
        Serial.println(central.address());

        while (central.connected()) {
            if (commandCharacteristic.written()) { // comand read from app

                String command = commandCharacteristic.value();
                Serial.print("Received command via Bluetooth: ");
                Serial.println(command);

                Serial1.println(command);
                Serial.println("Command sent to Secondary Arduino over Serial1.");
            }
        }
        Serial.print("Disconnected from the app!");
        Serial.println(central.address());
    }
}
