const int FIRST_PIN = 2;
const int PLAYER_COUNT = 3;
const int BUTTON_COUNT = 4;
const int TOTAL_PINS = PLAYER_COUNT * BUTTON_COUNT;

bool has_triggered_once[TOTAL_PINS];


// const float message_time = 500;
// float next_message = 50;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  for (int i = 0; i < TOTAL_PINS; i++){
    pinMode(FIRST_PIN + i, INPUT_PULLUP);
    has_triggered_once[i] = false;
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < TOTAL_PINS; i++){
    if (digitalRead(FIRST_PIN + i) == LOW)
    {
      if (!has_triggered_once[i]){
          Serial.print(i);
          Serial.println(":none");
          has_triggered_once[i] = true;
      }
    } else {
      has_triggered_once[i] = false;
    }
  }

  // if (millis() > next_message){
  //   for (int j = 0; j < TOTAL_PINS; j++){
  //     has_triggered_once[j] = false;
  //   }
    
  //   next_message = millis() + message_time;
  // }
}
