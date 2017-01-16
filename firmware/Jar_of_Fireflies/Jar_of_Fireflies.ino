/*
Jar of Fireflies using ATTiny85
Author: Jason Webb
Author website: http://jason-webb.info
Author e-mail: zen.webb@gmail.com
Github repo: https://github.com/jasonwebb/Jar-of-Fireflies

GENERAL DESCRIPTION:
An Arduino sketch for the ATTiny85 (using HLT's bootloader)
that flashes six charlieplexed LEDs to mimic the behavior of
fireflies. Using a piezo detector, the LED array can react to 
taps on the enclosure.
*/

// Pin assignments
const byte pinA = 0;
const byte pinB = 1;
const byte pinC = 2;
const byte piezoPin = 2;  // analog pin 2

// LED variables
byte currentLED;
byte previousLED = -1;
byte rampUpSpeed;
byte rampDownSpeed;
byte numBlinks;
int counter;

// Piezo variables
const int piezoBufferSize = 10;
int piezoValues[piezoBufferSize];
int piezoThreshold = 1;
int piezoCounter = 0;

// Behavior states
const byte BEGIN = 0;
const byte RAMP_UP = 1;
const byte BLINKING = 2;
const byte RAMP_DOWN = 3;
const byte EXCITED = 4;
byte CURRENT_ACTION = BEGIN;

void setup() {
  // Flush any stray current from the ports
  turnOffAll();
}

void loop() {
  switch(CURRENT_ACTION) {
    
    // BEGIN =========================================
    // + Set up all the variables to flash new LED
    case BEGIN:
      // Choose a new LED
      previousLED = currentLED;
      
      do {
        currentLED = (int)random(1,6);
      } while(currentLED == previousLED);
      
      // Number of times to blink
      numBlinks = (int)random(1,6);
      
      // Fade in and fade out speed
      rampUpSpeed = random(6);
      rampDownSpeed = rampUpSpeed*2;
      
      counter = 0;
      CURRENT_ACTION = RAMP_UP;
      break;
      
    // RAMP UP ========================================
    // + Fade in the LED
    case RAMP_UP:
      analogOn(currentLED, counter);
      delay(rampUpSpeed);
      
      if(counter >= 255) {
        CURRENT_ACTION = BLINKING;
        counter = 0;
      } else {
        counter++;
      }
      
      break;
      
    // BLINKING ====================================
    // + Blink the LED a certain number of times
    case BLINKING:
      analogOn(currentLED, 0);
      delay(random(10,50));
      analogOn(currentLED, 255);
      delay(random(30,100));
      
      if(numBlinks > 0) {
        numBlinks--;
      } else {
        CURRENT_ACTION = RAMP_DOWN;
        counter = 255;
      }
      
      break;
      
    // RAMP DOWN ===========================================
    // + Fade out the LED
    case RAMP_DOWN:
      analogOn(currentLED, counter);
      delay(rampDownSpeed);
      
      if(counter == 0) {
        CURRENT_ACTION = BEGIN;
      } else {
        counter--;
      }
      
      break;
      
    // EXCITED =========================================
    // + Flash each LED, one at a time, six times in a row
    case EXCITED:
      for(int j=0; j<6; j++) {
        for(int i=1; i<=6; i++) {
          turnOn(i);
          delay(50);
          turnOff(i);
          delay(50);
        }
      }

      CURRENT_ACTION = BEGIN;

      break;
  }
  
  checkPiezo();
}

// Turn on a single LED to full brightness
void turnOn(byte led) {
  analogOn(led, 255);
}

// Turn off an LED completely
void turnOff(byte led) {
  analogOn(led, 0);
}

void turnOffAll() {
  for(int i=0; i<=2; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

// Write an analog value to an LED
void analogOn(byte led, byte value) {
  switch(led) {
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
      analogWrite(pinB, 255-value);
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
      analogWrite(pinA, 255-value);
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

void checkPiezo() {
  if(piezoCounter < piezoBufferSize) {
    // Take a reading
    int val = analogRead(piezoPin);
    piezoValues[piezoCounter] = val;
  } else {
    // Find average
    int avg = 0;
    
    for(int i=0; i<piezoBufferSize; i++)
      avg += piezoValues[i];
      
    avg = avg/piezoBufferSize;
    
    if(avg >= piezoThreshold) {
      for(int j=0; j<6; j++) {
        for(int i=1; i<=6; i++) {
          turnOn(i);
          delay(50);
          turnOff(i);
          delay(50);
        }
      }
    }
    
    // Reset counter
    piezoCounter = 0;
  }
  
  piezoCounter++;
}
