#define LED_INDICATOR 0

void setup() {
  pinMode(LED_INDICATOR, OUTPUT);
}

void loop() {
  digitalWrite(LED_INDICATOR, HIGH);
  delay(500);
  digitalWrite(LED_INDICATOR, LOW);
  delay(500);
}
