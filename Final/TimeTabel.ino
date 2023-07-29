// Datum und Uhrzeit auf dem LCD-Display ausgeben
  void TimeTabelDatum(){
    //lcd.setCursor(0, 0);
    DateTime now = rtc.now();
    lcd.print("Datum: ");
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
  }
  void TimeTabeUhrzeit(){
    DateTime now = rtc.now();
    lcd.setCursor(0, 1);
    lcd.print("Uhrzeit:");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
  }