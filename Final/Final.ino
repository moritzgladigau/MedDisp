

//LCD einfuehrung
 #include <LiquidCrystal.h>

 const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Servo einfuegen
  #include <Servo.h>
  Servo myservo;  // create servo object to control a servo
//Joystick einweisung
  #include <ezButton.h>

  #define VRX_PIN  A0 // Arduino pin connected to VRX pin
  #define VRY_PIN  A1 // Arduino pin connected to VRY pin
  #define SW_PIN   7  // Arduino pin connected to SW  pin

  ezButton button(SW_PIN);

  int xValue = 0; // To store value of the X axis
  int yValue = 0; // To store value of the Y axis

//RTC einfuegen 
  #include <SoftWire.h>
  #include <RTClib.h>

  RTC_DS1307 rtc;
  //DateTime now = rtc.now(); 

int SetNumber=1; // helper value to display numbers 0-9
int WorkOnlyOnce = 0; // Whait for press button OnlyOnce at the Start
int ButtonIsPressedGoInAndOut = 0; // Was the Joystick pressed the lassed time 
int ServoPos = 0;    // variable to store the servo ServoPosition
int Next = 0; // Switch "set date /time"
int NextArlarm = 0;
int NextStep = 0;

int year = 2023; ////2023 - 2099
int month = 1; // 1 - 12
int day = 1; // 1 - 31
int hour = 0; // 0 - 23
int minute = 0; // 0 - 59
int second = 0;

int Numb = 1;


  //Wich timeslots are used
int isSet[4] = {0, 0, 0, 0};
// Timeslots: [Stunde, Minute, Sekunde]
int timeslots[4][3] = {
  {5, 27, 0}, // Timeslot1
  {0, 0, 0},   // Timeslot2
  {0, 0, 0},   // Timeslot3
  {0, 0, 0}    // Timeslot4
};

//Text Icons
  // Herz <3
    byte heart[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b10101,
    0b10001,
    0b01010,
    0b00100,
    0b00000
    };
//Menu einweisung
  String MenuItems[] = {  // Your menu items 
    "Show Date & Time",
    "manual dispense",
    "Set Date & Time",
    "Clear all",
    "Set Alarm"
    // and so on...
  };
//menu Function
 void menuFunctions(int menu, byte right, byte left, byte Up, byte Down){  // Your menu functions
  if(menu == 1){ // example function for 1. menu item
    if(ButtonIsPressedGoInAndOut == 1){
      lcd.setCursor(0, 0);
      TimeTabelDatum();
      TimeTabeUhrzeit();
    }
  }
  if(menu == 2){ // example function for 2. menu item
    if(ButtonIsPressedGoInAndOut == 1){
      //RTCWire();
      ServoMove();
    }
  }
  if(menu == 3){
    if(ButtonIsPressedGoInAndOut == 1){
      DateTime now = rtc.now(); 

      int second = now.second(); // Die Sekunde bleibt unverändert
      //lcd.clear();
      if(right == 1){if(Next < 5){Next++;}}
      if(left == 1){if(Next > 0){Next--;}}

      //lcd.setCursor(0, 0);
      //lcd.print("Set Date:");
      lcd.cursor();
      if(Next == 0){
        year = NumberCounterNew(Up, Down, 2099, 2022, year);

        lcd.setCursor(0, 1);
        lcd.print(year);
      }
      else if(Next == 1){
        month = NumberCounterNew(Up, Down, 11, 2, month);

        lcd.setCursor(0, 1);
        lcd.print(year);
        lcd.print("/");
        lcd.print(month);

      }
      else if(Next == 2){
        day = NumberCounterNew(Up, Down, 30, 2, day);

        lcd.setCursor(0, 1);
        lcd.print(year);
        lcd.print("/");
        lcd.print(month);
        lcd.print("/");
        lcd.print(day);
      }
      else if(Next == 3){
        hour = NumberCounterNew(Up, Down, 22, 1, hour);

        lcd.setCursor(11, 1);
        lcd.print(hour);
      }
      else if(Next == 4){
        minute = NumberCounterNew(Up, Down, 58, 1, minute);

        lcd.setCursor(11, 1);
        lcd.print(hour);
        lcd.print(":");
        lcd.print(minute);
      }
      else if(Next == 5){
        lcd.noCursor();
        rtc.adjust(DateTime(year, month, day, hour, minute, second));
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Date & Time");
        lcd.setCursor(0, 1);
        lcd.print("All Set");
      }
    }
    
  }
  if(menu == 4){
    if(ButtonIsPressedGoInAndOut == 1){
      isSet[0] = 0;
      isSet[1] = 0;
      isSet[2] = 0;
      isSet[3] = 0;
    }
  }
  if(menu == 5){
    
    if(ButtonIsPressedGoInAndOut == 1){
      
      if(right == 1){if(NextArlarm < Numb){NextArlarm++;}}
      if(left == 1){if(NextArlarm > 0){NextArlarm--;}}
      
      if(NextArlarm == 0){
        lcd.setCursor(0, 1);
        lcd.print("Timeslots: ");
        Numb = NumberCounterNew(Up, Down, 3, 2, Numb);
        lcd.print(Numb);
        if(Numb >= 1){isSet[0]=1;}else{isSet[0]=0;}
        //Serial.print("isSet 1:"); Serial.println(isSet[0]);
        if(Numb >= 2){isSet[1]=1;}else{isSet[1]=0;}
        //Serial.print("isSet 2:"); Serial.println(isSet[1]);
        if(Numb >= 3){isSet[2]=1;}else{isSet[2]=0;}
        //Serial.print("isSet 3:"); Serial.println(isSet[2]);
        if(Numb >= 4){isSet[3]=1;}else{isSet[3]=0;}
        //Serial.print("isSet 4:"); Serial.println(isSet[3]);
      }
      lcd.setCursor(0, 1);
      if(NextArlarm == 1){
          timeslots[0][0] = NumberCounterNew(Up, Down, 22, 1, timeslots[0][0]);
          timeslots[0][2] = 0;  // Sekunde auf 0 setzen (Start der Servo-Bewegung zu jeder vollen Minute)
          lcd.print("Timeslot 1:");
          lcd.print(timeslots[0][0]);
          lcd.print(":");
          lcd.print(timeslots[0][1]);
      }
      
      if(NextArlarm == 2){
          timeslots[0][1] = NumberCounterNew(Up, Down, 58, 2, timeslots[0][1]);
          timeslots[0][2] = 0;  // Sekunde auf 0 setzen (Start der Servo-Bewegung zu jeder vollen Minute)
          lcd.print("Timeslot 1:");
          lcd.print(timeslots[0][0]);
          lcd.print(":");
          lcd.print(timeslots[0][1]);
      
      }
      if(NextArlarm == 3){
          lcd.print("Timeslot 2:");
      }
    }
  }
   // and so on... 
 }

