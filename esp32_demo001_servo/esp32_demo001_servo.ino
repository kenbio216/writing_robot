#include <ESP32Servo.h>

Servo servo;

void setup()
{
    // 初始化舵机
    servo.attach(22);
}

void loop()
{
    // 将舵机移动到0度
    servo.write(0);
    delay(2000);

    // 将舵机移动到90度
    servo.write(90);
    delay(2000);

    // 将舵机移动到180度
    servo.write(180);
    delay(2000);
}
