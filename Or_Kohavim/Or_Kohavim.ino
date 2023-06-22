const int readPin=A0;
int readOut;
float rate = 1.0 / 1023.0;
void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  readOut = 0;
  Serial.begin(9600);

}

void loop() {
  readOut = analogRead(readPin);
  Serial.println(readOut * rate);
  delay(100);
}
