//LCD einfuehrung
 #include <LiquidCrystal.h>

 const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Servo einfuegen
  #include <Servo.h>

  Servo myservo;  // create servo object to control a servo
const int buttonPinL = 6; 
const int buttonPinR = 7; 
const int buttonPinU = 9; 
const int buttonPinD = 10; 
const int buttonPinS = 8; 

int buttonStateL = 0;  // variable for reading the pushbutton status
int buttonStateR = 0;  // variable for reading the pushbutton status
int buttonStateU = 0;  // variable for reading the pushbutton status
int buttonStateD = 0;  // variable for reading the pushbutton status
int buttonStateS = 0;  // variable for reading the pushbutton status

int SetNumber=1; // helper value to display numbers 0-9
int WorkOnlyOnce = 0; // Whait for press button OnlyOnce at the Start
int ButtonIsPressedGoinAndOut = 0; // Was the Joystick pressed the lassed time 
int ServoPos = 0;    // variable to store the servo ServoPosition

//Text Icons
  // Hertz <3
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
    "meueitem 2"
    // and so on...
  };
//menu Function
 void menuFunctions(int menu, byte right, byte left, byte Up, byte Down){  // Your menu functions
  if(menu == 1){ // example function for 1. menu item
  
    if(right == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Off <<");
      lcd.setCursor(10, 1);
      lcd.print("On    ");
    }
    if(left == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Off   ");
      lcd.setCursor(10, 1);
      lcd.print("On  <<");
    }
  }
  if(menu == 2){ // example function for 2. menu item
    if(ButtonIsPressedGoinAndOut == 1){
      lcd.setCursor(0, 1);
      lcd.print("Counter: ");
      if(Up == 1){NumberCounterNew(1, 0);}
      if(Down == 1){NumberCounterNew(0, 1);}
      lcd.print(SetNumber);
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
 unsigned long previousMillis = millis();
//Setup
  void setup(){
    Serial.begin(57600); // comunication between PC and Arduino
    lcd.begin(16,2);
   // button.setDebounceTime(50); // Set debounce time to 50ms for button to prevent unintended multiple inputs caused by mechanical contacts
    StartMail();
    //delay(5000);
    //lcd.clear();
    myservo.attach(19);  // attaches the servo on pin 9 to the servo object
   }
//Loop
  void loop(){
    ServoLoop();
    buttonStateL = digitalRead(buttonPinL);
    buttonStateR = digitalRead(buttonPinR);
    buttonStateU = digitalRead(buttonPinU);
    buttonStateD = digitalRead(buttonPinD);
    buttonStateS = digitalRead(buttonPinS);
	
      if(WorkOnlyOnce == 0){
        //Control Suport Serial Monitor
          Serial.println("If WorkOnlyOnce: 0 -> Wait to press the JoyStick");
          Serial.println("            or: 1 -> The button was pressed code wont work again");
          Serial.print("WorkOnlyOnce:");
          Serial.println(WorkOnlyOnce);
        while(digitalRead(buttonPinS) == LOW);{
          StartButton();
          WorkOnlyOnce =1;
          //Control Suport Serial Monitor
            Serial.print("WorkOnlyOnce:");
            Serial.println(WorkOnlyOnce);
        }
      }
    // Joystick movement 
      // Joystick pressed to go futher yes or no 
      if(buttonStateS == HIGH && button_flag == 0){
        Serial.println("If ButtonIsPressedGoinAndOut New is 0 you can use yValue if 1 xValue:");
        Serial.print("ButtonIsPressedGoinAndOut Old: ");
        Serial.println(ButtonIsPressedGoinAndOut);
        if(ButtonIsPressedGoinAndOut == 0){
          ButtonIsPressedGoinAndOut = 1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(MenuItems [currentMenuItem]);
        }else{ButtonIsPressedGoinAndOut = 0; CurrentMenueItem();}
        Serial.print("ButtonIsPressedGoinAndOut New: ");
        Serial.println(ButtonIsPressedGoinAndOut);
      }
      
      if(ButtonIsPressedGoinAndOut == 1){
        if(buttonStateL == HIGH && button_flag == 0){
          menuFunctions(currentMenuItem + 1, 1, 0, 0, 0);
          button_flag = 1;
          previousMillis = millis();
        }else if(buttonStateR == HIGH && button_flag == 0){
          menuFunctions(currentMenuItem + 1, 0, 1, 0, 0);
          button_flag = 1;
          previousMillis = millis();
        }else{menuFunctions(currentMenuItem + 1, 0, 0, 0, 0);}
      }
      //controle menu wird brauch ich nur im menu wechsel 
      // instansiere kontrollwert=1 wenn joystick gedruekt 
      // und dann wieder auf 0 setzen wenn ein weiteres mal getruken wird  
      if(ButtonIsPressedGoinAndOut == 0){
        if(buttonStateU == HIGH && button_flag == 0){
          ++currentMenuItem;
          if(currentMenuItem > numberOfMenuItems )
          {
            currentMenuItem = numberOfMenuItems ;
          }
          button_flag = 1;
          previousMillis = millis();
        }else if(buttonStateD == HIGH && button_flag == 0){
          currentMenuItem--;
          if(currentMenuItem < 0)
          {
            currentMenuItem = 0;
          }
          button_flag = 1;
          previousMillis = millis();
        }
      }else{
        if(buttonStateU == HIGH && button_flag == 0){
          menuFunctions(currentMenuItem + 1, 0, 0, 1, 0);
          button_flag = 1;
          previousMillis = millis();
        }
        if(buttonStateD == HIGH && button_flag == 0){
          menuFunctions(currentMenuItem + 1, 0, 0, 0, 1);
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
      if(millis() - previousMillis >= 400) {
        previousMillis = millis();
        button_flag = 0;
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
          delay(80); 
        }
    lcd.clear();
    }
//Value on display numbers 0-9 Count
  void NumberCounterNew(byte Up, byte Down){
    if(Up == 1 && SetNumber <=8){
      SetNumber=SetNumber+1;
    }
    if(Down == 1 && SetNumber >=1){
      SetNumber=SetNumber-1;
    }
  }
//Servo Loop
  void ServoLoop(){
    for (ServoPos = 0; ServoPos <= 180; ServoPos += 1) { // goes from 0 degrees to 180 degrees
	    // in steps of 1 degree
	    myservo.write(ServoPos);              // tell servo to go to ServoPosition in variable 'ServoPos'
	    delay(15);                       // waits 15ms for the servo to reach the ServoPosition
	  }
	  for (ServoPos = 180; ServoPos >= 0; ServoPos -= 1) { // goes from 180 degrees to 0 degrees
	    myservo.write(ServoPos);              // tell servo to go to ServoPosition in variable 'ServoPos'
	    delay(15);                       // waits 15ms for the servo to reach the ServoPosition
	  }
  }