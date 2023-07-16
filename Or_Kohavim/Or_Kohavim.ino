const int readPin=A0;
int readOut;
float rate = 1.0 / 1023.0;
float highest, lowest;
void setup() {
  // put your setup code here, to run once:
  pinMode(readPin, INPUT);
  readOut = 0;
  highest = 0;
  lowest = 1;
  Serial.begin(9600);

}

void loop() {
  readOut = analogRead(readPin);
  if (readOut > highest){
    highest = readOut;
  }
  if (readOut < lowest){
    lowest = readOut;
  }
  int value = map(readOut, lowest, highest, 0, 1);
  Serial.println(value * rate);
  delay(100);
}
