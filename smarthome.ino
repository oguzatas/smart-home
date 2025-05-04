int potPin = A0;
int redPin = 3;
int greenPin = 5;
int bluePin = 6;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(potPin);
  float voltage = value * (5.0 / 1023.0);
  float temp = voltage * 100;

  Serial.print("Sicaklik: ");
  Serial.println(temp);

  if (temp <= 20) {
    setColor(0, 0, 255);
  } else if (temp <= 30) {
    setColor(0, 255, 0);
  } else if (temp <= 40) {
    setColor(255, 255, 0);
  } else {
    setColor(255, 0, 0);
  }

  delay(500);
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
