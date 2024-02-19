const int fpb = 2;
const int spb = 6;
const int fpr = 10;
const int spr = 11;

bool p_turn = true;
int turns = 0;
float time, timet;
bool active;

#define TIMEOUT 30600000 //8.5 hours in ms

bool ReceiveSignal(){
  char signal = Serial.peek();
  bool accept = true;
  if (signal == '!'){
    active = true;
  } else if (signal == '*') {
    active = false;
  } else {
    accept = false;
  }
  return accept;
}


void setup() {
  active = true;
  for (int i = 0; i < 4; i++){
    pinMode(fpb + i, INPUT_PULLUP);
    pinMode(spb + i, INPUT_PULLUP);
  }
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(fpr, OUTPUT);
  pinMode(spr, OUTPUT);
  digitalWrite(spr, HIGH);
  digitalWrite(fpr, HIGH);
  Serial.begin(115200);
  while(!Serial);
  time = millis();
  timet = millis();
}

void loop() {
  // if (ReceiveSignal()){
  //   Serial.read();
  //   Serial.read();
  // }
  //Serial.println(millis() - timet);
  if (millis() - timet > TIMEOUT)
  {
    active = false;
  }
  delay(100);

  if (!active){
    digitalWrite(spr, HIGH);
    digitalWrite(fpr, HIGH);
    digitalWrite(LED_BUILTIN, LOW);

  }
  else{
    digitalWrite(LED_BUILTIN, HIGH);

    int playerButton, playerRelay;
    if (p_turn){
      playerButton = fpb;
      playerRelay = fpr;
    } else {
      playerButton = spb;
      playerRelay = spr;
    }

    if (millis() - time > 60000){
      p_turn = true;
      turns = 0;
      Serial.println("reset");
      time = millis();
      digitalWrite(spr, HIGH);
      digitalWrite(fpr, HIGH);
    }
    else{
      digitalWrite(playerRelay, LOW);
      for (int i = 0; i < 4; i++ ){
        int currentButton = playerButton + i;
        if (digitalRead(currentButton) == LOW){
          Serial.println(currentButton - 1);
          p_turn = !p_turn;
          delay(5000);
          digitalWrite(playerRelay, HIGH);
          turns++;
          time = millis();
        }
      }

      if (turns >= 8){
        turns = 0;
        digitalWrite(fpr, LOW);
        digitalWrite(spr, LOW);

        delay(20000);
        digitalWrite(fpr, HIGH);
        digitalWrite(spr, HIGH);
        
        time = millis();
      }
  }
}
}
