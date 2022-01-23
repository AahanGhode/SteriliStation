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

void HOME(){
  bool button_state = digitalRead(button);
  
  if (button_state == true) {
    button_history = true;
    return;
  }
  
  while(button_history == false){
  bool button_state = digitalRead(button);
  
    if (button_state == true){
      button_history = true;
      return;
    }
    
  String HOME_T = "SteriliStation:";
  String HOME_I = "Press To Start";
  lcd.setCursor(0,0);
  lcd.print(HOME_T);
  
  lcd.setCursor(1,1);
  lcd.print(HOME_T);
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(HOME_I);
  delay(600);
  }
}

void BUTTON_TRUE(){
  lcd.clear();
  String BT_P = "Preparing to";
  String BT_S = "Sterilize"
  lcd.setCursor(2,0);
  lcd.print(BT_T);
  
  lcd.setCursor(4,1);
  lcd.print(BT_S);
  delay(1000)
  
  while (latch == HIGH){
   lcd.clear();
   latch = digitalRead(switchBtn);
   if (latch == LOW){
    break;
  }
  
  Serial.println(latch);
   String LATCH_T = "Please Close";
   String LATCH_B = "Door";
   
   lcd.setCursor(2,0);
   lcd.print(LATCH_T);
  
   lcd.setCursor(6,1);
   lcd.print(LATCH_B);
   delay(500);
   
   latch = digitalRead(switchBtn);
   if (latch == LOW){
    break;
   }
   
   lcd.clear();
   delay(500);
  }
}
