//************************************************
//Insert Libary
#include <Keypad.h>                     //Keypad by Mark Stanley, Alexander Brevig. https://github.com/Chris--A/Keypad
#include <Adafruit_LiquidCrystal.h>     //LCD Display -> LiquidCrystal by Arduino, Adafruit. https://github.com/adafruit/Adafruit_LiquidCrystal
//************************************************
//LCD_Diplay
Adafruit_LiquidCrystal lcd_1(0);        //Name Dispaly as "lcd_1"
//************************************************
//Keypad
const byte ROWS = 4;                    //Introduce Rows of the Keypad
const byte COLS = 4;                    //Introduce colums of the Keypad

char hexaKeys[ROWS][COLS] = {           //define the cymbols on the buttons of the keypads
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};      //row pins define
byte colPins[COLS] = {5, 4, 3, 2};      //colum pins define

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);    //Difine the Keypad to the Arduino Bord
//************************************************
//Global variables 
char Data[10];                          //n first undefine values named "Data(0),Data(1),...,Data(n)"
int i;                                  //integer to count Data(n) n=i
char customKey;                         //value that holds the last presed Key ->Defind later 

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
