#include <Arduino.h>
#include <vector>
#include <WiFi.h>
#include <Wire.h>
#include "SPI.h"
#include "Adafruit_GFX.h"  //for matrix led
#include "Adafruit_LEDBackpack.h"

#include "Servo.h"
#include "MLBlockSerial.h"
MLBlockSerial mlblock(&Serial);

#include "KB_initBoard.h"
#include "KB_music.h"
#include "KB_LDR.h"
#include "KB_LM73.h"
#include "KB_ht16k33.h"
#include "MCP7941x.h"
#include "Kalman.h"
#include "TFT_eSPI.h"  //for matrix led

TFT_eSPI tft = TFT_eSPI();
MCP7941x rtc = MCP7941x();
Kalman mpu;
KB_board board = KB_board();
KB_music music = KB_music();
KB_LDR ldr = KB_LDR();
KB_LM73 lm73 = KB_LM73();
KB_8x16Matrix matrix = KB_8x16Matrix();

typedef int Number;
typedef int Boolean;
using namespace std;

Servo Servo1;

void OnResult(MLObject __result) {
  if ((__result.classId) == 1) {
    matrix.drawBitmap(
        0, 0, (uint8_t *)"\x0\x0\x0\x0\x0\x1\x1\xff\x41\x21\x0\x0\x0\x0\x0\x0");
    Servo1.write(180);
  } else {
    matrix.drawBitmap(
        0, 0,
        (uint8_t *)"\x0\x0\x0\x0\x0\x3c\x42\x81\x81\x42\x3c\x0\x0\x0\x0\x0");
    Servo1.write(0);
  }
}

void setup() {
  board.begin();
  music.begin();
  lm73.begin();
  matrix.displayBegin();
  ldr.begin();

  Serial.begin(115200);

  Servo1.attach(15);
  matrix.printText(0, 0, " ");
  mlblock.setOnResult(OnResult);
}
void loop() {
  mlblock.process();
}
