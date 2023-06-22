const int firstPin=A0;
const int count = 6;
const int SAMPLE_RATE = 50;
unsigned int readOut[count];
float rate = 1.0 / 1023.0;
void setup() {
  // put your setup code here, to run once:
  InitRead();
  Serial.begin(9600);

}

void loop() {

  // gather an amount of samples to increase accuracy and decrease jittering
  for (int sample = 0; sample < SAMPLE_RATE; sample++ ){
    for (int pin = firstPin; pin < firstPin + count; pin++){
        readOut[pin - firstPin] += analogRead(pin);
    }
  }

  Serial.print("{");
  for (int pin = firstPin; pin < firstPin + count; pin++){
    unsigned int value = readOut[pin - firstPin] / SAMPLE_RATE;
    Serial.print(value * rate);
    Serial.print(",");
  }
  Serial.println("}");
  InitRead();
}


void InitRead(){
  for (int pin = firstPin; pin < firstPin + count; pin++){
    pinMode(pin, INPUT);
    readOut[pin-firstPin] = 0;
  }
}