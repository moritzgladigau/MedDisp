/*
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick
 * https://docs.arduino.cc/learn/electronics/lcd-displays
 */
#include <ezButton.h>
#include <LiquidCrystal.h>


#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define SW_PIN   7  // Arduino pin connected to SW  pin

ezButton button(SW_PIN);

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int bValue = 0; // To store value of the button

int StartButtonAbfrage=0;
int Up=0;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

String MenuItems[] = {  // Your menü items
  "LED Switch",
  "LED Brightness",
  "menuitem 3",
  "menuitem 4",
  "menuitem 5",
  "menuitem 6" 
  // and so on... 
};

void menuFunctions(int menu, byte right, byte left)  // Your menü functions
{
  if(menu == 1) // example function for 1. menü item
  {
    if(right == 1)
    {
      lcd.setCursor(0, 1);
      lcd.print("Off   ");
      lcd.setCursor(10, 1);
      lcd.print("On  <<");
      //digitalWrite(ledPin, HIGH);
    }
    if(left == 1)
    {
      lcd.setCursor(0, 1);
      lcd.print("Off <<");
      lcd.setCursor(10, 1);
      lcd.print("On    ");
      //digitalWrite(ledPin, LOW);
    }
  }
  if(menu == 2) // example function for 2. menü item
  {
    lcd.setCursor(0, 1);
    lcd.print("Brightness:     ");
    lcd.setCursor(12, 1);
    //lcd.print(fade);
    //analogWrite(ledPin_fade, fade);
  }
  if(menu == 3)
  {
    lcd.setCursor(0, 1);
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
  
/*******************************************************************/

void setup() {
  Serial.begin(57600); // Start the serial interface

  lcd.begin(16, 2);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  lcd.createChar(0, heart);   // create a new character

  lcd.setCursor(0, 0);
  
  //BegrüsungsText
  lcd.print("Hallo und ");
  lcd.write(byte(0)); // when calling lcd.write() '0' must be cast as a byte
  lcd.print(" Wilkommen im Menu ihres ");

  //goto jump;
  
  delay(500);
  for(int i=0;i<2;i++){
  for(int PositionCount=0;PositionCount<20; PositionCount++)//loop for scrolling the LCD text
  {
    lcd.scrollDisplayLeft();//builtin command to scroll left the text
    delay(500);// delay of 150 msec
    }
    
    lcd.clear();
    lcd.print("im Menue ihres eigenen MedDisp.");
  }
  
  //jump:
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("MedDisp");
}

void loop() {
  button.loop(); // MUST call the loop() function first

  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
   // Read the button value
  bValue = button.getState();
  
  //Starte Den MedDisp nach der Begrüsung 
  if(StartButtonAbfrage==0){
    while(digitalRead(7) != LOW);{
      Serial.println(bValue);
      Serial.print("StartButtonAbfrage=");
      Serial.println(StartButtonAbfrage);
      StartButton();
      //if(button.isPressed()){
    }
  }
  // Serial.print("Befor:");
  // Serial.println(Up);
  UpDownControle();
  // Serial.print("After:");
  // Serial.println(Up);

  lcd.setCursor(0,0);
  lcd.print("X Value : ");
  lcd.print(Up);//Displaying xValue on top
  
  lcd.setCursor(0,1);
  lcd.print("Y Value : ");
  lcd.print(yValue);//Displaying yValue on bottom
}

void StartButton(){
  lcd.setCursor(6,1);
  lcd.print("Start");
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
  StartButtonAbfrage=1;
  Serial.print("StartButtonAbfrage=");
  Serial.println(StartButtonAbfrage);
}

void UpDownControle(){
  if(xValue>900 && Up <=8){
    Up=Up+1;
    delay(200);
  }else if(xValue<50 && Up >=1){
    Up=Up-1;
    delay(200);
  }
}


