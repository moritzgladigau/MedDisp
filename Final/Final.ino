// LCD and Servo libraries inclusion
#include <LiquidCrystal.h>
#include <Servo.h>

// Joystick and Button libraries inclusion
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
#define VRX_PIN A0  // Arduino pin connected to VRX pin
#define VRY_PIN A1  // Arduino pin connected to VRY pin
#define SW_PIN 7    // Arduino pin connected to SW  pin
ezButton button(SW_PIN);

// Create RTC object
RTC_DS1307 rtc;

// Global variables
// Store Joystick Values
int xValue = 0;  // To store value of the X axis
int yValue = 0;  // To store value of the Y axis

// Global variables for time settings
int year = 2023;  //2023 - 2099
int month = 1;    // 1 - 12
int day = 1;      // 1 - 31
int hour = 0;     // 0 - 23
int minute = 0;   // 0 - 59
int second = 0;

// Global variables for the menu
int SetNumber = 1;                  // Auxiliary value for representing the numbers 0-9
int WorkOnlyOnce = 0;               // Wait for press button Only Once at the Start
int ButtonIsPressedGoInAndOut = 0;  // Was the Joystick pressed the last time
int ServoPos = 0;                   // variable to store the servo ServoPosition
int Next = 0;                       // Switch "set date /time"
int NextArlarm = 0;
int NextStep = 0;
int Numb = 1;

// Timeslots
// Array to track which timeslots are enabled
int isSet[4] = { 0, 0, 0, 0 };

// Array for timeslots: [Hour, Minute, Second]
int timeslots[4][3] = {
  { 0, 0, 0 },  // Timeslot1
  { 0, 0, 0 },  // Timeslot2
  { 0, 0, 0 },  // Timeslot3
  { 0, 0, 0 }   // Timeslot4
};

// Text Icons
// Heart <3
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
String MenuItems[] = {
  // Your menu items
  "Show Date & Time",
  "Set Date & Time",
  "manual dispense",
  "Clear all",
  "Set Alarm"
  // additional menu items...
};

/***  do not modify  ***********************************************/
template< typename T, size_t NumberOfSize >
size_t MenuItemsSize(T (&)[NumberOfSize]) {
  return NumberOfSize;
}  // allows to get the size of an array, regardless of its type and size.
int numberOfMenuItems = MenuItemsSize(MenuItems) - 1;
int currentMenuItem = 0;
int previousMenuItem = 1;
byte button_flag = 0;  //instance to prevent multiple button inputs in too short a time
unsigned long previousMillis = millis();

//Setup
void setup() {
  Serial.begin(57600);  // communication between PC and Arduino
  lcd.begin(16, 2);
  StartMail();

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  //RTC
  Wire.begin();
  rtc.begin();

  button.setDebounceTime(50);  // Set debounce time to 50ms for button to prevent unintended multiple inputs caused by mechanical contacts
}
//Loop
void loop() {
  DateTime now = rtc.now();

  // Button initialize
  button.loop();  // Update button status

  xValue = analogRead(VRX_PIN);  // read analog X analog values
  yValue = analogRead(VRY_PIN);  // read analog Y analog values

  // StartButton to continue
  if (WorkOnlyOnce == 0) {
    //Control Suport Serial Monitor
    SerialMonitor("WorkOnlyOnceOne");
    while (digitalRead(7) != LOW)
      ;
    {
      StartButton();
      WorkOnlyOnce = 1;
      //Control Suport Serial Monitor
      SerialMonitor("WorkOnlyOnceTwo");
    }
  }
  // Joystick movement
  // Check if the joystick button is pressed to navigate further or not
  if (button.getState() != HIGH && button_flag == 0) {
    button_flag = 1;
    SerialMonitor("GoInMenu");
    if (ButtonIsPressedGoInAndOut == 0) {  // If entering the menu
      ButtonIsPressedGoInAndOut = 1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(MenuItems[currentMenuItem]);      // Display the current menu item
    } else if (ButtonIsPressedGoInAndOut == 1) {  // If exiting the menu
      ButtonIsPressedGoInAndOut = 0;
      CurrentMenueItem();  // Show the main menu again
    }
    SerialMonitor("GoOutMenu");
  }

  if (ButtonIsPressedGoInAndOut == 1) {                // If inside the menu
    if (xValue > 900 && button_flag == 0) {            // Check joystick movement along the x-axis
      menuFunctions(currentMenuItem + 1, 0, 1, 0, 0);  // Move to the next menu item
      button_flag = 1;
      previousMillis = millis();
    } else if (xValue < 50 && button_flag == 0) {  // Move to the previous menu item
      menuFunctions(currentMenuItem + 1, 1, 0, 0, 0);
      button_flag = 1;
      previousMillis = millis();
    } else {
      menuFunctions(currentMenuItem + 1, 0, 0, 0, 0);  // Stay on the current menu item
    }
  }

  // Menu navigation:
  // - If ButtonIsPressedGoInAndOut is 0, joystick Y-axis values determine menu item increments/decrements.
  // - When ButtonIsPressedGoInAndOut is 1, joystick Y-axis value triggers menu function calls for upward movement.
  if (ButtonIsPressedGoInAndOut == 0) {
    if (yValue < 50 && button_flag == 0) {  // Check joystick Y-axis for upward movement
      ++currentMenuItem;
      if (currentMenuItem > numberOfMenuItems) {
        currentMenuItem = numberOfMenuItems;
      }
      button_flag = 1;
      previousMillis = millis();
    } else if (yValue > 900 && button_flag == 0) {  // Check joystick Y-axis for downward movement
      currentMenuItem--;
      if (currentMenuItem < 0) {
        currentMenuItem = 0;
      }
      button_flag = 1;
      previousMillis = millis();
    }
  } else {
    if (yValue < 50 && button_flag == 0) {             // Check joystick Y-axis for upward movement
      menuFunctions(currentMenuItem + 1, 0, 0, 1, 0);  // Move upward
      button_flag = 1;
      previousMillis = millis();
    }
    if (yValue > 900 && button_flag == 0) {            // Check joystick Y-axis for downward movement
      menuFunctions(currentMenuItem + 1, 0, 0, 0, 1);  // Move downward
      button_flag = 1;
      previousMillis = millis();
    }
  }

  // This condition checks whether the selected menu item has changed.
  if (currentMenuItem != previousMenuItem) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menu Item:");
    lcd.setCursor(0, 1);
    lcd.print(MenuItems[currentMenuItem]);
    menuFunctions(currentMenuItem + 1, 0, 0, 0, 0);
    previousMenuItem = currentMenuItem;
  }
  // instance to prevent multiple button inputs in too short a time
  if (millis() - previousMillis >= 700) {
    previousMillis = millis();
    button_flag = 0;
  }
  // Get the current time from the real-time clock (RTC) and store hours, minutes, and seconds in respective variables.
  int RTCHour = now.hour();
  int RTCMin = now.minute();
  int RTCSec = now.second();

  //Servo
  // Check if the current time matches any of the specified timeslots, and if the timeslot is enabled (isSet[x] == 1). If both conditions are met, call the "ServoMove()" function to initiate servo movement.
  for (int i = 0; i < 4; i++) {
    if (RTCHour == timeslots[i][0] && RTCMin == timeslots[i][1] && RTCSec == timeslots[i][2] && isSet[i] == 1) {
      ServoMove();  // Call the function to move the servo.
      break;        // Exit the loop once the condition is met to avoid unnecessary checks.
    }
  }
}
