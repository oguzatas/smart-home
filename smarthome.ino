#include <Servo.h>

int leds[] = {22, 24, 26, 28};
int switches[] = {23, 25, 27, 29};

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int potPin = A0;

int trigPin = 6;
int echoPin = 7;
int securityLed = 8;

int servoPin = 12;
int servoButtonPin = 5;
Servo doorLock;

// Servo toggle
bool doorOpen = false;
bool lastButtonState = LOW;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(switches[i], INPUT_PULLUP);  // PULLUP aktif
  }

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(securityLed, OUTPUT);

  doorLock.attach(servoPin);
  pinMode(servoButtonPin, INPUT_PULLUP); // PULLUP burada da önemli

  Serial.begin(9600);
}

void loop() {
  // Oda ışıkları kontrolü
  for (int i = 0; i < 4; i++) {
    bool pressed = digitalRead(switches[i]) == LOW;
    digitalWrite(leds[i], pressed ? HIGH : LOW);
  }

  // Sıcaklık simülasyonu (potansiyometre)
  int potValue = analogRead(potPin);
  int temp = map(potValue, 0, 1023, 0, 255);

  if (temp < 85) { // Soğuk
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
  } else if (temp < 170) { // Ilık
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  } else { // Sıcak
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }

  // Güvenlik sensörü
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration / 29 / 2;

  if (distance < 20) {
    digitalWrite(securityLed, HIGH);
  } else {
    digitalWrite(securityLed, LOW);
  }

  // Servo butonu toggle mantığıyla kontrol
  bool currentButtonState = digitalRead(servoButtonPin) == LOW;

  if (currentButtonState && !lastButtonState) {
    doorOpen = !doorOpen;
    doorLock.write(doorOpen ? 90 : 0);
    delay(300); // Debounce etkisi
  }

  lastButtonState = currentButtonState;
}