/***  do not modify  ***********************************************/
 template< typename T, size_t NumberOfSize > 
 size_t MenuItemsSize(T (&) [NumberOfSize]){ return NumberOfSize; } //allows to get the size of any array, regardless of its type and size.
 int numberOfMenuItems = MenuItemsSize(MenuItems) - 1;
 int currentMenuItem = 0;
 int previousMenuItem = 1;
 byte button_flag = 0;   //instance to prevent multiple button inputs in too short a time
 //byte button_flag_1 = 0;
 unsigned long previousMillis = millis();
//Setup
  void setup(){
    Serial.begin(57600); // comunication between PC and Arduino
    lcd.begin(16,2);
    StartMail();
    
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    //RTC 
      Wire.begin();
      rtc.begin();
      //Wire.endTransmission();
    button.setDebounceTime(50); // Set debounce time to 50ms for button to prevent unintended multiple inputs caused by mechanical contacts
    Serial.print(button.getState());
   }
//Loop
  void loop(){
    // button.loop();
    //RTCWire();

    DateTime now = rtc.now(); 

    // Button initialize
      button.loop(); // // Update button status
      
      xValue = analogRead(VRX_PIN); // read analog X analog values
      yValue = analogRead(VRY_PIN); // read analog Y analog values
    // StartButton to continue
      if(WorkOnlyOnce == 0){
        //Control Suport Serial Monitor
          Serial.println("If WorkOnlyOnce: 0 -> Wait to press the JoyStick");
          Serial.println("            or: 1 -> The button was pressed code wont work again");
          Serial.print("WorkOnlyOnce:");
          Serial.println(WorkOnlyOnce);
        while(digitalRead(7) != LOW);{
          StartButton();
          WorkOnlyOnce =1;
          //Control Suport Serial Monitor
            Serial.print("WorkOnlyOnce:");
            Serial.println(WorkOnlyOnce);
            Serial.println(button.getState());
        }
      }
    // Joystick movement 
      // Joystick pressed to go futher yes or no 
        if(button.getState() != HIGH && button_flag == 0){
          button_flag = 1;
          Serial.println("If ButtonIsPressedGoInAndOut New is 0 you can use yValue if 1 xValue:");
          Serial.print("ButtonIsPressedGoInAndOut Old: ");
          Serial.println(ButtonIsPressedGoInAndOut);
          if(ButtonIsPressedGoInAndOut == 0){
            ButtonIsPressedGoInAndOut = 1;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(MenuItems [currentMenuItem]);
          }else if(ButtonIsPressedGoInAndOut == 1){ButtonIsPressedGoInAndOut = 0; CurrentMenueItem();}
          Serial.print("ButtonIsPressedGoInAndOut New: ");
          Serial.println(ButtonIsPressedGoInAndOut);
        }
      if(ButtonIsPressedGoInAndOut == 1){
        if(xValue>900 && button_flag == 0){
          menuFunctions(currentMenuItem + 1, 0, 1, 0, 0); 
          button_flag = 1;
          previousMillis = millis();
        }else if(xValue<50 && button_flag == 0){
          menuFunctions(currentMenuItem + 1, 1, 0, 0, 0); 
          button_flag = 1;
          previousMillis = millis();
        }else{menuFunctions(currentMenuItem + 1, 0, 0, 0, 0);}
      }
      //controle menu wird brauch ich nur im menu wechsel 
      // instansiere kontrollwert=1 wenn joystick gedruekt 
      // und dann wieder auf 0 setzen wenn ein weiteres mal getruken wird  
      if(ButtonIsPressedGoInAndOut == 0){
        if(yValue<50 && button_flag == 0){
          ++currentMenuItem;
          if(currentMenuItem > numberOfMenuItems )
          {
            currentMenuItem = numberOfMenuItems ;
          }
          button_flag = 1;
          previousMillis = millis();
        }else if(yValue>900 && button_flag == 0){
          currentMenuItem--;
          if(currentMenuItem < 0)
          {
            currentMenuItem = 0;
          }
          button_flag = 1;
          previousMillis = millis();
        }
      }else{
        if(yValue<50 && button_flag == 0){
          menuFunctions(currentMenuItem + 1, 0, 0, 1, 0); //up
          button_flag = 1;
          previousMillis = millis();
        }
        if(yValue>900 && button_flag == 0){
          menuFunctions(currentMenuItem + 1, 0, 0, 0, 1); //down
          button_flag = 1;
          previousMillis = millis();
        }
      }
    // This condition checks whether the selected menu item has changed.
      if(currentMenuItem != previousMenuItem){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu Item:");
        lcd.setCursor(0, 1);
        lcd.print(MenuItems [currentMenuItem]);
        menuFunctions(currentMenuItem + 1, 0, 0, 0, 0);
        previousMenuItem = currentMenuItem;
      }
    // instance to prevent multiple button inputs in too short a time
      if(millis() - previousMillis >= 700) {
        previousMillis = millis();
        button_flag = 0;
      }
      int RTCHour = now.hour();
      int RTCMin = now.minute();
      int RTCSec = now.second();
      Serial.println("RTCMin");
      Serial.println(RTCMin);
      Serial.println(timeslots[0][1]);
      Serial.println("RTCSec");
      Serial.println(RTCSec);
      Serial.println(timeslots[0][2]);
    //Servo
      if(RTCHour == timeslots[0][0] && RTCMin == timeslots[0][1] && RTCSec == timeslots[0][2] && isSet[0] == 1){
          ServoMove();
        }
        else if(RTCHour == timeslots[1][0] && RTCMin == timeslots[1][1] && RTCSec == timeslots[1][2] && isSet[1] == 1){
          ServoMove();
        }
        else if(RTCHour == timeslots[2][0] && RTCMin == timeslots[2][1] && RTCSec == timeslots[2][2] && isSet[2] == 1){
          ServoMove();
        }
        else if(RTCHour == timeslots[3][0] && RTCMin == timeslots[3][1] && RTCSec == timeslots[3][2] && isSet[3] == 1){
          ServoMove();
        }
  }

