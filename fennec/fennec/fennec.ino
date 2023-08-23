const int fpb = 2;
const int spb = 6;
const int fpr = 10;
const int spr = 11;

bool p_turn = true;
int turns = 0;
float time;

void setup() {
  for (int i = 0; i < 4; i++){
    pinMode(fpb + i, INPUT_PULLUP);
    pinMode(spb + i, INPUT_PULLUP);
  }
  pinMode(fpr, OUTPUT);
  pinMode(spr, OUTPUT);
  digitalWrite(spr, HIGH);
  digitalWrite(fpr, HIGH);
  Serial.begin(115200);
  while(!Serial);
  time = millis();
}

void loop() {
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
  }

  digitalWrite(playerRelay, LOW);
  for (int i = 0; i < 4; i++ ){
    int currentButton = playerButton + i;
    if (digitalRead(currentButton) == LOW){
      Serial.println(currentButton - 1);
      Serial.println(turns);
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
  }


///////////////////////////////
/*
  digitalWrite(fpr, LOW);
  while (p_turn){
    for (int i = fpb; i < fpb + 4; i++){
      if (digitalRead(i) == LOW){
        Serial.println(i - 1);
        p_turn = false;
        digitalWrite(fpr, HIGH);
        delay(5000);
      }
    }
    if (millis() - time > 60000){

    }
    
  }
  digitalWrite(spr, LOW);
  while (!p_turn){
    for (int j = spb; j < spb + 4; j++){
      if (digitalRead(j) == LOW){
        Serial.println(j - 1);
        p_turn = true;
        digitalWrite(spr, HIGH);
        delay(5000);
      }
    }
    
  }
  turns++;
  if (turns >= 4){
    turns = 0;
    digitalWrite(fpr, LOW);
    digitalWrite(spr, LOW);

    delay(10000);
    digitalWrite(fpr, HIGH);
    digitalWrite(spr, HIGH);

    }
    */
}
  
