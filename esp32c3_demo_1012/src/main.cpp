/*** 
 * @Author: xuyang
 * @Date: 2024-10-12 14:21:16
 * @LastEditors: xuyang
 * @LastEditTime: 2024-10-12 14:33:03
 * @FilePath: \esp32c3_demo_1012\src\main.cpp
 * @Description: 
 * @
 * @Copyright (c) 2024 by xuyang, All Rights Reserved 
 */
#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  //设置引脚12和13为输出模式
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  //让引脚12和13的led闪烁
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  delay(1000);
  
}
