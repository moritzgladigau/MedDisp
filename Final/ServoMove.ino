//Servo Move
  void ServoMove() {
    for (ServoPos = 97; ServoPos >= 34; ServoPos -= 1) {  // goes from 180 degrees to 0 degrees
      myservo.write(ServoPos);                            // tell servo to go to ServoPosition in variable 'ServoPos'
      delay(5);                                           // waits 15ms for the servo to reach the ServoPosition
    }
    //delay(300);
    for (ServoPos = 34; ServoPos <= 97; ServoPos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(ServoPos);  // tell servo to go to ServoPosition in variable 'ServoPos'
      delay(20);                // waits 15ms for the servo to reach the ServoPosition
    }

    return;
  }