#define LED_PIN 8 

string trimCommand(command);

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    while (!Serial);
    Serial.begin(9600);

    Serial.println("Secondary Arduino ready and working!");
}

/* TO-DO:
  Write a separate function for trimming
  Maybe write seperate functions for each command
  Remove commented out code if what is written works
*/
void loop() {
    string command = ""; // might be redundant
    
    if (Serial.available() > 0) { // checks if the command is received from the primary Arduino
        /*String command = Serial.readStringUntil('\n');
        command.trim();
        Serial.print("Received command from Primary Arduino: ");
        Serial.println(command);*/

        trimCommand(command); // function to make command match switch statement

        switch(trimmedCommand){ // depending on what the command says, run specified state
            case "toggle"; 
                digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // example case for testing.
                Serial.println("LED state toggled!"); // consider making function so code is cleaner
                break;
            default:
                Serial.println("Error, command not accepted");
                break;
        }
        /*
        if (command == "toggle") {
            digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
            Serial.println("LED state toggled on Secondary Arduino.");
        } else {
            Serial.println("Unknown command received.");
        }
        */
    }
}

// /*
string trimCommand(command){ // trims command so no whitespace or new lines exist
        String command = Serial.readStringUntil('\n');
        command.trim();
        Serial.print("Received command from Primary Arduino: ");
        Serial.println(command);
    return trimmedCommand;
}
// */
