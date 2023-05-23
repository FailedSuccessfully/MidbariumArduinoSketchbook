const int first_trigger_pin = 8;
const int trigger_count = 3;
const int reads_per_frame = 100;

int reads_this_loop[trigger_count];
float has_triggerd_once[trigger_count];

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < trigger_count; i++){
    pinMode(first_trigger_pin + i, INPUT_PULLUP);
    reads_this_loop[i] = 0;
    has_triggerd_once[i] = false;
  }

  Serial.begin(9600);

}

void loop() {
  for (int j = 0; j < reads_per_frame; j++){
    for (int i = 0; i < trigger_count; i++){
      reads_this_loop[i] +=  digitalRead(first_trigger_pin + i);
    }
  }

  for (int k = 0; k < trigger_count; k++){
    if (reads_this_loop[k] == 0){
      if (!has_triggerd_once[k]){
        Serial.println(k);
        has_triggerd_once[k] = true;
      }
    }
    else {
      has_triggerd_once[k] = false;
    }
    reads_this_loop[k] = 0;
  }
}
