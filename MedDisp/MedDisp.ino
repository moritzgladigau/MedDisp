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

//************************************************
void setup() {
  Serial.begin(9600);                   //communication between Arduino & Pc
  //LCD_Display
  lcd_1.begin(16, 2);                   //Truns on the Display and defines width & height
  lcd_1.setCursor(0,0);                 //Set the Curser -> top Left corner
  lcd_1.print("hello world");           //Writes "hello world"
  lcd_1.cursor();                       //Turns on the Curser = Curser visible 
  lcd_1.blink();                        //Lets the curser blink
}

//************************************************
void loop() {
  customKey = customKeypad.getKey();    //variable "customKey" gets value of the last presed Key 
                                        //if no Key get presed the funktion .getKey() gives the value "NO_KEY"
  if(customKey != NO_KEY){              //Chek if an Key was presed
    Key();                              //calls the funktion Key() from down below
    Serial.print("i=");                 //writes on the Serial monitor...
    Serial.println(i);
    Serial.println(Data);
  }

}
//************************************************
//Key funktion -> 0-9 Keys Write & C Key Clear all & D Key delete last writen
void Key(){
  switch(customKey){
    //Keys 0-9
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
    {                                   //What hapens if one of the Keys above is Presed 
      lcd_1.print(customKey);           //Print last presd key on the LCD Display
      Data[i]=customKey;                //saves to last presd key to Data[0],...,Data[n]
      i++;                              //increase the value i by 1
    }
    break;
    //Key C shoud clear the Display & Data
    case 'C':{
      lcd_1.clear();                    //Clears the Display
      i=0;                              //set i=0 so we can overwrite all the saved values in Data
    }
    break;
    //Key D delete the last writen value in Data
    case 'D':{
      int a=i-1;                        //condition -> We ned all values exept of the last one 
      int x=0;                          //value to write Data in right order
      //Simpel Serial Monitor Control of the first 3 values in Data
      Serial.print("Data.1=");
      Serial.println(Data[0]);
      Serial.print("Data.2=");
      Serial.println(Data[1]);
      Serial.print("Data.3=");
      Serial.println(Data[2]);

      lcd_1.home();                     //set the curser in the top left corner
      //lcd_1.setCurser(0,0);           //set the curser at an position you like 
      if(i>0){                          //controles that the Data save dosent fall under the value 0 (can't delet smth that dosen't exsist)
        while(x<a){                     //repeat until described condition from above is true
          lcd_1.print(Data[x]);         //rewrite all Data 
          x++;
        }
        i--;                            //is used to overwrite the last savet value -> the value we want to delet
      }
    }
    break;
  }
}

