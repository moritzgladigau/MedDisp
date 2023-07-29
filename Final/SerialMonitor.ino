void SerialMonitor(const String& input) {
  if (input == "WorkOnlyOnceOne") {
    Serial.println("If WorkOnlyOnce: 0 -> Wait to press the JoyStick");
    Serial.println("            or: 1 -> The button was pressed code wont work again");
    Serial.print("WorkOnlyOnce:");
    Serial.println(WorkOnlyOnce);
  } else if(input == "WorkOnlyOnceTwo"){
    Serial.print("WorkOnlyOnce:");
    Serial.println(WorkOnlyOnce);
    Serial.println(button.getState());
    //Serial.println("Error");
  }
}