/***
 * @Author: xuyang
 * @Date: 2024-10-12 14:35:15
 * @LastEditors: xuyang
 * @LastEditTime: 2024-10-12 15:04:13
 * @FilePath: \UNO_formal_1012\src\main.cpp
 * @Description:
 * @
 * @Copyright (c) 2024 by xuyang, All Rights Reserved
 */
#include <Arduino.h>
#include <Servo.h>
/* -------------------------------------------------------------------------- */
/*                                    定义与声明                                    */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- 引脚定义 ---------------------------------- */
const int X_DIR_PIN = 5;
const int Y_DIR_PIN = 6;
const int X_STEP_PIN = 2;
const int Y_STEP_PIN = 3;
const int SERVO_PIN = 4;     // 对应UNO板子上面的Z轴的STEP引脚
const int RGB_CTRL_PIN = 11; // RGB彩灯的PWM引脚
const int ENABLE_PIN = 8;

// 步进电机控制速度
const int internal_time = 500;
const int servo_speed_time = 2000;
// 声明servo类
Servo servo;

/* ---------------------------------- 函数声明 ---------------------------------- */
void move_X_(int x_mm);
void move_Y_(int y_mm);

/* -------------------------------------------------------------------------- */
/*                                    setup                                   */
/* -------------------------------------------------------------------------- */
void setup()
{
  // 设置引脚模式
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(RGB_CTRL_PIN, OUTPUT);
  /* -------------------------------- 开启RGB灯的部分 ------------------------------- */
  // int pwmValue = (2/ 5.0) * 255;      // 计算出对应的占空比
  // analogWrite(RGB_CTRL_PIN, pwmValue); // 点亮RGB灯
  // 启用步进电机驱动器（负电平有效）
  digitalWrite(ENABLE_PIN, LOW);

  // 初始化舵机
  servo.attach(SERVO_PIN, 500, 2500);
}

/* -------------------------------------------------------------------------- */
/*                                    loop                                    */
/* -------------------------------------------------------------------------- */
void loop()
{
  move_X_(50);
  delay(1000);
  move_Y_(50);
  delay(20000); // 等待

  // 将舵机移动到0度
  // servo.write(0);
  // delay(servo_speed_time); // 将舵机移动到90度 servo.write(90); delay(servo_speed_time);
  // servo.write(90);
  // delay(servo_speed_time);

  // 将舵机移动到180度 servo.write(180); delay(servo_speed_time)
}

/* -------------------------------------------------------------------------- */
/*                                    函数定义                                    */
/* -------------------------------------------------------------------------- */
// 控制吸头在X轴方向移动
void move_X_(int x_mm)
{
  if (x_mm >= 0)
  {
    digitalWrite(X_DIR_PIN, HIGH); // HIGH
    digitalWrite(Y_DIR_PIN, HIGH); // LOW
  }
  else if (x_mm < 0)
  {
    x_mm = -x_mm;
    digitalWrite(X_DIR_PIN, LOW); // HIGH
    digitalWrite(Y_DIR_PIN, LOW); // LOW
  }
  int x_count = x_mm * 4.897;
  for (int i = 0; i < x_count; i++)
  { // 进行200个步进，具体数值可调整
    digitalWrite(X_STEP_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(internal_time); // 控制步进速度，数值可调整
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(internal_time);
  }
}

// 控制吸头在Y轴方向移动
void move_Y_(int y_mm)
{
  if (y_mm >= 0)
  {
    digitalWrite(X_DIR_PIN, LOW);  // HIGH
    digitalWrite(Y_DIR_PIN, HIGH); // LOW
  }
  else if (y_mm < 0)
  {
    y_mm = -y_mm;
    digitalWrite(X_DIR_PIN, HIGH); // HIGH
    digitalWrite(Y_DIR_PIN, LOW);  // LOW
  }
  int y_count = y_mm * 4.897;
  for (int i = 0; i < y_count; i++)
  { // 进行200个步进，具体数值可调整
    digitalWrite(X_STEP_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(internal_time); // 控制步进速度，数值可调整
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(internal_time);
  }
}
