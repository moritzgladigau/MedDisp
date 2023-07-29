void SerialMonitor(const String& input) {
  // Überprüfe, ob der übergebene Wert gleich "Aufwiedersehen" ist
  if (input == "Aufwiedersehen") {
    Serial.println("Bis bald!");
  } else {
    Serial.println("Error");
  }
}