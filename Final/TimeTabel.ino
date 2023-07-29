// Datum und Uhrzeit auf dem LCD-Display ausgeben
  void TimeTabelDatum(){
    //lcd.setCursor(0, 0);
    DateTime now = rtc.now();
    lcd.print("Datum:");
    char lcdline[10];
    sprintf(lcdline,"%02d/%02d/%04d",now.day(),now.month(),now.year());
    lcd.print(lcdline);
  }
  void TimeTabeUhrzeit(){
    DateTime now = rtc.now();
    lcd.setCursor(0, 1);
    lcd.print("Uhrzeit:");
    char lcdline[10];
    sprintf(lcdline,"%02d:%02d:%02d",now.hour(),now.minute(),now.second());
    lcd.print(lcdline);
  }