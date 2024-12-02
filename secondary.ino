#include <string>
#define LED_PIN 8 

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    while (!Serial);
    Serial.begin(9600);

    Serial.println("Secondary Arduino ready and working!");
}

void loop() {
    
    if (Serial.available() > 0) { // checks if the command is received from the primary Arduino
        String command = Serial.readStringUntil('\n');
        command.trim();
        Serial.print("Received command from Primary Arduino: ");
        Serial.println(command);

        if (command == "toggle") {
            digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
            Serial.println("LED state toggled on Secondary Arduino.");
        } else {
            Serial.println("Unknown command received.");
        }
    }
}
