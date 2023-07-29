// Function to execute the corresponding actions for each menu item
void menuFunctions(int menu, byte right, byte left, byte Up, byte Down) {  // Your menu functions
  // The actions for each menu item are implemented here, based on the states of right, left, up, and down
  // which are captured from joystick movements.

  if (menu == 1) {  // Menue.1 shows the date and time on the lcd
    if (ButtonIsPressedGoInAndOut == 1) {
      lcd.setCursor(0, 0);
      TimeTabelDatum();
      TimeTabeUhrzeit();
    }
  }
  if (menu == 2) {  // example function for 2. menu item
    if (ButtonIsPressedGoInAndOut == 1) {
      ServoMove();
    }
  }
  if (menu == 3) {
    if (ButtonIsPressedGoInAndOut == 1) {
      DateTime now = rtc.now();

      int second = now.second();  // Die Sekunde bleibt unverändert
      //lcd.clear();
      if (right == 1) {
        if (Next < 5) { Next++; }
      }
      if (left == 1) {
        if (Next > 0) { Next--; }
      }

      //lcd.setCursor(0, 0);
      //lcd.print("Set Date:");
      lcd.cursor();
      char lcdline[17];  // Array to store the formatted LCD line

      if (Next == 0) {
        year = NumberCounterNew(Up, Down, 2099, 2022, year);
      } else if (Next == 1) {
        month = NumberCounterNew(Up, Down, 11, 2, month);
      } else if (Next == 2) {
        day = NumberCounterNew(Up, Down, 30, 2, day);
      } else if (Next == 3) {
        hour = NumberCounterNew(Up, Down, 22, 1, hour);
      } else if (Next == 4) {
        minute = NumberCounterNew(Up, Down, 58, 1, minute);
      } else if (Next == 5) {
        lcd.noCursor();
        rtc.adjust(DateTime(year, month, day, hour, minute, second));
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Date & Time");
        lcd.setCursor(0, 1);
        lcd.print("All Set");
      }
      sprintf(lcdline, "%04d/%02d/%02d %02d:%02d", year, month, day, hour, minute);
      lcd.setCursor(0, 1);
      lcd.print(lcdline);
    }
  }
  if (menu == 4) {
    if (ButtonIsPressedGoInAndOut == 1) {
      isSet[0] = 0;
      isSet[1] = 0;
      isSet[2] = 0;
      isSet[3] = 0;
    }
  }
  if (menu == 5) {

    if (ButtonIsPressedGoInAndOut == 1) {

      if (right == 1) {
        if (NextArlarm < Numb) { NextArlarm++; }
      }
      if (left == 1) {
        if (NextArlarm > 0) { NextArlarm--; }
      }

      if (NextArlarm == 0) {
        lcd.setCursor(0, 1);
        lcd.print("Timeslots: ");
        Numb = NumberCounterNew(Up, Down, 3, 2, Numb);
        lcd.print(Numb);
        if (Numb >= 1) {
          isSet[0] = 1;
        } else {
          isSet[0] = 0;
        }
        //Serial.print("isSet 1:"); Serial.println(isSet[0]);
        if (Numb >= 2) {
          isSet[1] = 1;
        } else {
          isSet[1] = 0;
        }
        //Serial.print("isSet 2:"); Serial.println(isSet[1]);
        if (Numb >= 3) {
          isSet[2] = 1;
        } else {
          isSet[2] = 0;
        }
        //Serial.print("isSet 3:"); Serial.println(isSet[2]);
        if (Numb >= 4) {
          isSet[3] = 1;
        } else {
          isSet[3] = 0;
        }
        //Serial.print("isSet 4:"); Serial.println(isSet[3]);
      }
      lcd.setCursor(0, 1);
      if (NextArlarm == 1) {
        timeslots[0][0] = NumberCounterNew(Up, Down, 22, 1, timeslots[0][0]);
        timeslots[0][2] = 0;  // Sekunde auf 0 setzen (Start der Servo-Bewegung zu jeder vollen Minute)
        lcd.print("Timeslot 1:");
        lcd.print(timeslots[0][0]);
        lcd.print(":");
        lcd.print(timeslots[0][1]);
      }

      if (NextArlarm == 2) {
        timeslots[0][1] = NumberCounterNew(Up, Down, 58, 2, timeslots[0][1]);
        timeslots[0][2] = 0;  // Sekunde auf 0 setzen (Start der Servo-Bewegung zu jeder vollen Minute)
        lcd.print("Timeslot 1:");
        lcd.print(timeslots[0][0]);
        lcd.print(":");
        lcd.print(timeslots[0][1]);
      }
      if (NextArlarm == 3) {
        lcd.print("Timeslot 2:");
      }
    }
  }
  // and so on...
}
