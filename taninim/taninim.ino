// constants won't change. They're used here to set pin numbers:
const int ropes[] = {2, 6, 10, 22};
const int ropeEvent = 12;
bool flags[4][4];
void setup() {
Serial.begin(9600);
  for (int i =0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      pinMode(ropes[i] + j, INPUT_PULLUP);
    }
  }
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      flags[i][j] = false;
    }
  }
}

void loop() {
    for (int i =0; i < 4; i++){
      int val = digitalRead(ropes[i]);
      if (val == HIGH){
        flags[i][0] = false;
      }
      else if (!flags[i][0]){
        Serial.println(ropeEvent + i);
        flags[i][0] = true;
      }
      for (int j = 1; j < 4; j++) {
        int b = digitalRead(ropes[i] + j);
        if (b == HIGH){
          flags[i][j] = false;
        }
        else if (!flags[i][j]) {
          Serial.println(j + i*3 - 1);
          flags[i][j] = true;
        }
      }
   }
}
