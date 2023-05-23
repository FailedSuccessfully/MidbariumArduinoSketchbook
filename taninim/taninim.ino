// constants won't change. They're used here to set pin numbers:
int ropes[] = {2, 6, 10, 22};
const int ropeEvent = 12;
const float message_time = 50;
float next_message = 50;

void setup() {
Serial.begin(9600);
  for (int i =0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      pinMode(ropes[i] + j, INPUT_PULLUP);
    }
  }
}

void loop() {

  // if (millis() > next_message){
    for (int i =0; i < 4; i++){
      int val = digitalRead(ropes[i]);
      if (val == 0){
        // Serial.print("r~");
        Serial.print(ropeEvent + i);
        Serial.println(":none");
      }
      for (int j = 0; j < 3; j++) {
        int b = digitalRead(ropes[i] + j + 1);
        if (b == 0){
          // Serial.print("b~");
          Serial.print(j + i*3);
          Serial.println(":none");
        }
      }
  //   }
  //   next_message = millis() + message_time;
   }
}
