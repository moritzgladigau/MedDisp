//LCD einfuehrung
 #include <LiquidCrystal.h>

 const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Servo einfuegen
  // #include <Servo.h>
  // Servo myservo;  // create servo object to control a servo
//Joystick einweisung
  #include <ezButton.h>

  #define VRX_PIN  A0 // Arduino pin connected to VRX pin
  #define VRY_PIN  A1 // Arduino pin connected to VRY pin
  #define SW_PIN   7  // Arduino pin connected to SW  pin

  ezButton button(SW_PIN);

  int xValue = 0; // To store value of the X axis
  int yValue = 0; // To store value of the Y axis
  //int bValue = 0; // To store value of the button

//RTC einfuegen 
  #include <Wire.h>
  #include <RTClib.h>

  RTC_DS1307 rtc;
  //DateTime now = rtc.now(); 

int SetNumber=1; // helper value to display numbers 0-9
int WorkOnlyOnce = 0; // Whait for press button OnlyOnce at the Start
int ButtonIsPressedGoInAndOut = 0; // Was the Joystick pressed the lassed time 
int ServoPos = 0;    // variable to store the servo ServoPosition
int Next = 0; // Switch "set date /time"
int SetYear = 0;
int SetMonth = 0;

int year = 2023; ////2023 - 2099
int month = 1; // 1 - 12
int day = 1; // 1 - 31
int hour = 0; // 0 - 23
int minute = 0; // 0 - 59

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
    "meueitem 1",
    "meueitem 2",
    "Data & Time"
    // and so on...
  };
//menu Function
 void menuFunctions(int menu, byte right, byte left, byte Up, byte Down){  // Your menu functions
  if(menu == 1){ // example function for 1. menu item
    if(ButtonIsPressedGoInAndOut == 1){
      lcd.setCursor(0, 0);
      TimeTabelDatum();
      TimeTabeUhrzeit();
      //delay(1000);
    }
  }
  if(menu == 2){ // example function for 2. menu item
    if(ButtonIsPressedGoInAndOut == 1){
      // lcd.setCursor(0, 1);
      // lcd.print("Counter: ");
      // if(Up == 1){NumberCounterNew(0, 1, 8, 1);}
      // if(Down == 1){NumberCounterNew(1, 0, 8, 1);}
      // lcd.print(SetNumber);
    }
  }
  if(menu == 3){
    if(ButtonIsPressedGoInAndOut == 1){
      DateTime now = rtc.now(); 
      // int year = 2023; ////2023 - 2099
      // int month = 1; // 1 - 12
      // int day = 1; // 1 - 31
      // int hour = 0; // 0 - 23
      // int minute = 0; // 0 - 59
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
    //RTC 
      Wire.begin(); 
      rtc.begin();
    button.setDebounceTime(50); // Set debounce time to 50ms for button to prevent unintended multiple inputs caused by mechanical contacts
    //delay(5000);
    //lcd.clear();
    //myservo.attach(19);  // attaches the servo on pin 9 to the servo object
    Serial.print(button.getState());
   }
//Loop
  void loop(){
    button.loop();
    
    DateTime now = rtc.now(); 
    //Docu fehlt int Datum ... in 0-9 couter und dann mit rtc.adjust(DateTime(year, month, day, hour, minute, second)); deff
    // https://chat.openai.com/?model=text-davinci-002-render-sha 
    //ServoLoop();
    //Button
      // buttonStateL = digitalRead(buttonPinL);
      // buttonStateR = digitalRead(buttonPinR);
      // buttonStateU = digitalRead(buttonPinU);
      // buttonStateD = digitalRead(buttonPinD);
      // buttonStateS = digitalRead(buttonPinS);
    // Button initialize
      button.loop(); // // Update button status
      
      xValue = analogRead(VRX_PIN); // read analog X analog values
      yValue = analogRead(VRY_PIN); // read analog Y analog values
      //bValue = button.getState(); // Read the button value
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
        //Serial.println(button_flag_1);
        if(button.getState() != HIGH && button_flag == 0){
          //Serial.println(button.getState());
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
          //delay(700);
        }
        //delay(2000);
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
      // if(millis() - previousMillis >= 800) {
      //   previousMillis = millis();
      //   button_flag_1 = 0;
      // }

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
//Servo Loop
  // void ServoLoop(){
  //   for (ServoPos = 0; ServoPos <= 180; ServoPos += 1) { // goes from 0 degrees to 180 degrees
	//     // in steps of 1 degree
	//     myservo.write(ServoPos);              // tell servo to go to ServoPosition in variable 'ServoPos'
	//     delay(15);                       // waits 15ms for the servo to reach the ServoPosition
	//   }
	//   for (ServoPos = 180; ServoPos >= 0; ServoPos -= 1) { // goes from 180 degrees to 0 degrees
	//     myservo.write(ServoPos);              // tell servo to go to ServoPosition in variable 'ServoPos'
	//     delay(15);                       // waits 15ms for the servo to reach the ServoPosition
	//   }
  // }
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
    lcd.print("Uhrzeit: ");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    // lcd.print(':');
    // lcd.print(now.second(), DEC);
  }