# 1 "E:\\win_code_git\\alist_ACTIVITY\\writing_robot\\esp32_demo001_servo\\esp32_demo001_servo.ino"
# 2 "E:\\win_code_git\\alist_ACTIVITY\\writing_robot\\esp32_demo001_servo\\esp32_demo001_servo.ino" 2

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
