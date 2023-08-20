const int FIRST_PIN = 2;
const int PIN_COUNT = 3;

const float TIME_BUFFER = 250;
float last_trigger = 0;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < PIN_COUNT; i++){
    pinMode(FIRST_PIN + i, INPUT_PULLUP);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < PIN_COUNT; i++){
    if ( digitalRead(FIRST_PIN + i) == LOW){
      Serial.println(i);
    } 
  }

}
