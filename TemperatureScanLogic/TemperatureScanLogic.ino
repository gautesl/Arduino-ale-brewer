#define SKRUE A2
#define KNAPPEN A3
#define LYS_GRONN A1
#define LYS_ROD A0
#define KOKEPLATE A5

int segA = 11;
int segB = 7;
int segC = 4;
int segD = 2;
int segE = 13;
int segF = 10;
int segG = 5;
int segPt = 3;

int dgt1 = 12;
int dgt2 = 9;
int dgt3 = 8;
int dgt4 = 6;
int dgts[4] = {dgt1, dgt2, dgt3, dgt4};

double curr_temp = 0;
int delayTime = 2;

double target_temp = 30;
boolean buttonPressed = false;
boolean buttonState = false;
boolean lastButtonState = false;
boolean setTempMode = false;
unsigned long lastDebounceTime = 0;
short debounceDelay = 50; 

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(KOKEPLATE, OUTPUT);
  pinMode(LYS_GRONN, OUTPUT);
  pinMode(LYS_ROD, OUTPUT);
  pinMode(SKRUE, INPUT);
  pinMode(KNAPPEN, INPUT);
  digitalWrite(dgt1, HIGH);
  digitalWrite(dgt2, HIGH); 
  digitalWrite(dgt3, HIGH); 
  digitalWrite(dgt4, HIGH);
  Serial.begin(9600);
}

void loop() {
  readTemperatures();
  registerButtonClick();

  if (curr_temp < target_temp) {
    digitalWrite(LYS_ROD, HIGH);
    digitalWrite(KOKEPLATE, LOW);
  } else {
    digitalWrite(LYS_ROD, LOW);
    digitalWrite(KOKEPLATE, HIGH);
  }
  

  if (setTempMode) {
    target_temp = (double) map(analogRead(SKRUE), 0, 1023, 60, 210) / 2; // 0 nr 2 var 60
    writeNumber(target_temp);
  }
  else {
    writeNumber(curr_temp);
  }
}

void readTemperatures() {
  if (Serial.available() > 0) {
    uint8_t firstHalf = Serial.read();
    delay(2);
    uint8_t secondHalf = Serial.read();
    uint16_t result = (firstHalf << 8) + secondHalf;
    curr_temp = (double) result / 10;
  }
}

void registerButtonClick() {
  buttonPressed = digitalRead(KNAPPEN);

  if (buttonPressed != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {

    if (buttonPressed != buttonState) {
      buttonState = buttonPressed;

      if (buttonPressed) {
        setTempMode = !setTempMode;
        digitalWrite(LYS_GRONN, setTempMode);
        
      }
    }
  }
  lastButtonState = buttonPressed;
}

void writeNumber(double number) {
  number *= 10;
  int pos = 0;
  int digit;

  for (int i = 1000; i > 0; i /= 10) {
    digit = number / i;
    digitalWrite(dgts[pos], LOW);
  
   switch (digit) {
      case 1: one(); break;
      case 2: two(); break;
      case 3: three(); break;
      case 4: four(); break;
      case 5: five(); break;
      case 6: six(); break;
      case 7: seven(); break;
      case 8: eight(); break;
      case 9: nine(); break;
      default: zero(); break;
   }

   if (pos == 2) point();

   delay(delayTime);
   digitalWrite(dgts[pos++], HIGH);
   number -= digit * i;
  }
   
}

void one() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}

void two() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void three() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void four() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void five() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void six() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void seven() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}

void eight() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void nine() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void zero() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}

void point() {
  digitalWrite(segPt, HIGH);
}

