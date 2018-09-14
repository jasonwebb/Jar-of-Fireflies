/*
  Jar of Fireflies using ATTiny85

  DESCRIPTION:
    An Arduino sketch for the ATTiny85 (using HLT's bootloader)
    that flashes six charlieplexed LEDs to mimic the behavior of
    fireflies. Using a piezo element and tactile button in parallel
    the LED array can react to human interactions.
*/

// Pin assignments
const byte pinA = 0;        // Physical pin 5 (PB0, MOSI, PWM)
const byte pinB = 1;        // Physical pin 6 (PB1, MISO, PWM)
const byte pinC = 2;        // Physical pin 7 (PB2, SCK, ADC1)
const byte triggerPin = 4;  // Physical pin 3 (PB4, ADC2)

// LED variables
byte currentLED;        // Number of currently active LED (1-6)
byte previousLED = -1;  // Last LED flashed so we can avoid flashing it twice in a row
byte rampUpSpeed;       // Randomly generated value for fading in LEDs
byte rampDownSpeed;     // Randomly generated value for fading out LEDs
byte numBlinks;         // Randomly generated value for number of times to flash LED whe fully faded in
int brightness;         // Current brightness (0-255) of currently active LED

// "Dance mode" trigger variables
const int triggerBufferSize = 10;      // Number of readings to store
int triggerValues[triggerBufferSize];  // Last n values of triggers
int triggerThreshold = 1;              // Minimum average value to trigger "dance mode"
int triggerCounter = 0;                // Current index in buffer array, used when filling it with readings

// Program states
const byte BEGIN = 0;         // Sets up program for a new cycle
const byte RAMP_UP = 1;       // Fades in current LED
const byte BLINKING = 2;      // Blinks the current LED when at full brightness
const byte RAMP_DOWN = 3;     // Fades out the current LED
const byte DANCE = 4;         // Flashes LEDs in fun pattern
byte CURRENT_ACTION = BEGIN;  // Start program off in BEGIN mode

void setup() {
  turnOffAll();  // Flush any stray current from the ports
}

void loop() {
  switch (CURRENT_ACTION) {

    // BEGIN ===========================================
    // Set up all the variables to flash a new LED
    case BEGIN:
      // Choose a new LED
      previousLED = currentLED;

      // Make sure it's different than the last one
      do {
        currentLED = (int) random(1, 6);
      } while (currentLED == previousLED);

      // Randomize the number of times to blink
      numBlinks = (int) random(1, 6);

      // Randomize the fade in and fade out speeds
      rampUpSpeed = random(6);
      rampDownSpeed = rampUpSpeed * 2;

      brightness = 0;
      CURRENT_ACTION = RAMP_UP;
      break;

    // RAMP UP ========================================
    // Fade in the LED
    case RAMP_UP:
      analogOn(currentLED, brightness);
      delay(rampUpSpeed);

      if (brightness >= 255) {
        CURRENT_ACTION = BLINKING;
        brightness = 0;
      } else {
        brightness++;
      }

      break;

    // BLINKING ====================================
    // Blink the LED a certain number of times
    case BLINKING:
      analogOn(currentLED, 0);
      delay(random(10, 50));
      analogOn(currentLED, 255);
      delay(random(30, 100));

      if (numBlinks > 0) {
        numBlinks--;
      } else {
        CURRENT_ACTION = RAMP_DOWN;
        brightness = 255;
      }

      break;

    // RAMP DOWN ===========================================
    // Fade out the LED
    case RAMP_DOWN:
      analogOn(currentLED, brightness);
      delay(rampDownSpeed);

      if (brightness == 0) {
        CURRENT_ACTION = BEGIN;
      } else {
        brightness--;
      }

      break;

    // DANCE ==============================================
    // Flash each LED, one at a time, six times in a row
    case DANCE:
      for (int j = 0; j < 6; j++) {
        for (int i = 1; i <= 6; i++) {
          turnOn(i);
          delay(50);
          turnOff(i);
          delay(50);
        }
      }

      // Clear the trigger value buffer so dance mode isn't immediately retriggered
      for(int i = 0; i < triggerBufferSize; i++) {
        triggerValues[i] = 0;
      }

      CURRENT_ACTION = BEGIN;

      break;
  }

  // Poll the "dance mode" triggers
  checkDanceTriggers();
}

// Turn on a single LED to full brightness
void turnOn(byte led) {
  analogOn(led, 255);
}

// Turn off an LED completely
void turnOff(byte led) {
  analogOn(led, 0);
}

// Turn off all LEDs and drain any remaining current
void turnOffAll() {
  for (int i = 0; i <= 2; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

// Write an analog value to an LED
void analogOn(byte led, byte value) {
  switch (led) {
    case 1:
      pinMode(pinA, OUTPUT);
      pinMode(pinB, OUTPUT);
      pinMode(pinC, INPUT);

      digitalWrite(pinA, LOW);
      analogWrite(pinB, value);
      break;
    case 2:
      pinMode(pinA, OUTPUT);
      pinMode(pinB, OUTPUT);
      pinMode(pinC, INPUT);

      digitalWrite(pinB, LOW);
      analogWrite(pinA, value);
      break;
    case 3:
      pinMode(pinA, INPUT);
      pinMode(pinB, OUTPUT);
      pinMode(pinC, OUTPUT);

      digitalWrite(pinC, HIGH);
      analogWrite(pinB, 255 - value);
      break;
    case 4:
      pinMode(pinA, INPUT);
      pinMode(pinB, OUTPUT);
      pinMode(pinC, OUTPUT);

      digitalWrite(pinC, LOW);
      analogWrite(pinB, value);
      break;
    case 5:
      pinMode(pinA, OUTPUT);
      pinMode(pinB, INPUT);
      pinMode(pinC, OUTPUT);

      digitalWrite(pinC, HIGH);
      analogWrite(pinA, 255 - value);
      break;
    case 6:
      pinMode(pinA, OUTPUT);
      pinMode(pinB, INPUT);
      pinMode(pinC, OUTPUT);

      digitalWrite(pinC, LOW);
      analogWrite(pinA, value);
      break;
  }
}

// Poll the "dance mode" triggers to find out if program state needs to change
void checkDanceTriggers() {
  // Fill up the buffer with readings
  if (triggerCounter < triggerBufferSize) {
    int val = analogRead(triggerPin);
    triggerValues[triggerCounter] = val;
    triggerCounter++;
    return;
  }

  // Once the buffer is full, find the average
  int avg = 0;

  for (int i = 0; i < triggerBufferSize; i++)
    avg += triggerValues[i];

  avg = avg / triggerBufferSize;

  // If the average is above the threshold, initiate "dance mode" state
  if (avg >= triggerThreshold) {
    CURRENT_ACTION = DANCE;
  }

  // Reset counter
  triggerCounter = 0;
}