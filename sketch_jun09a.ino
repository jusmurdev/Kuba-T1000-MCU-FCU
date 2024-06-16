
const int button1Pin = 4;     // Trigger
const int button2Pin = 14;     // FullAuto
const int ledPin = 5;        // Theoretical valve pin 2 
bool released = true;         //Is the trigger released?
bool fullAutoEnabled = false; //If full auto enabled?
bool burstFire = true;
const unsigned long interval = 35; // Semi auto delay in ms
const unsigned long flashSpeed = 20; // Full auto delat in ms
int i = 0;


void setup() {
  // Initialize the button pins as inputs
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Initialize the valve pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Boolean Conditioners
  if (digitalRead(button1Pin) == LOW) {
    released = true;
  }
  if (digitalRead(button2Pin) == HIGH) {
    fullAutoEnabled = true;
  }else{
    fullAutoEnabled = false; 
  }

  // Trigger Logic
  if (digitalRead(button1Pin) == HIGH && released == true && fullAutoEnabled == false) {
    if (fullAutoEnabled == false){
      shoot();
      released = false;
    }
  }
  if (digitalRead(button1Pin) == HIGH && released == true && fullAutoEnabled == true && burstFire == false) {
    while (digitalRead(button1Pin) == HIGH){
      shoot();
      delay(flashSpeed); 
    }
  }
  if (digitalRead(button1Pin) == HIGH && released == true && fullAutoEnabled == true && burstFire == true) {
    burst();
    released = false;
  }
}

void shoot() {
  digitalWrite(ledPin, HIGH);
  delay(interval);
  digitalWrite(ledPin, LOW);
}

void burst() {
  i = 0;
  while (i <= 3) {
    shoot();
    i++;
    delay(flashSpeed);
  }
}
