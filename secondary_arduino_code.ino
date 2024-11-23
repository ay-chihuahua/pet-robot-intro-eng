#include <ArduinoBLE.h>

BLEService commandService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Custom service UUID
BLEStringCharacteristic commandCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 10); // Command characteristic

void setup() {
    // Initialize Serial Monitor for debugging
    Serial.begin(9600);
    while (!Serial);

    // Initialize Serial1 for communication with the Secondary Arduino
    Serial1.begin(9600);  // Set the baud rate for Serial1 (TX/RX to the Secondary Arduino)

    // Initialize BLE
    if (!BLE.begin()) {
        Serial.println("Starting BLE failed!");
        while (1);
    }

    // Set up BLE device details
    BLE.setLocalName("PrimaryArduino");
    BLE.setAdvertisedService(commandService);           // Advertise the custom service
    commandService.addCharacteristic(commandCharacteristic); // Add characteristic to service
    BLE.addService(commandService);                     // Add service to BLE stack

    // Start advertising
    BLE.advertise();
    Serial.println("Primary Arduino is advertising over Bluetooth!");
}

void loop() {
    // Wait for a BLE central to connect
    BLEDevice central = BLE.central();

    if (central) {
        Serial.print("Connected to central: "); // runs if device is connected
        Serial.println(central.address());

        // While connected, check for data written to the characteristic
        while (central.connected()) {
            if (commandCharacteristic.written()) {
                // Read the command from Bluetooth
                String command = commandCharacteristic.value();
                Serial.print("Received command via Bluetooth: ");
                Serial.println(command);

                // Forward the command to the Secondary Arduino over Serial1
                Serial1.println(command);
                Serial.println("Command sent to Secondary Arduino over Serial1.");
            }
        }

        // Once disconnected
        Serial.print("Disconnected from central: ");
        Serial.println(central.address());
    }
}
