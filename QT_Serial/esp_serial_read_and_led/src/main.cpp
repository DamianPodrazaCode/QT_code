#include <Arduino.h>

const int LED = 22;
String Command = "";
String InputData = "";
bool dataComplete = false;

void SerialDataEvants();

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 1);

  Serial.begin(115200);
}

void loop() {
  SerialDataEvants();

  if (dataComplete) {
    if (Command == "On") {
      digitalWrite(LED, 0);
      Serial.println("LED IS ON");
      delay(100);
    }
    else if (Command == "Off") {
      digitalWrite(LED, 1);
      Serial.println("LED IS OFF");
      delay(100);
    }
   // Serial.println(Command);
    dataComplete = false;
    Command = "";
    InputData = "";
  }
}

void SerialDataEvants() {
  Serial.flush();
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      dataComplete = true;
      Command = InputData;
    }
    else {
      InputData += inChar;
    }
  }
}