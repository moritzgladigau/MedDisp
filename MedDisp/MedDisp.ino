//************************************************
//Insert Libary
#include <Keypad.h>                     //Keypad by Mark Stanley, Alexander Brevig
#include <Adafruit_LiquidCrystal.h>     //LCD Display -> LiquidCrystal by Arduino, Adafruit
//************************************************
//LCD_Diplay
Adafruit_LiquidCrystal lcd_1(0);        //Name Dispaly as "lcd_1"
//************************************************

void setup() {
  //LCD_Display
  lcd_1.begin(16, 2);                   //Truns on the Display and defines width & height
  lcd_1.setCursor(0,0);                 //Set the Curser -> top Left corner
  lcd_1.print("hello world");           //Writes "hello world"
  lcd_1.cursor();                       //Turns on the Curser = Curser visible 
  lcd_1.blink();                        //Lets the curser blink
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
