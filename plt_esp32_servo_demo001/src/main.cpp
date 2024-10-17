#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo;

void setup()
{
  // 初始化舵机
  servo.attach(22);
}
int delay_time = 400;
void loop()
{

  // 将舵机向右转（down）
  servo.write(80);
  delay(delay_time);
  servo.write(90);
  delay(delay_time);

  // 将舵机向左转(up)
  servo.write(120);
  delay(delay_time);
  servo.write(90);
  delay(delay_time);

  // // rotate clockwise full-speed
  // servo.writeMicroseconds(200);
  // delay(1000);

  // // rotation stopped
  // servo.writeMicroseconds(1500);
  // delay(1000);

  // // rotate clockwise full-speed
  // servo.writeMicroseconds(1300);
  // delay(1000);

  // // rotation stopped
  // servo.writeMicroseconds(1500);
  // delay(1000);
}
