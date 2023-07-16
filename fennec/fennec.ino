bool phase;
int p1btn = 2;
int p2btn = 6;
int p1rel = 10
int p2rel = 11;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++){
    pinMode(p1btn + i, INPUT_PULLUP);
    pinMode(p2btn + i, INPUT_PULLUP);
  }
    pinMode(p1rel, OUTPUT);
    pinMode(p2rel, OUTPUT);

    phase = false;
    Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int p;
  if (phase){
    p = 6;
  } else {
    p = 2;
  }

  for (int i = 0; i < 4; i++){
    if (digitalRead(p+i) == LOW){
      Serial.write(p+i);
      alter();
    }
  }
}

void alter() {
  phase = !phase;

  digitalWrite(p1rel, phase);
  digitalWrite(p2rel, !phase);
}


