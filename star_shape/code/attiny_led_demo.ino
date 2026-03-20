/*
  Star Shape ATtiny85 LED Badge Demo - 5 LED Version

  This example uses 5 LEDs with charlieplexing on:
  - PB0
  - PB1
  - PB2

  Push button:
  - PB4

  LED mapping assumed in this example:
  - LED1: PB0 -> PB1
  - LED2: PB1 -> PB0
  - LED3: PB0 -> PB2
  - LED4: PB2 -> PB0
  - LED5: PB1 -> PB2
*/

const int buttonPin = 4;   // PB4

const int pinA = 0;        // PB0
const int pinB = 1;        // PB1
const int pinC = 2;        // PB2

int mode = 0;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// --- Helper functions ---

void allPinsHiZ() {
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);

  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
}

void driveLed(int anodePin, int cathodePin) {
  allPinsHiZ();

  pinMode(anodePin, OUTPUT);
  pinMode(cathodePin, OUTPUT);

  digitalWrite(anodePin, HIGH);
  digitalWrite(cathodePin, LOW);
}

void ledOff() {
  allPinsHiZ();
}

// LED map
void lightLED1() { driveLed(pinA, pinB); } // PB0 -> PB1
void lightLED2() { driveLed(pinB, pinA); } // PB1 -> PB0
void lightLED3() { driveLed(pinA, pinC); } // PB0 -> PB2
void lightLED4() { driveLed(pinC, pinA); } // PB2 -> PB0
void lightLED5() { driveLed(pinB, pinC); } // PB1 -> PB2

void showLed(int ledNumber, int durationMs) {
  unsigned long startTime = millis();

  while (millis() - startTime < (unsigned long)durationMs) {
    switch (ledNumber) {
      case 1: lightLED1(); break;
      case 2: lightLED2(); break;
      case 3: lightLED3(); break;
      case 4: lightLED4(); break;
      case 5: lightLED5(); break;
      default: ledOff(); break;
    }
    delay(2);  // refresh for visible brightness
  }

  ledOff();
}

// --- Button handling ---

void handleButton() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      mode++;
      if (mode > 3) {
        mode = 0;
      }
    }
  }

  lastButtonState = reading;
}

// --- Animation modes ---

void sequentialBlink() {
  showLed(1, 120);
  showLed(2, 120);
  showLed(3, 120);
  showLed(4, 120);
  showLed(5, 120);
}

void alternatingBlink() {
  // Group A
  showLed(1, 80);
  showLed(3, 80);
  showLed(5, 80);

  delay(80);

  // Group B
  showLed(2, 80);
  showLed(4, 80);

  delay(80);
}

void allFlash() {
  unsigned long startTime = millis();

  while (millis() - startTime < 250UL) {
    lightLED1(); delay(2);
    lightLED2(); delay(2);
    lightLED3(); delay(2);
    lightLED4(); delay(2);
    lightLED5(); delay(2);
  }

  ledOff();
  delay(180);
}

void rotatingPattern() {
  showLed(1, 70);
  showLed(2, 70);
  showLed(3, 70);
  showLed(4, 70);
  showLed(5, 70);
}

// --- Main program ---

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  ledOff();
}

void loop() {
  handleButton();

  switch (mode) {
    case 0:
      sequentialBlink();
      break;
    case 1:
      alternatingBlink();
      break;
    case 2:
      allFlash();
      break;
    case 3:
      rotatingPattern();
      break;
    default:
      mode = 0;
      break;
  }
}
