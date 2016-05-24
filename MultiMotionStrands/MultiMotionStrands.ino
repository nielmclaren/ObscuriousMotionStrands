
int inputPin = 2;
int pirState = LOW;

int outputPinCount = 7;
int outputPins[] = {3, 4, 5, 6, 7, 8, 9};
unsigned long activateMs[7];
unsigned long deactivateMs[7];
 
void setup() {
  randomSeed(analogRead(0));
  
  pinMode(inputPin, INPUT);
 
  setupOutputPins();
  setupActivationTimings();
}

void setupOutputPins() {
  for (int i = 0; i < outputPinCount; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
}

void setupActivationTimings() {
  for (int i = 0; i < outputPinCount; i++) {
    activateMs[i] = 0;
    deactivateMs[i] = 0;
  }
}
 
void loop() {
  int reading = digitalRead(inputPin);
  updateActivationTimings(reading);
  updateOutputPins();
}

void updateActivationTimings(int val) {
  if (val == HIGH) {
    setActivationTimings();
    if (pirState == LOW) {
      pirState = HIGH;
    }
  } else {
    setDeactivationTimings();
    if (pirState == HIGH) {
      pirState = LOW;
    }
  }
}

void setActivationTimings() {
  unsigned long now = millis();
  for (int i = 0; i < outputPinCount; i++) {
    activateMs[i] = now + random(500);
    deactivateMs[i] = 0;
  }
}

void setDeactivationTimings() {
  unsigned long now = millis();
  for (int i = 0; i < outputPinCount; i++) {
    activateMs[i] = 0;
    deactivateMs[i] = now + random(2000);
  }
}

void updateOutputPins() {
  unsigned long now = millis();
  for (int i = 0; i < outputPinCount; i++) {
    updateOutputPin(i);
  }
}

void updateOutputPin(int i) {
  unsigned long now = millis();
  if (activateMs[i] != 0 && activateMs[i] < now) {
    activateMs[i] = 0;
    deactivateMs[i] = 0;
    digitalWrite(outputPins[i], HIGH);
  }
  if (deactivateMs[i] != 0 && deactivateMs[i] < now) {
    activateMs[i] = 0;
    deactivateMs[i] = 0;
    digitalWrite(outputPins[i], LOW);
  }
}

