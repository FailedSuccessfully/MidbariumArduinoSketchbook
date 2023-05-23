#define BUTTON_PIN 4

bool is_pressed;
int last_state;
const long PRINT_TIME = 500;

unsigned long last_print;

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  is_pressed = false;
  last_state = digitalRead(BUTTON_PIN);
  last_print = millis();
}
void loop()
{
  unsigned long now = millis();
  int button_state = digitalRead(BUTTON_PIN);
  if (button_state != last_state && now - last_print > PRINT_TIME){
    if (button_state == LOW){
      Serial.println(button_state);
      last_print = now;
    }
    
  }
  last_state = button_state;
}