//currentMeueItem
  void CurrentMenueItem(){
    lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu Item:");
        lcd.setCursor(0, 1);
        lcd.print(MenuItems [currentMenuItem]);
  }
  
// Start Mail
  void StartMail(){
    lcd.createChar(0, heart);   // create a new character
    lcd.setCursor(0, 0);
    lcd.setCursor(3,0);
    lcd.write(byte(0)); // when calling lcd.write() '0' must be cast as a byte
    lcd.print("MedDisp");
    lcd.write(byte(0)); // when calling lcd.write() '0' must be cast as a byte
  }
 // Press buton to continue
    void StartButton(){
      lcd.setCursor(6,1);
      lcd.print("Start");
      // fake loading process
        for(int Laden=0;Laden<=100; Laden++){
          lcd.setCursor(15, 1);
          lcd.print("%");
          if(Laden<10){
            lcd.setCursor(14, 1);
          }else if(Laden<100){
            lcd.setCursor(13, 1);
          }
          lcd.print(Laden);
          delay(10); 
        }
    lcd.clear();
    }
//Value on display numbers 0-9 Count
  int NumberCounterNew(byte Up, byte Down, int Max, int Min, int Start){
    if(Up == 1 && Start <= Max){
      return Start+1;
    }
    if(Down == 1 && Start >= Min){
      return Start-1;
    }
    return Start;
  }
//Servo Move
  void ServoMove(){
  for (ServoPos = 97; ServoPos >= 34; ServoPos -= 1) { // goes from 180 degrees to 0 degrees
  myservo.write(ServoPos);              // tell servo to go to ServoPosition in variable 'ServoPos'
  delay(5);                       // waits 15ms for the servo to reach the ServoPosition
  }
  //delay(300);
  for (ServoPos = 34; ServoPos <= 97; ServoPos += 1) { // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
  myservo.write(ServoPos);              // tell servo to go to ServoPosition in variable 'ServoPos'
  delay(20);                       // waits 15ms for the servo to reach the ServoPosition
  }

  return;
  }
// Datum und Uhrzeit auf dem LCD-Display ausgeben
  void TimeTabelDatum(){
    //lcd.setCursor(0, 0);
    DateTime now = rtc.now();
    lcd.print("Datum: ");
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
  }
  void TimeTabeUhrzeit(){
    DateTime now = rtc.now();
    lcd.setCursor(0, 1);
    lcd.print("Uhrzeit:");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
  }
