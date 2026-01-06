/* 3X3X3 Summative LED Cube Code - Written by Mr. Yousef - 2025.01.15
A 3x3x3 LED cube that lights up a startup sequence and 
multiple different sequences using the 3 pushbuttons
Uses common positive columns and common negative layers to light up
designated LEDs
*/

int commonPositive[] = { 13, 12, 11, 9, 8, 7, 10, 1, 0 };  // Array with all the pins values for common positives

// Initialize button pins and states
int button1Pin = 4;
int button2Pin = 3;
int button3Pin = 2;

int button1State;
int button2State;
int button3State;

// Initialize variables
int currentPattern;

int randomNumber;
int randomLayer;

void setup() {
  randomSeed(analogRead(A3));  // Used to create random sequences
  // Initialize common postives as output
  for (int i = 0; i < 9; i++) {
    pinMode(commonPositive[i], OUTPUT);
  }
  // Initialize common negatives as output
  pinMode(A0, OUTPUT);  // PIN A0 set as output
  pinMode(A1, OUTPUT);  // PIN A1 set as output
  pinMode(A2, OUTPUT);  // PIN A2 set as output

  // Initialize button pins as input
  pinMode(button1Pin, INPUT_PULLUP);  // Button 1 set as input pullup
  pinMode(button2Pin, INPUT_PULLUP);  // Button 2 set as input pullup
  pinMode(button3Pin, INPUT_PULLUP);  // Button 3 set as input pullup

  digitalWrite(A0, LOW);   // Layer 1 of cube is enabled
  digitalWrite(A1, HIGH);  // Layer 2 of cube is disabled
  digitalWrite(A2, HIGH);  // Layer 3 of cube is disabled

  for (int i = 0; i < 9; i++) {  // Turn ON each LED one after another in layer 1
    digitalWrite(commonPositive[i], HIGH);
    delay(50);
  }
  for (int i = 0; i < 9; i++) {  // Turn OFF each LED one after another in layer 1
    digitalWrite(commonPositive[i], LOW);
    delay(50);
  }

  digitalWrite(A0, HIGH);        // Layer 1 of cube is disabled
  digitalWrite(A1, LOW);         // Layer 2 of cube is enabled
  digitalWrite(A2, HIGH);        // Layer 3 of cube is disabled
  for (int i = 0; i < 9; i++) {  // Turn ON each LED one after another in layer 2
    digitalWrite(commonPositive[i], HIGH);
    delay(50);
  }
  for (int i = 0; i < 9; i++) {  // Turn OFF each LED one after another in layer 2
    digitalWrite(commonPositive[i], LOW);
    delay(50);
  }

  digitalWrite(A0, HIGH);        // layer 1 of cube is disabled
  digitalWrite(A1, HIGH);        // layer 2 of cube is disabled
  digitalWrite(A2, LOW);         // layer 3 of cube is enabled
  for (int i = 0; i < 9; i++) {  // Turn ON each LED one after another in layer 3
    digitalWrite(commonPositive[i], HIGH);
    delay(50);
  }
  for (int i = 0; i < 9; i++) {  // Turn OFF each LED one after another in layer 3
    digitalWrite(commonPositive[i], LOW);
    delay(50);
  }
  delay(500);
  digitalWrite(A0, LOW);         // Layer 1 of cube is enabled
  digitalWrite(A1, LOW);         // Layer 2 of cube is enabled
  digitalWrite(A2, LOW);         // Layer 3 of cube is enabled
  for (int i = 0; i < 9; i++) {  // Turn ON all LEDs
    digitalWrite(commonPositive[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 9; i++) {  // Turn OFF all LEDs
    digitalWrite(commonPositive[i], LOW);
  }
  delay(200);
  for (int i = 0; i < 9; i++) {  // Turn ON all LEDs
    digitalWrite(commonPositive[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 9; i++) {  // Turn OFF all LEDs
    digitalWrite(commonPositive[i], LOW);
  }
  delay(200);
  for (int i = 0; i < 9; i++) {  // Turn ON all LEDs
    digitalWrite(commonPositive[i], HIGH);
  }
  delay(100);
  for (int i = 0; i < 9; i++) {  // Turn OFF all LEDs
    digitalWrite(commonPositive[i], LOW);
  }
}

void loop() {
  // Read button states
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);


  // Switch patterns based on button presses
  if (button1State == LOW) {  // Button 1 is pressed, play pattern one
    currentPattern = 1;
    delay(200);
  } else if (button2State == LOW) {  // Button 2 is pressed, play pattern two
    currentPattern = 2;
    delay(200);
  } else if (button3State == LOW) {  // Button 3 is pressed, play pattern three
    currentPattern = 3;
    delay(200);
  }
  // Play the selected pattern
  if (currentPattern == 1) {
    patternOne();
  } else if (currentPattern == 2) {
    patternTwo();
  } else if (currentPattern == 3) {
    patternThree();
  }
}


void patternOne() {
  // Activate all layers
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);

  // Light up the central column (CP5)
  digitalWrite(commonPositive[4], HIGH);

  // Rotating the surrounding columns
  int rotatingOrder[] = { 0, 1, 2, 5, 8, 7, 6, 3 };  // Order of surrounding LEDs
  for (int i = 0; i < 8; i++) {
    digitalWrite(commonPositive[rotatingOrder[i]], HIGH);
    delay(100);
    digitalWrite(commonPositive[rotatingOrder[i]], LOW);
  }
}

void patternTwo() {
  // Deactivate all layers
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  for (int i = 0; i < 9; i++) {
    // Generate random numbers
    randomLayer = random(0, 3);
    randomNumber = random(0, 9);

    // Turn on designated layer based on random number generated
    if (randomLayer == 0) {
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
    } else if (randomLayer == 1) {
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
    } else if (randomLayer == 2) {
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
    }

    // Turn on designated common positive based on random number generated
    digitalWrite(commonPositive[randomNumber], HIGH);
    delay(150);
    digitalWrite(commonPositive[randomNumber], LOW);
    delay(100);
  }
}

void patternThree() {
  // Deactivate all layers
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  // Define LED groupings
  int corners[] = { 0, 2, 6, 8 };  // Corner LEDs
  int edges[] = { 1, 3, 5, 7 };    // Edge LEDs
  int layers[] = { A0, A1, A2 };   // Layer control pins

  // Part 1 of pattern
  for (int layer = 0; layer < 3; layer++) {
    digitalWrite(layers[layer], LOW);  // Activate the current layer

    // Light up the center first
    digitalWrite(commonPositive[4], HIGH);
    delay(200);

    // Light up the edges next
    for (int i = 0; i < 4; i++) {
      digitalWrite(commonPositive[edges[i]], HIGH);
      delay(100);
    }

    // Light up the corners last
    for (int i = 0; i < 4; i++) {
      digitalWrite(commonPositive[corners[i]], HIGH);
      delay(100);
    }

    // Turn off all LEDs in reverse order
    for (int i = 0; i < 4; i++) {
      digitalWrite(commonPositive[corners[i]], LOW);
      delay(100);
    }

    for (int i = 0; i < 4; i++) {
      digitalWrite(commonPositive[edges[i]], LOW);
      delay(100);
    }

    digitalWrite(commonPositive[4], LOW);  // Turn off center LED
    delay(200);

    digitalWrite(layers[layer], HIGH);  // Deactivate the current layer
  }


  // Part two of pattern
  for (int i = 0; i < 3; i++) {
    // Activate all layers
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);

    // Light up LEDs layer-by-layer
    if (i == 0) {
      digitalWrite(commonPositive[4], HIGH);  // Light center
    } else if (i == 1) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(commonPositive[edges[i]], HIGH);  // Light edges, no delay
      }
    } else if (i == 2) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(commonPositive[corners[i]], HIGH);  // Light corners, no delay
      }
    }

    delay(200);

    // Turn off LEDs in the same step order
    if (i == 2) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(commonPositive[corners[i]], LOW);  // Turn off corners
      }
    } else if (i == 1) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(commonPositive[edges[i]], LOW);  // Turn off edges
      }
    } else if (i == 0) {
      digitalWrite(commonPositive[4], LOW);  // Turn off center
    }

    // Deactivate all layers
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);


    delay(200);
  }

  // Part three of pattern
  for (int layer = 0; layer < 3; layer++) {
    digitalWrite(layers[layer], LOW);  // Activate layer
    for (int i = 0; i < 9; i++) {
      digitalWrite(commonPositive[i], HIGH);  // Light up all LEDs in the layer
    }
    delay(200);
    for (int i = 0; i < 9; i++) {
      digitalWrite(commonPositive[i], LOW);  // Turn off all LEDs in the layer
    }
    digitalWrite(layers[layer], HIGH);  // Deactivate layer
  }

  for (int layer = 2; layer >= 0; layer--) {
    digitalWrite(layers[layer], LOW);  // Activate layer
    for (int i = 0; i < 9; i++) {
      digitalWrite(commonPositive[i], HIGH);  // Light up all LEDs in the layer
    }
    delay(200);
    for (int i = 0; i < 9; i++) {
      digitalWrite(commonPositive[i], LOW);  // Turn off all LEDs in the layer
    }
    digitalWrite(layers[layer], HIGH);  // Deactivate layer
  }
}
