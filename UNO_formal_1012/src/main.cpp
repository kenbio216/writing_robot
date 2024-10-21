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
// 电机引脚
const int ENABLE_PIN = 8;
const int X_DIR_PIN = 5;
const int Y_DIR_PIN = 6;
const int X_STEP_PIN = 2;
const int Y_STEP_PIN = 3;

// 其他引脚
const int SERVO_PIN = 4;     // 对应UNO板子上面的Z轴的STEP引脚
const int RGB_CTRL_PIN = 11; // RGB彩灯的PWM引脚
const int CIFA_PIN = 10;     // 电磁阀对应的引脚，控制气泵的直接断开
const int QIBENG_PIN = 7;    // 气泵的控制引脚，对应Z的DIR

// 步进电机控制速度
const int internal_time = 500;
// const int servo_speed_time = 2000;
// 声明servo类
Servo servo;

/* ---------------------------------- 函数声明 ---------------------------------- */
void move_X_(int x_mm);
void move_Y_(int y_mm);
void turn_on_qb(void);
void turn_off_qb(void);
void servo_set(void);
void servo_up(void);
void servo_down(void);
void xizi(void);
void luozi(void);
void parseCommand(String input);
/* -------------------------------------------------------------------------- */
/*                                    setup                                   */
/* -------------------------------------------------------------------------- */

void setup()
{
  // 初始化串口通讯
  Serial.begin(115200);
  // 设置引脚模式
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(RGB_CTRL_PIN, OUTPUT);
  pinMode(CIFA_PIN, OUTPUT);
  pinMode(QIBENG_PIN, OUTPUT);
  /* -------------------------------- 开启RGB灯的部分 ------------------------------- */
  int pwmValue = (1 / 5.0) * 255;      // 计算出对应的占空比
  analogWrite(RGB_CTRL_PIN, pwmValue); // 点亮RGB灯

  // 启用步进电机驱动器（负电平有效）
  digitalWrite(ENABLE_PIN, LOW);
  // 初始化继电器（关闭气泵）digitalWrite(QIBENG_PIN, HIGH);
  // turn_off_qb();
  // 初始化舵机
  servo.attach(SERVO_PIN, 500, 2500);
  servo.write(180);
}

// 全局变量用于记录X和Y轴的移动总量
long totalX = 0;
long totalY = 0;
/* -------------------------------------------------------------------------- */
/*                                    loop                                    */
/* -------------------------------------------------------------------------- */
int servo_delay_time = 800;
int dd = 500;
void loop()
{
  /* --------------------------------- 串口调试系统 --------------------------------- */
  if (Serial.available() > 0)
  {
    // 读取一整行输入的字符串
    String input = Serial.readStringUntil('\n');
    input.trim();        // 去掉输入中的空白符
    parseCommand(input); // 解析输入指令
  }

   digitalWrite(QIBENG_PIN, 0); //1为启动，0为关闭
  digitalWrite(CIFA_PIN, 0); //0为没有上电，1为上电
  delay(20000);

  // move_X_(30);
  // delay(dd);
  // move_X_(-30);
  // delay(dd);
  // delay(20000);

  // delay(1000);
  // 将舵机移动到0度
  // servo.write(180);
  // delay(servo_delay_time);
  // servo.write(90);
  // delay(servo_delay_time);
  // servo.write(180);
  // delay(servo_delay_time);
  // delay(20000); // 等待

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
  Serial.print("Moving X by: ");
  Serial.println(x_mm);
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
  Serial.print("Moving Y by: ");
  Serial.println(y_mm);
}

void turn_on_qb()
{
  digitalWrite(QIBENG_PIN, LOW); // 打开气泵
}

void turn_off_qb()
{
  digitalWrite(QIBENG_PIN, HIGH); // 关闭气泵
}

void servo_set()
{
  servo.write(180);
}

void servo_up()
{
  servo.write(180);
}
void servo_down()
{
  servo.write(90);
}

void xizi()
{
  servo_down();
  turn_on_qb();
  delay(1500);
  servo_up();
  turn_off_qb();
  delay(1500);
}

void luozi()
{
  servo_down();
  turn_off_qb();
  delay(2000);
  servo_up();
}

// 解析和执行串口指令
void parseCommand(String input)
{
  if (input.startsWith("MOVEX"))
  {
    // 提取数字并调用move_X_函数
    long value = input.substring(5).toInt();
    totalX += value; // 累加X轴的移动量
    move_X_(value);  // 调用原有的move_X_函数
  }
  else if (input.startsWith("MOVEY"))
  {
    // 提取数字并调用move_Y_函数
    long value = input.substring(5).toInt();
    totalY += value; // 累加Y轴的移动量
    move_Y_(value);  // 调用原有的move_Y_函数
  }
  else if (input == "RETURNX")
  {
    // 返回X轴的总移动值
    Serial.print("X total move: ");
    Serial.println(totalX);
  }
  else if (input == "RETURNY")
  {
    // 返回Y轴的总移动值
    Serial.print("Y total move: ");
    Serial.println(totalY);
  }
  else
  {
    // 如果是无效指令，提示用户
    Serial.println("Invalid command.");
  }
}