//LCD einfuehrung
 #include <LiquidCrystal.h>

 const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Joystick einweisung
 #define VRX_PIN  A0 // Arduino pin connected to VRX pin
 #define VRY_PIN  A1 // Arduino pin connected to VRY pin

 int xValue = 0; // To store value of the X axis
 int yValue = 0; // To store value of the Y axis

//Menu einweisung
 String MenuItems[] = {  // Your menu items
  "LED Switch",
  "LED Brightness",
  "menuitem 3",
  "menuitem 4",
  "menuitem 5",
  "menuitem 6" 
  // and so on... 
 };

 void menuFunctions(int menu, byte right, byte left){  // Your menu functions
  if(menu == 1){ // example function for 1. menu item
  
    if(right == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 3);
      lcd.print("Off   ");
      lcd.setCursor(10, 3);
      lcd.print("On  <<");
    }
    if(left == 1)
    {
      lcd.setCursor(0, 3);
      lcd.print("Off <<");
      lcd.setCursor(10, 3);
      lcd.print("On    ");
    }
  }
  if(menu == 2){ // example function for 2. menu item
    if(right == 1)
    {
      lcd.print("right");
    }
    if(left == 1)
    {
      lcd.print("left");
    }
    lcd.print("Uff");
  }
  if(menu == 3){
    lcd.setCursor(0,2);
    lcd.print("Hello Menu Item 3");
  }
   // and so on... 
 }

/***  do not modify  ***********************************************/
 template< typename T, size_t NumberOfSize > 
 size_t MenuItemsSize(T (&) [NumberOfSize]){ return NumberOfSize; }
 int numberOfMenuItems = MenuItemsSize(MenuItems) - 1;
 int currentMenuItem = 0;
 int previousMenuItem = 1;
 byte button_flag = 0;
 unsigned long previousMillis = millis();
 const int note = 4699;
//********

void setup(){
  Serial.begin(57600);
  lcd.begin(16,2);
  //button.setDebounceTime(50);
  lcd.setCursor(2, 0);
  lcd.print("Hi");
  delay(500);
  lcd.clear();
}

void loop(){
  //button.loop();
  // read analog X and Y analog values
   xValue = analogRead(VRX_PIN);
   yValue = analogRead(VRY_PIN);
  //***
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
  if(currentMenuItem != previousMenuItem){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menu Item:");
    lcd.setCursor(0, 1);
    lcd.print(MenuItems [currentMenuItem]);
    menuFunctions(currentMenuItem + 1, 0, 0);
    previousMenuItem = currentMenuItem;
  }
  if(millis() - previousMillis >= 400) {
    previousMillis = millis();
    button_flag = 0;
  }
}
