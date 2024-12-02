#include <ArduinoBLE.h>

BLEService commandService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLEStringCharacteristic commandCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 10);

void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial1.begin(9600);

    BLE.setLocalName("Arduino");
    BLE.setAdvertisedService(commandService);
    commandService.addCharacteristic(commandCharacteristic);
    BLE.addService(commandService);

    BLE.advertise();
}

void loop() {
    BLEDevice central = BLE.central();

    if (central) {
        Serial.print("Connected to the app!");
        Serial.println(central.address());

        while (central.connected()) {
            if (commandCharacteristic.written()) {

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
