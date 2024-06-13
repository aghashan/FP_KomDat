#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

long feed_time1 = 60000;
long feed_time2 = 2 * 60000;
long feed_time3 = 3 * 60000;

long endtime;
long now;
int pos = 0; // tambahkan deklarasi variabel pos

const byte ROWS = 4; // rows
const byte COLS = 4; // columns
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //konek ke row pinouts  keypad
byte colPins[COLS] = {13, 12, 11, 10}; //konek column pinouts  keypad

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Servo servo1; 

int menuOption = 0; 

void setup() {
  servo1.attach(3);  
  servo1.write(0);
  lcd.begin(20, 4);
  displayMenu();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    switch(key) {
      case '1':
        menuOption = 1;
        displayMenu();
        break;
      case '2':
        menuOption = 2;
        displayMenu();
        break;
      case '3':
        menuOption = 3;
        displayMenu();
        break;
      case '9':
        menuOption = 0; // kembali ke main menu
        displayMenu();
        break;
      default:
        break;
    }
  }
  if (menuOption != 0 && millis() >= endtime) {
    displayMenu();
  }
}

void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("menu:");

//servo gerak
  for(pos = 0; pos < 180; pos += 1) {
    servo1.write(pos);
    delay(3);
  } 
  for(pos = 180; pos >= 1; pos -= 1) {
    servo1.write(pos);
    delay(3);
  }
  
  // Reset waktu
  now = millis();
  
  switch(menuOption) {
    case 0:
      lcd.setCursor(0, 1);
      lcd.print("1. 1 menit sekali");
      lcd.setCursor(0, 2);
      lcd.print("2. 2 menit sekal");
      lcd.setCursor(0, 3);
      lcd.print("3. 3 menit sekali");
      break;
    case 1:
      lcd.setCursor(0, 1);
      lcd.print("1 menit sekali");
      endtime = now + feed_time1; 
      break;
    case 2:
      lcd.setCursor(0, 1);
      lcd.print("2 menit sekali");
      endtime = now + feed_time2; 
      break;
    case 3:
      lcd.setCursor(0, 1);
      lcd.print("3 menit sekali");
      endtime = now + feed_time3; 
      break;
    default:
      break;
  }
}
