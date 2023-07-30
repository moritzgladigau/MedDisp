void SerialMonitor(const String& input) {
  if (input == "WorkOnlyOnceOne") {
    Serial.println("If WorkOnlyOnce: 0 -> Wait to press the JoyStick");
    Serial.println("             or: 1 -> The button was pressed code wont work again");
    Serial.print("WorkOnlyOnce:");
    Serial.println(WorkOnlyOnce);
  } else if (input == "WorkOnlyOnceTwo") {
    Serial.print("WorkOnlyOnce:");
    Serial.println(WorkOnlyOnce);
    Serial.println("-------------------------------------------------------------------");
    //Serial.println("Error");
  } else if (input == "GoInMenu") {
    Serial.println("If ButtonIsPressedGoInAndOut New == 1 you are in the selectet Menu and use the new definitions of x & yValue.");
    Serial.println("If ButtonIsPressedGoInAndOut New == 0 you can switch the difrent Menu Items.");
    Serial.print("      ButtonIsPressedGoInAndOut Old: ");
    Serial.println(ButtonIsPressedGoInAndOut);
  } else if (input == "GoOutMenu") {
    Serial.print("      ButtonIsPressedGoInAndOut New: ");
    Serial.println(ButtonIsPressedGoInAndOut);
    Serial.println("-------------------------------------------------------------------");
  }
}