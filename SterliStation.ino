int switchBtn = 2;
int buzzer = 3;
int strtUpBtn = 4;
int statusLED = 6;
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
  pinMode(strtUpBtn, INPUT);
  pinMode(switchBtn, INPUT);
  pinMode(statusLED, OUTPUT);
  
  HOME();
  BUTTON_TRUE();
}

void loop() {
  // put your main code here, to run repeatedly:
  SANITIZE();
}

void BOOTUP() {
  String bootUpMsgT = "-SteriliStation-";
  String bootUpMsgV = "Version 1";
  lcd.setCursor(0,0);
  lcd.print(bootUpMsgT);
  
  lcd.setCursor(4,1);
  lcd.print(bootUpMsgV);
  
  delay(2000);


 for (int positionCounter = 0; positionCounter < BootupMSG_T.length()+3; positionCounter++) {
  lcd.scrollDisplayLeft();
  
  delay(200);
 }
 lcd.clear();
}

