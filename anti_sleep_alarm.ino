const int sensorPin = 2;     // Pin connected to the IR sensor (or eye detection sensor)
const int motorPin = 8;      // Pin connected to the motor
const int buzzerPin = 9;     // Pin connected to the buzzer

unsigned long eyesOpenTime = 0; // Variable to store the time when eyes were first detected open

void setup() {
  pinMode(motorPin, OUTPUT);   // Set motorPin as an OUTPUT
  pinMode(buzzerPin, OUTPUT);  // Set buzzerPin as an OUTPUT
  pinMode(sensorPin, INPUT);   // Set sensorPin as an INPUT
  digitalWrite(motorPin, HIGH); // Turn on the motor initially
}

void loop() {
  if (!digitalRead(sensorPin)) {
    // Eyes are closed, reset the timer
    eyesOpenTime = 0;
    
    // Start buzzer if eyes are closed for 2 seconds
    delay(2000);
    if (!digitalRead(sensorPin)) {
      digitalWrite(buzzerPin, HIGH);
    }
    
    // Stop motor if eyes are closed for 4 seconds
    delay(2000); // Additional delay after starting buzzer
    if (!digitalRead(sensorPin)) {
      digitalWrite(motorPin, LOW);
    }
  } else {
    // Eyes are open, reset the timer and turn off buzzer
    eyesOpenTime = millis();
    digitalWrite(buzzerPin, LOW);
    
    // Turn on motor if eyes were closed for less than 4 seconds
    if (millis() - eyesOpenTime < 4000) {
      digitalWrite(motorPin, HIGH);
    }
  }
}
