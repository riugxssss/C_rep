const int LED_PINS[] = {11, 12, 13};
const int NUM_LEDS = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino ready! Send '1', '2' or '3' to control the LEDs.");

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void controlLed(int ledIndex) {
  if (ledIndex >= 0 && ledIndex < NUM_LEDS) {
    int currentLedPin = LED_PINS[ledIndex];

    digitalWrite(currentLedPin, HIGH);
    Serial.print("LED ");
    Serial.print(currentLedPin);
    Serial.println(" ON");

    delay(1000);

    digitalWrite(currentLedPin, LOW);
    Serial.print("LED ");
    Serial.print(currentLedPin);
    Serial.println(" OFF");
  } else {
    Serial.println("Error: Invalid LED index.");
  }
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    switch (command) {
      case '1':
        controlLed(0);
        break;
      case '2':
        controlLed(1);
        break;
      case '3':
        controlLed(2);
        break;
      default:
        Serial.println("Unknown command.");
        Serial.print("You sent: '");
        Serial.print(command);
        Serial.println("'\nAvailable commands:");
        Serial.println("  '1' = Turn ON/OFF LED 11");
        Serial.println("  '2' = Turn ON/OFF LED 12");
        Serial.println("  '3' = Turn ON/OFF LED 13");
        break;
    }
  }
}
