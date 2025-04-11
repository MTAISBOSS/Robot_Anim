#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_SH110X.h>
#define i2c_Address 0x3c

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String emotion = "neutral";
int face_x = 0, face_y = 0;
int delay_amount = 25;

int xDiff = 0, yDiff = 0;
float ratio = 0.5;
void setup() {

  Serial.begin(115200);
  display.begin(i2c_Address, true);  // Address 0x3C default
  display.clearDisplay();
  display.display();
}
void loop() {
  while (true) {
    for (int i = 0; i < 7; i++) {
      Screen_HeartEyes_Middle();
      delay(delay_amount);
      Screen_HeartEyes_LeftUp();
      delay(delay_amount);
      Screen_HeartEyes_Middle();
      delay(delay_amount);
      Screen_HeartEyes_RightUp();
      delay(delay_amount);
      Screen_HeartEyes_Middle();
      delay(delay_amount);
    }
    for (int i = 0; i < 7; i++) {
      Screen_Happy_ClosedEyes_Middle();
      delay(2*delay_amount);
      Screen_Happy_ClosedEyes_Bottom();
      delay(2*delay_amount);
      Screen_Happy_ClosedEyes_Middle();
      delay(2*delay_amount);
      Screen_Happy_ClosedEyes_Top();
      delay(2*delay_amount);
      Screen_Happy_ClosedEyes_Middle();
      delay(2*delay_amount);
    }
    for (int i = 0; i < 7; i++) {

      Screen_Idle_FullEyesOpen();
      delay(delay_amount);
      Screen_Idle_HalfEyesOpen();
      delay(delay_amount);
      Screen_Idle_ClosedEyes();
      delay(delay_amount);
      Screen_Idle_HalfEyesOpen();
      delay(delay_amount);
      Screen_Idle_FullEyesOpen();
      delay(delay_amount);
    }
  }
  if (Serial.available()) {
    String jsonData = Serial.readStringUntil('\n');
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, jsonData);

    if (!error) {
      // Parse data
      emotion = doc["emotion"].as<String>();
      face_x = doc["position"]["x"];
      face_y = doc["position"]["y"];

      xDiff = int(face_x * ratio + 0.5);
      yDiff = int(face_y * ratio + 0.5);
      // Control robot emotion (Example: LED feedback or servo movement)
      if (emotion == "happy") {

      } else if (emotion == "sad") {

      } else if (emotion == "angry") {
        // Example: Set LED to red
      }
    }
  }
}
void Screen_IdleGaze() {
  display.clearDisplay();
  display.fillRect(89 + xDiff, 12 + yDiff, 17, 24, SH110X_WHITE);

  display.fillCircle(97 + xDiff, 32 + yDiff, 8, SH110X_WHITE);

  display.fillCircle(97 + xDiff, 14 + yDiff, 8, SH110X_WHITE);

  display.fillRect(22 + xDiff, 12 + yDiff, 17, 24, SH110X_WHITE);

  display.fillCircle(30 + xDiff, 32 + yDiff, 8, SH110X_WHITE);

  display.fillCircle(30 + xDiff, 14 + yDiff, 8, SH110X_WHITE);

  display.fillCircle(67 + xDiff, 42 + yDiff, 3, SH110X_WHITE);

  display.fillCircle(70 + xDiff, 45 + yDiff, 3, SH110X_WHITE);

  display.fillCircle(64 + xDiff, 39 + yDiff, 3, SH110X_WHITE);

  display.fillCircle(62 + xDiff, 41 + yDiff, 3, SH110X_WHITE);

  display.fillCircle(60 + xDiff, 43 + yDiff, 3, SH110X_WHITE);

  display.fillCircle(58 + xDiff, 45 + yDiff, 3, SH110X_WHITE);

  display.display();
}
void Screen_Idle_FullEyesOpen() {
  display.clearDisplay();

  display.fillCircle(90, 26, 9, SH110X_WHITE);

  display.fillCircle(90, 21, 9, SH110X_WHITE);

  display.fillCircle(90, 31, 9, SH110X_WHITE);

  display.fillCircle(37, 26, 9, SH110X_WHITE);

  display.fillCircle(37, 21, 9, SH110X_WHITE);

  display.fillCircle(37, 31, 9, SH110X_WHITE);

  display.fillCircle(66, 46, 3, SH110X_WHITE);

  display.fillCircle(68, 44, 3, SH110X_WHITE);

  display.fillCircle(63, 49, 3, SH110X_WHITE);

  display.fillCircle(58, 44, 3, SH110X_WHITE);

  display.fillCircle(61, 47, 3, SH110X_WHITE);

  display.display();
}
void Screen_Idle_HalfEyesOpen() {
  display.clearDisplay();

  display.fillCircle(90, 25, 9, SH110X_WHITE);
  display.fillCircle(90, 26, 9, SH110X_WHITE);
  display.fillCircle(90, 28, 9, SH110X_WHITE);
  display.fillCircle(37, 26, 9, SH110X_WHITE);
  display.fillCircle(37, 25, 9, SH110X_WHITE);
  display.fillCircle(37, 28, 9, SH110X_WHITE);
  display.fillCircle(68, 44, 3, SH110X_WHITE);
  display.fillCircle(66, 46, 3, SH110X_WHITE);
  display.fillCircle(63, 49, 3, SH110X_WHITE);
  display.fillCircle(58, 44, 3, SH110X_WHITE);
  display.fillCircle(61, 47, 3, SH110X_WHITE);
  display.display();
}
void Screen_Idle_ClosedEyes() {
  display.clearDisplay();

  display.fillCircle(90, 25, 9, SH110X_WHITE);
  display.fillCircle(90, 26, 9, SH110X_WHITE);
  display.fillCircle(90, 28, 9, SH110X_WHITE);
  display.fillCircle(37, 26, 9, SH110X_WHITE);
  display.fillCircle(37, 25, 9, SH110X_WHITE);
  display.fillCircle(37, 28, 9, SH110X_WHITE);
  display.fillCircle(68, 44, 3, SH110X_WHITE);
  display.fillCircle(66, 46, 3, SH110X_WHITE);
  display.fillCircle(63, 49, 3, SH110X_WHITE);
  display.fillCircle(58, 44, 3, SH110X_WHITE);
  display.fillCircle(61, 47, 3, SH110X_WHITE);
  display.display();
}
void Screen_Happy_ClosedEyes_Top() {
  display.clearDisplay();

  display.fillCircle(93, 23, 3, SH110X_WHITE);

  display.fillCircle(96, 26, 3, SH110X_WHITE);

  display.fillCircle(90, 20, 3, SH110X_WHITE);

  display.fillCircle(64, 43, 3, SH110X_WHITE);

  display.fillCircle(87, 23, 3, SH110X_WHITE);

  display.fillCircle(69, 38, 3, SH110X_WHITE);

  display.fillCircle(67, 40, 3, SH110X_WHITE);

  display.fillCircle(84, 26, 3, SH110X_WHITE);

  display.fillCircle(59, 38, 3, SH110X_WHITE);

  display.fillCircle(61, 40, 3, SH110X_WHITE);

  display.fillCircle(40, 23, 3, SH110X_WHITE);

  display.fillCircle(43, 26, 3, SH110X_WHITE);

  display.fillCircle(37, 20, 3, SH110X_WHITE);

  display.fillCircle(34, 23, 3, SH110X_WHITE);

  display.fillCircle(31, 26, 3, SH110X_WHITE);
  display.display();
}
void Screen_Happy_ClosedEyes_Middle() {
  display.clearDisplay();

  display.fillCircle(96, 32, 3, SH110X_WHITE);

  display.fillCircle(93, 29, 3, SH110X_WHITE);

  display.fillCircle(90, 26, 3, SH110X_WHITE);

  display.fillCircle(64, 43, 3, SH110X_WHITE);

  display.fillCircle(67, 40, 3, SH110X_WHITE);

  display.fillCircle(69, 38, 3, SH110X_WHITE);

  display.fillCircle(87, 29, 3, SH110X_WHITE);

  display.fillCircle(61, 40, 3, SH110X_WHITE);

  display.fillCircle(59, 38, 3, SH110X_WHITE);

  display.fillCircle(84, 32, 3, SH110X_WHITE);

  display.fillCircle(40, 29, 3, SH110X_WHITE);

  display.fillCircle(43, 32, 3, SH110X_WHITE);

  display.fillCircle(37, 26, 3, SH110X_WHITE);

  display.fillCircle(34, 29, 3, SH110X_WHITE);

  display.fillCircle(31, 32, 3, SH110X_WHITE);

  display.display();
}
void Screen_Happy_ClosedEyes_Bottom() {
  display.clearDisplay();

  display.fillCircle(93, 26, 3, SH110X_WHITE);

  display.fillCircle(96, 29, 3, SH110X_WHITE);

  display.fillCircle(90, 23, 3, SH110X_WHITE);

  display.fillCircle(64, 43, 3, SH110X_WHITE);

  display.fillCircle(87, 26, 3, SH110X_WHITE);

  display.fillCircle(69, 38, 3, SH110X_WHITE);

  display.fillCircle(67, 40, 3, SH110X_WHITE);

  display.fillCircle(84, 29, 3, SH110X_WHITE);

  display.fillCircle(59, 38, 3, SH110X_WHITE);

  display.fillCircle(61, 40, 3, SH110X_WHITE);

  display.fillCircle(40, 26, 3, SH110X_WHITE);

  display.fillCircle(43, 29, 3, SH110X_WHITE);

  display.fillCircle(37, 23, 3, SH110X_WHITE);

  display.fillCircle(34, 26, 3, SH110X_WHITE);

  display.fillCircle(31, 29, 3, SH110X_WHITE);

  display.display();
}
void Screen_HeartEyes_Middle() {
  display.clearDisplay();

  display.fillCircle(93, 23, 6, SH110X_WHITE);
  display.fillCircle(83, 23, 6, SH110X_WHITE);
  display.fillCircle(88, 28, 6, SH110X_WHITE);
  display.fillCircle(34, 23, 6, SH110X_WHITE);
  display.fillCircle(44, 23, 6, SH110X_WHITE);
  display.fillCircle(39, 28, 6, SH110X_WHITE);
  display.fillCircle(67, 47, 4, SH110X_WHITE);
  display.fillCircle(63, 49, 4, SH110X_WHITE);
  display.fillCircle(55, 45, 4, SH110X_WHITE);
  display.fillCircle(59, 47, 4, SH110X_WHITE);
  display.fillCircle(71, 45, 4, SH110X_WHITE);
  display.display();
}
void Screen_HeartEyes_LeftUp() {
  display.clearDisplay();

  display.fillCircle(83, 25, 6, SH110X_WHITE);
  display.fillCircle(93, 25, 6, SH110X_WHITE);
  display.fillCircle(88, 30, 6, SH110X_WHITE);
  display.fillCircle(34, 20, 6, SH110X_WHITE);
  display.fillCircle(44, 20, 6, SH110X_WHITE);
  display.fillCircle(39, 25, 6, SH110X_WHITE);
  display.fillCircle(63, 49, 4, SH110X_WHITE);
  display.fillCircle(67, 47, 4, SH110X_WHITE);
  display.fillCircle(55, 45, 4, SH110X_WHITE);
  display.fillCircle(59, 47, 4, SH110X_WHITE);
  display.fillCircle(71, 45, 4, SH110X_WHITE);
  display.display();
}
void Screen_HeartEyes_RightUp() {
  display.clearDisplay();

  display.fillCircle(93, 20, 6, SH110X_WHITE);
  display.fillCircle(83, 20, 6, SH110X_WHITE);
  display.fillCircle(88, 25, 6, SH110X_WHITE);
  display.fillCircle(34, 25, 6, SH110X_WHITE);
  display.fillCircle(44, 25, 6, SH110X_WHITE);
  display.fillCircle(39, 30, 6, SH110X_WHITE);
  display.fillCircle(67, 47, 4, SH110X_WHITE);
  display.fillCircle(63, 49, 4, SH110X_WHITE);
  display.fillCircle(55, 45, 4, SH110X_WHITE);
  display.fillCircle(59, 47, 4, SH110X_WHITE);
  display.fillCircle(71, 45, 4, SH110X_WHITE);
  display.display();
}