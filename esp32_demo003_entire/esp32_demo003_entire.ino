// 引脚定义
const int X_DIR_PIN = 5;
const int Y_DIR_PIN = 6;
const int X_STEP_PIN = 2;
const int Y_STEP_PIN = 3;
const int ENABLE_PIN = 8;

void setup() {
  // 设置引脚模式
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // 启用步进电机驱动器（负电平有效）
  digitalWrite(ENABLE_PIN, LOW);
}
const int internal_time = 500;

void loop() {
  move_X_(80);
  delay(1000);
  move_X_(-50);

  // int x_mm = 50;

  //   if (x_mm >= 0) {
  //     digitalWrite(X_DIR_PIN, HIGH);  // HIGH
  //     digitalWrite(Y_DIR_PIN, HIGH);  // LOW
  //   } else if (x_mm < 0) {
  //     x_mm = -x_mm;
  //     digitalWrite(X_DIR_PIN, LOW);  // HIGH
  //     digitalWrite(Y_DIR_PIN, LOW);  // LOW
  //   }
  //   int x_count = x_mm * 4.897;
  //   for (int i = 0; i < x_count; i++) {  // 进行200个步进，具体数值可调整
  //     digitalWrite(X_STEP_PIN, HIGH);
  //     digitalWrite(Y_STEP_PIN, HIGH);
  //     delayMicroseconds(internal_time);  // 控制步进速度，数值可调整
  //     digitalWrite(X_STEP_PIN, LOW);
  //     digitalWrite(Y_STEP_PIN, LOW);
  //     delayMicroseconds(internal_time);
  //   }
  // // 设置方向
  // digitalWrite(X_DIR_PIN, HIGH);  // HIGH
  // digitalWrite(Y_DIR_PIN, HIGH);  // LOW

  // // X轴步进
  // for (int i = 0; i < 100; i++) {  // 进行200个步进，具体数值可调整
  //   digitalWrite(X_STEP_PIN, HIGH);
  //   digitalWrite(Y_STEP_PIN, HIGH);
  //   delayMicroseconds(internal_time);  // 控制步进速度，数值可调整
  //   digitalWrite(X_STEP_PIN, LOW);
  //   digitalWrite(Y_STEP_PIN, LOW);
  //   delayMicroseconds(internal_time);
  // }
  // delay(1000);  // 等待1秒

  // // 设置方向
  // digitalWrite(X_DIR_PIN, LOW);   // HIGH
  // digitalWrite(Y_DIR_PIN, HIGH);  // LOW

  // for (int i = 0; i < 100; i++) {  // 进行200个步进，具体数值可调整
  //   digitalWrite(X_STEP_PIN, HIGH);
  //   digitalWrite(Y_STEP_PIN, HIGH);
  //   delayMicroseconds(internal_time);  // 控制步进速度，数值可调整
  //   digitalWrite(X_STEP_PIN, LOW);
  //   digitalWrite(Y_STEP_PIN, LOW);
  //   delayMicroseconds(internal_time);
  // }

  delay(2000);  // 等待1秒

  // // 设置Y轴方向
  // digitalWrite(Y_DIR_PIN, HIGH);  // 设为高电平，改变方向可设为LOW

  // // Y轴步进
  // for (int i = 0; i < 200; i++) {  // 进行200个步进
  //   digitalWrite(Y_STEP_PIN, HIGH);
  //   delayMicroseconds(500);  // 控制步进速度
  //   digitalWrite(Y_STEP_PIN, LOW);
  //   delayMicroseconds(500);
  // }

  // delay(1000);  // 等待1秒
}

void move_X_(int x_mm) {
  if (x_mm >= 0) {
    digitalWrite(X_DIR_PIN, HIGH);  // HIGH
    digitalWrite(Y_DIR_PIN, HIGH);  // LOW
  } else if (x_mm < 0) {
    x_mm = -x_mm;
    digitalWrite(X_DIR_PIN, LOW);  // HIGH
    digitalWrite(Y_DIR_PIN, LOW);  // LOW
  }
  int x_count = x_mm * 4.897;
  for (int i = 0; i < x_count; i++) {  // 进行200个步进，具体数值可调整
    digitalWrite(X_STEP_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(internal_time);  // 控制步进速度，数值可调整
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(internal_time);
  }
}
void move_Y_(int y_mm) {
  if (y_mm >= 0) {
    digitalWrite(X_DIR_PIN, LOW);   // HIGH
    digitalWrite(Y_DIR_PIN, HIGH);  // LOW
  } else if (y_mm < 0) {
    y_mm = -y_mm;
    digitalWrite(X_DIR_PIN, HIGH);  // HIGH
    digitalWrite(Y_DIR_PIN, LOW);   // LOW
  }
  int y_count = y_mm * 4.897;
  for (int i = 0; i < y_count; i++) {  // 进行200个步进，具体数值可调整
    digitalWrite(X_STEP_PIN, HIGH);
    digitalWrite(Y_STEP_PIN, HIGH);
    delayMicroseconds(internal_time);  // 控制步进速度，数值可调整
    digitalWrite(X_STEP_PIN, LOW);
    digitalWrite(Y_STEP_PIN, LOW);
    delayMicroseconds(internal_time);
  }
}
