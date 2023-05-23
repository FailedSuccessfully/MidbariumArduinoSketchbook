#include <SPI.h>

//Add the SdFat Libraries
#include <SdFat.h>
#include <FreeStack.h>

//and the MP3 Shield Library
#include <SFEMP3Shield.h>

#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
  #include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
  #include <SimpleTimer.h>
#endif

SdFat sd;
SFEMP3Shield player;

int const SENSOR_COUNT = 6;
int const SENSOR_PIN = 22;
int const CORRECT_PIN = 30;
int const INCORRECT_PIN = 31;
int const BUTTON_PIN = 29;
int const RESET_PIN = 28;


void setup() {
  
  Serial.begin(115200);
  for (int i = 0; i < SENSOR_COUNT; i++){
    int jump = i * 2;
    pinMode(SENSOR_PIN + i, INPUT);
    pinMode(CORRECT_PIN + jump, OUTPUT);
    digitalWrite(CORRECT_PIN + jump, LOW);
    pinMode(INCORRECT_PIN + jump, OUTPUT);
    digitalWrite(INCORRECT_PIN + jump, LOW);
    Serial.print(SENSOR_PIN + i);
    Serial.print(", ");
    Serial.print(CORRECT_PIN + jump);
    Serial.print(", ");
    Serial.println(INCORRECT_PIN + jump);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, INPUT_PULLUP);

  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");
  sd.ls(LS_R | LS_DATE | LS_SIZE);

  uint8_t result = player.begin();
  

  if(result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
  }

  reset();
}

void loop() {
  if (!digitalRead(RESET_PIN)){
      reset();
    }
  if (!digitalRead(BUTTON_PIN)){
    int total = 0;
    for (int i = 0; i < SENSOR_COUNT; i++){
      int jump = i*2;
      int value = digitalRead(SENSOR_PIN + i);
        Serial.print(i);
        Serial.print(" ~ ");
        Serial.println(value);
      if (value == LOW){
        // relay correct
        digitalWrite(CORRECT_PIN + jump, LOW);
        digitalWrite(INCORRECT_PIN + jump, HIGH);
      }
      else {
        // relay incorrect
        digitalWrite(CORRECT_PIN + jump, HIGH);
        digitalWrite(INCORRECT_PIN + jump, LOW);
      }
      total += value;
    }

    player.stopTrack();
    if (total == 0){
      player.playTrack(2);
    }
    delay(500);
  }
  
}

void  reset(){
  player.stopTrack();
    
  for (int i = 0; i < SENSOR_COUNT; i++){
      int jump = i*2;
      digitalWrite(CORRECT_PIN + jump, LOW);
      digitalWrite(INCORRECT_PIN + jump, LOW);
  }
}