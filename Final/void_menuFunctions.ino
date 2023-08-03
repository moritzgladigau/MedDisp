// Function to execute the corresponding actions for each menu item
void menuFunctions(int menu, byte right, byte left, byte Up, byte Down) {  // Your menu functions
  // The actions for each menu item are implemented here, based on the states of right, left, up, and down
  // which are captured from joystick movements.

  if (menu == 1) {  // "Show Date & Time"
    if (ButtonIsPressedGoInAndOut == 1) {
      lcd.setCursor(0, 0);
      TimeTabelDatum();
      TimeTabeUhrzeit();
    }
  }
  if (menu == 3) {  // "manual dispense"
    if (ButtonIsPressedGoInAndOut == 1) {
      ServoMove();
    }
  }
  if (menu == 2) {  // "Set Date & Time"
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
        rtc.adjust(DateTime(year, month, day, hour, minute, second));
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Date & Time");
        lcd.setCursor(0, 1);
        lcd.print("All Set");
        delay(700);
        ButtonIsPressedGoInAndOut = 0;
        CurrentMenueItem();
        Next = 0;
      }
      if (Next != 5 && ButtonIsPressedGoInAndOut == 1) {
        sprintf(lcdline, "%04d/%02d/%02d %02d:%02d", year, month, day, hour, minute);
        lcd.setCursor(0, 1);
        lcd.print(lcdline);
      }
    }
  }
  if (menu == 4) {  // "Clear all"
    if (ButtonIsPressedGoInAndOut == 1) {
      for (int i = 0; i < 4; i++) {
        timeslots[i][0] = 0;
        timeslots[i][1] = 0;
        isSet[i] = 0;
      }
      lcd.setCursor(0, 1);
      lcd.print("All Timeslots cleared");
      delay(800);
      for (int i = 0; i < 8; i++) {
        lcd.scrollDisplayLeft();
        delay(500);
      }
    }
  }
  if (menu == 5) {  // "Set Alarm"

    if (ButtonIsPressedGoInAndOut == 1) {

      if (right == 1) {
        if (NextArlarm < Numb * 2) { NextArlarm++; }
      }
      if (left == 1) {
        if (NextArlarm > 0) { NextArlarm--; }
      }

      lcd.setCursor(0, 1);
      // Common functionality for all cases
      char lcdline[17];  // Array to store the formatted LCD line

      switch (NextArlarm) {
        case 1:  // Timeslot-1 hour
          timeslots[0][0] = NumberCounterNew(Up, Down, 22, 1, timeslots[0][0]);
          sprintf(lcdline, "Timeslot-1 %02d:%02d", timeslots[0][0], timeslots[0][1]);
          lcd.print(lcdline);
          break;

        case 2:  // Timeslot-1 minute
          timeslots[0][1] = NumberCounterNew(Up, Down, 58, 1, timeslots[0][1]);
          sprintf(lcdline, "Timeslot-1 %02d:%02d", timeslots[0][0], timeslots[0][1]);
          lcd.print(lcdline);
          break;

        case 3:  // Timeslot-2 hour
          timeslots[1][0] = NumberCounterNew(Up, Down, 22, 1, timeslots[1][0]);
          sprintf(lcdline, "Timeslot-2 %02d:%02d", timeslots[1][0], timeslots[1][1]);
          lcd.print(lcdline);
          break;

        case 4:  // Timeslot-2 minute
          timeslots[1][1] = NumberCounterNew(Up, Down, 58, 1, timeslots[1][1]);
          sprintf(lcdline, "Timeslot-2 %02d:%02d", timeslots[1][0], timeslots[1][1]);
          lcd.print(lcdline);
          break;

        case 5:  // Timeslot-3 hour
          timeslots[2][0] = NumberCounterNew(Up, Down, 22, 1, timeslots[2][0]);
          sprintf(lcdline, "Timeslot-3 %02d:%02d", timeslots[2][0], timeslots[2][1]);
          lcd.print(lcdline);
          break;

        case 6:  // Timeslot-3 minute
          timeslots[2][1] = NumberCounterNew(Up, Down, 58, 1, timeslots[2][1]);
          sprintf(lcdline, "Timeslot-3 %02d:%02d", timeslots[2][0], timeslots[2][1]);
          lcd.print(lcdline);
          break;

        case 7:  // Timeslot-4 hour
          timeslots[3][0] = NumberCounterNew(Up, Down, 22, 1, timeslots[3][0]);
          sprintf(lcdline, "Timeslot-4 %02d:%02d", timeslots[3][0], timeslots[3][1]);
          lcd.print(lcdline);
          break;

        case 8:  // Timeslot-4 minute
          timeslots[3][1] = NumberCounterNew(Up, Down, 58, 1, timeslots[3][1]);
          sprintf(lcdline, "Timeslot-4 %02d:%02d", timeslots[3][0], timeslots[3][1]);
          lcd.print(lcdline);
          break;

          // Add more cases as needed

        default:
          // Handle the default case, if required
          lcd.setCursor(0, 1);
          lcd.print("Timeslots: ");
          Numb = NumberCounterNew(Up, Down, 3, 2, Numb);
          lcd.print(Numb);
          lcd.print("       ");
          for (int i = 0; i < 4; i++) {
            isSet[i] = (Numb >= i + 1) ? 1 : 0;
            // Serial.print("isSet "); Serial.print(i); Serial.print(":"); Serial.println(isSet[i]);
            // Serial.println("-------------------------------------------------------------------");
          }

          break;
      }
    }
  }
  // and so on...
}
