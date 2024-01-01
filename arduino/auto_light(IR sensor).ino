//================================
// Successful run on: 19/11/2023
//================================
byte PersonNo;
byte bt = 0;
bool entering, exiting, bet;

void setup() {
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  entering = exiting = bet = false;

  if (digitalRead(3) == HIGH && digitalRead(4) == HIGH) bet = true;   // Check if the person is standing in front of both sensors.

// Check if the person is entering.

  while(digitalRead(3) == HIGH){
    Serial.println("IR sensor 3.");
    if (digitalRead(4) == HIGH && !bet){
      entering = true;
      Serial.println("IR sensor 3 and 4");
    }
  }      

  
  // Check if the person is exiting.

  while(digitalRead(4) == HIGH){
    Serial.println("IR Sensor 4.");
    if (digitalRead(3) == HIGH && !bet){
      Serial.println("IR sensors 4 and 3.");
      exiting = true;
    }
  }
  
  //Check if the person is still exiting.

  if (digitalRead(3) == HIGH && digitalRead(4) == HIGH)  {               // if not, then the person must be standing in front of both sensors.
    exiting = false;
    bet = true;
    Serial.println("Person is in between.");
  }

  while (bet){
    if (!(digitalRead(3) == HIGH && digitalRead(4) == HIGH)) {
      ++bt;
      bet = false;                                                  // halt until the the person has moved.
      Serial.println("Person has moved and is exiting.");
    }
  }

// Increment or decrement person counter accordingly.
  if (entering){
    ++PersonNo;
    entering = false;
    Serial.print("No. of people: ");Serial.println(PersonNo);
  }

  if (exiting){
    --PersonNo;
    exiting = false;
    Serial.println("No. of people: "); Serial.println(PersonNo);
  }

// Turn on light only if someone is in the room.
  if (PersonNo > 0) digitalWrite(2, HIGH);
  else digitalWrite(2, LOW);
}
