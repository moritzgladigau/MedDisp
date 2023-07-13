//LCD einfuehrung
 #include <LiquidCrystal.h>

 const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Joystick einweisung
  #include <ezButton.h>

  #define VRX_PIN  A0 // Arduino pin connected to VRX pin
  #define VRY_PIN  A1 // Arduino pin connected to VRY pin
  #define SW_PIN   7  // Arduino pin connected to SW  pin

  ezButton button(SW_PIN);

  int xValue = 0; // To store value of the X axis
  int yValue = 0; // To store value of the Y axis
  //int bValue = 0; // To store value of the button

  int SetNumber=1; // helper value to display numbers 0-9
  int WorkOnlyOnce = 0; // Whait for press button OnlyOnce at the Start
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
 void menuFunctions(int menu, byte right, byte left){  // Your menu functions
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
    button.setDebounceTime(50); // Set debounce time to 50ms for button to prevent unintended multiple inputs caused by mechanical contacts
    StartMail();
    delay(5000);
    //lcd.clear();
   }
//Loop
  void loop(){
    // Button initialize
      button.loop(); // // Update button status
      
      xValue = analogRead(VRX_PIN); // read analog X analog values
      yValue = analogRead(VRY_PIN); // read analog Y analog values
      //bValue = button.getState(); // Read the button value
    // StartButton to continue
      
      if(WorkOnlyOnce == 0){
        //Control Suport Serial Monitor
          Serial.println("If WorkOnlyOce: 0 -> Whait to press the JoyStick");
          Serial.println("            or: 1 -> The button was pressed code wont work again");
          Serial.print("WorkOnlyOnce:");
          Serial.println(WorkOnlyOnce);
        while(digitalRead(7) != LOW);{
          StartButton();
          WorkOnlyOnce =1;
          //Control Suport Serial Monitor
            Serial.print("WorkOnlyOnce:");
            Serial.print(WorkOnlyOnce);
        }
      }
    // Joystick movement 
      if(xValue>900 && button_flag == 0){
        menuFunctions(currentMenuItem + 1, 1, 0);
        button_flag = 1;
        previousMillis = millis();
      }
      if(xValue<50 && button_flag == 0){
        menuFunctions(currentMenuItem + 1, 0, 1);
        button_flag = 1;
        previousMillis = millis();
      }
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
    // This condition checks whether the selected menu item has changed.
      if(currentMenuItem != previousMenuItem){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Menu Item:");
        lcd.setCursor(0, 1);
        lcd.print(MenuItems [currentMenuItem]);
        menuFunctions(currentMenuItem + 1, 0, 0);
        previousMenuItem = currentMenuItem;
      }
    // instance to prevent multiple button inputs in too short a time
      if(millis() - previousMillis >= 400) {
        previousMillis = millis();
        button_flag = 0;
      }

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
  // is used in the menuFunctions()
  // todo: Not used jet
  void NumberCounter(){
    if(xValue>900 && SetNumber <=9){
      SetNumber=SetNumber+1;
      delay(200);
    }else if(xValue<50 && SetNumber >=0){
      SetNumber=SetNumber-1;
      delay(200);
    }
  } 