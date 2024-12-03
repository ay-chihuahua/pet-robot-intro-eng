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
            digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // command used to test code
            Serial.println("LED command sent.");
        } else if(command == "walkForward"){
            Serial.println("Walk forward command sent.");
        } else if(command == "walkBackwards"){
            Serial.println("Walk backwards command sent.");
        } else if(command == "layDown"){
            Serial.println("Lay down command sent.");
        } else if (command == "bark"){
            Serial.println("Bark command sent.");
        } else {
            Serial.println("Unknown command sent"); // In case there is an error with
        }
}
