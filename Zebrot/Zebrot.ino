const int FIRST_PIN = 2;
const int FIRST_EVENT_ID = 3;
const int PLAYER_COUNT = 3;

const float TIME_BUFFER = 250;
float last_trigger[PLAYER_COUNT] = {0};
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < PLAYER_COUNT; i++){
    pinMode(FIRST_PIN + i, INPUT_PULLUP);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < PLAYER_COUNT; i++){
    if (last_trigger[i] + TIME_BUFFER  < millis() && digitalRead(FIRST_PIN + i) == 0){
      Serial.print(FIRST_EVENT_ID + i);
      Serial.println(":none");
      last_trigger[i] = millis ()+ TIME_BUFFER;
    } 
  }

}
