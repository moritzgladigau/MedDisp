

// LCD and Servo libraries inclusion
  #include <LiquidCrystal.h>
  #include <Servo.h>

//Joystick and Button libraries inclusion
  #include <ezButton.h>

// I2C library for RTC and RTC library inclusion
  #include <SoftWire.h>
  #include <RTClib.h>

// Create LCD object
  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// Create Servo object
  Servo myservo;
// Define Joystick pins
  #define VRX_PIN  A0 // Arduino pin connected to VRX pin
  #define VRY_PIN  A1 // Arduino pin connected to VRY pin
  #define SW_PIN   7  // Arduino pin connected to SW  pin
  ezButton button(SW_PIN);
// Create RTC object
  RTC_DS1307 rtc;

//Global variables
  // Store Joystick Values
    int xValue = 0; // To store value of the X axis
    int yValue = 0; // To store value of the Y axis

  // Global variables for time settings
    int year = 2023;  //2023 - 2099
    int month = 1;    // 1 - 12
    int day = 1;      // 1 - 31
    int hour = 0;     // 0 - 23
    int minute = 0;   // 0 - 59
    int second = 0;

  // Global variables for the menu
    int SetNumber=1;                    // helper value to display numbers 0-9
    int WorkOnlyOnce = 0;               // Whait for press button OnlyOnce at the Start
    int ButtonIsPressedGoInAndOut = 0;  // Was the Joystick pressed the lassed time 
    int ServoPos = 0;                   // variable to store the servo ServoPosition
    int Next = 0;                       // Switch "set date /time"
    int NextArlarm = 0;
    int NextStep = 0;

  int Numb = 1;

// Array to track which timeslots are enabled
  int isSet[4] = {0, 0, 0, 0};
// Array for timeslots: [Hour, Minute, Second]
  int timeslots[4][3] = {
    {5, 27, 0},  // Timeslot1
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
// Menu texts
  String MenuItems[] = {  // Your menu items 
    "Show Date & Time",
    "manual dispense",
    "Set Date & Time",
    "Clear all",
    "Set Alarm"
    // additional menu items...
  };

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






