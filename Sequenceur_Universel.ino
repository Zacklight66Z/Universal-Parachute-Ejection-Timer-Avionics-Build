#include <Servo.h>

const int buzzerPin = 11;
const int jackDetectPin = 6;
const int ledGreenPin = 12;
const int ledYellowPin = 4;
const int ledRedPin = 8;
const int servoPin = 9;

Servo myServo;

// States
bool jackConnected = false;
bool lastJackState = true;
bool dangerActivated = false;

unsigned long yellowLedStartTime = 0;
uint32_t buzzerLastTime=0;
uint32_t blinkTimeBuzzerRest=1000;
const unsigned long yellowLedDuration = 6000; // Yellow alert duration
unsigned long lastBlinkTime = 0;
bool yellowLedState = false;
const unsigned long blinkInterval = 250;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);

  pinMode(buzzerPin, OUTPUT);
  pinMode(jackDetectPin, INPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);

  digitalWrite(ledGreenPin, LOW);
  digitalWrite(ledYellowPin, LOW);
  digitalWrite(ledRedPin, LOW);
  noTone(buzzerPin);
  myServo.write(40);
}

void loop() {
  checkJackConnection();
  unsigned long currentTime = millis();

  if (jackConnected) {
    // Normal state
    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledYellowPin, LOW);
    digitalWrite(ledRedPin, LOW);
    //------
    if (currentTime-buzzerLastTime >= blinkTimeBuzzerRest){
      tone(buzzerPin, 2000, (500));
      buzzerLastTime=millis();
    }
    //------
    myServo.write(40);
    dangerActivated = false;
  } else {
    
    
    if (!dangerActivated && (currentTime - yellowLedStartTime < yellowLedDuration)) {
      // Yellow alert (blinking)
      if (currentTime - lastBlinkTime >= blinkInterval) {
        lastBlinkTime = currentTime;
        yellowLedState = !yellowLedState;
        digitalWrite(ledYellowPin, yellowLedState);
        digitalWrite(ledGreenPin, LOW);
        tone(buzzerPin, 2000, 70);
      }
    } else {
      // Red alert
      if (!dangerActivated) {
        digitalWrite(ledYellowPin, HIGH);
        digitalWrite(ledGreenPin, HIGH);
        digitalWrite(ledRedPin, HIGH);
        tone(buzzerPin, 2000); // continuous bip
        myServo.write(-5);
        dangerActivated = true;
      }
    }
  }
}

void checkJackConnection() {
  bool currentJackState = digitalRead(jackDetectPin);
  if (currentJackState != lastJackState) {
    lastJackState = currentJackState;
    if (!currentJackState) {
      // Jack disconected : start yellow alert sequence
      yellowLedStartTime = millis();
      lastBlinkTime = millis();
      yellowLedState = false;
      digitalWrite(ledYellowPin, LOW);
    }
  }
  jackConnected = currentJackState;
}
   