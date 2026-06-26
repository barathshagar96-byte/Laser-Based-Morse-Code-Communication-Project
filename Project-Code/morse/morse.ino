#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ldrPin = 2;
unsigned long pressStart = 0;
unsigned long lastSignalTime = 0;

String morse = "";

void setup() {
  pinMode(ldrPin, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int state = digitalRead(ldrPin);

  
  if (state == LOW) {
    pressStart = millis();

    while (digitalRead(ldrPin) == LOW); 

    unsigned long duration = millis() - pressStart;
    lastSignalTime = millis();

    
    if (duration < 50) return;

    if (duration < 300) {
      morse += ".";
    } else {
      morse += "-";
    }
  }


  if (morse.length() > 0 && (millis() - lastSignalTime > 700)) {
    char letter = decodeMorse(morse);
    lcd.print(letter);
    morse = "";
  }
}

char decodeMorse(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';

  return '?';
}