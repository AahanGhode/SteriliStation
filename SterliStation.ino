int switchBtn = 2;
int buzzer = 3;
int strtUpBtn = 4;
int UVBulbs = 5;
int statusLED = 6;
bool button_history = false;
bool latch = false;
bool doorState = false;
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
  pinMode(UVBulbs, OUTPUT);
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


 for (int positionCounter = 0; positionCounter < bootUpMsgT.length()+3; positionCounter++) {
  lcd.scrollDisplayLeft();
  
  delay(200);
 }
 lcd.clear();
}

void HOME(){
  bool button_state = digitalRead(strtUpBtn);
  
  if (button_state == true) {
    button_history = true;
    return;
  }
  
  while(button_history == false){
    bool button_state = digitalRead(strtUpBtn);
  
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
  String BT_S = "Sterilize";
  lcd.setCursor(2,0);
  lcd.print(BT_P);
  
  lcd.setCursor(4,1);
  lcd.print(BT_S);
  delay(1000);
  
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

void SANITIZE(){
  digitalWrite(buzzer, LOW);
  
  doorState=digitalRead(switchBtn);
  
  if(doorState == HIGH){
    digitalWrite(UVBulbs, LOW);
    LID_OPEN();
  }
  
  String SANITIZE_T = "Sterilizing: ";
  lcd.setCursor(2,0);
  lcd.print(SANITIZE_T);
  
  lcd.setCursor(5,1);
  lcd.print(4-minutes);
  lcd.print(":");
  
  if(seconds > 49){
    lcd.print("0");
    lcd.print(59-seconds);
  }
  if(seconds <50){
    lcd.print(59-seconds);
  }
  
  digitalWrite(UVBulbs, HIGH);
  milli++;
  
  if(milli >= 10){
    seconds++;
  
    if(LED_state == false){
      digitalWrite(statusLED, HIGH);
      LED_state = true;
    }
    else{
      digitalWrite(statusLED, LOW);
      LED_state == false;
    }
    milli=0;
  }
  
  if(seconds >= 60){
    lcd.clear();
    minutes ++;
    seconds = 0;
  }
  if(minutes >= 5){
    minutes = 0;
     DONE();
  }
  Serial.println(milli);
  Serial.println(seconds);
  Serial.println(minutes);
  delay(100);
}

void DONE(){
  lcd.clear();

  String DONE_T = "Sterilization";
  String DONE_B = "Complete";
  int counter = 0;
  
  while (latch == LOW){
    latch = digitalRead(switchBtn);
    
    lcd.setCursor(1,0);
    lcd.print(DONE_T);
    lcd.setCursor(3,1);
    lcd.print(DONE_B);
    
    if(counter < 3){
      digitalWrite(buzzer, HIGH);
      digitalWrite(statusLED, HIGH);
      counter++;
    }
    
    delay(500);
    
    lcd.clear();
    digitalWrite(buzzer, LOW);
    digitalWrite(statusLED, LOW);
    delay(500);
  }
  
  button_history = false; 
  HOME();
  BUTTON_TRUE();
}

void LID_OPEN(){
  Serial.println("IN LID_OPEN");
  
  latch = digitalRead(switchBtn);
  
  if(latch == LOW){
    return;
  }
  
  String LCD_OPEN_T1 = "-Warning";
  String LCD_OPEN_T2 = "Sterilizing";
  String LCD_OPEN_T3 = "Stopped";
  String LCD_OPEN_T4 = "Please Close";
  String LCD_OPEN_T5 = "Door";
  
  while(latch == HIGH){
   delay(1000);
   lcd.clear();
   Serial.println("In LID_OPEN While LOOP");
   latch = digitalRead(switchBtn);
   
   lcd.setCursor(3,0);
   lcd.print(LCD_OPEN_T1);
   digitalWrite(buzzer, HIGH);
   digitalWrite(statusLED, HIGH);
   
  
    if (latch == LOW){
     break;
   }
   latch = digitalRead(switchBtn);
   delay(500);
   digitalWrite(buzzer, LOW);
   digitalWrite(statusLED, LOW);
   lcd.clear();
   delay(500);
   lcd.setCursor(3,0);
   lcd.print(LCD_OPEN_T1);
   latch = digitalRead(switchBtn);
  
  if (latch == LOW){
    break;
   }
   digitalWrite(buzzer, HIGH);
   digitalWrite(statusLED, HIGH);
   delay(500);
   digitalWrite(buzzer, LOW);
   digitalWrite(statusLED, LOW);
   lcd.clear();
   delay(500);
   
   lcd.setCursor(3,0);
   lcd.print(LCD_OPEN_T1);
   latch = digitalRead(switchBtn);
   
  if (latch == LOW){
    break;
   }
   digitalWrite(buzzer, HIGH);
   digitalWrite(statusLED, HIGH);
   delay(500);
   
   digitalWrite(buzzer, LOW);
   digitalWrite(statusLED, LOW);
   lcd.clear();
   if (latch == LOW){
    break;
   }
   delay(500);
   
   lcd.setCursor(2,0);
   lcd.print(LCD_OPEN_T2);
   lcd.setCursor(4,1);
   lcd.print(LCD_OPEN_T3);
   latch = digitalRead(switchBtn);
  
    if (latch == LOW){
      break;
    }
   digitalWrite(buzzer, HIGH);
   digitalWrite(statusLED, HIGH);
   delay(1000);
    if (latch == LOW){
    break;
   }
  
   lcd.clear();
   
   lcd.setCursor(2,0);
   lcd.print(LCD_OPEN_T4);
   
   lcd.setCursor(6,1);
   lcd.print(LCD_OPEN_T5);
   
   latch = digitalRead(switchBtn);
  
  if (latch == LOW){
    break;
   }
   digitalWrite(buzzer, LOW);
   digitalWrite(statusLED, LOW);
   delay(750);
  }
  return;
}
