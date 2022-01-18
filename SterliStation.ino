int switchBtn=2;
int buzzer=3;
int strtUpBtn=4;
int statusLED=6;
bool button_history = false;
bool latch = false;
bool door_state = false;
int milli;
int seconds;
int minutes;
bool LED_state;
void(* resetFunc) (void) = 0;

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
  // put your setup code here, to run once:
  lcd.noCursor();
  lcd.noBlink();
  Serial.begin(9600);
  lcd.begin(16, 2);
  BOOTUP();
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  pinMode(strtUpBtn, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(status_LED, OUTPUT);
  
  HOME();
  BUTTON_TRUE();
}

void loop() {
  // put your main code here, to run repeatedly:
  SANITIZE();
}
