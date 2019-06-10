int Left_motor_back = 9;   //左电机后退(IN1)
int Left_motor_go = 5;     //左电机前进(IN2)
int Right_motor_go = 6;    // 右电机前进(IN3)
int Right_motor_back = 10; // 右电机后退(IN4)

int speed = 200;

char getstr;

void setup()
{
    pinMode(Left_motor_go, OUTPUT);    // PIN 5 (PWM)
    pinMode(Left_motor_back, OUTPUT);  // PIN 9 (PWM)
    pinMode(Right_motor_go, OUTPUT);   // PIN 6 (PWM)
    pinMode(Right_motor_back, OUTPUT); // PIN 10 (PWM)
    Serial.begin(9600);
}

void loop()
{
    getstr = Serial.read();
    if (getstr == 'w')
    {
        run();
    }
    else if (getstr == 's')
    {
        back();
    }
    else if (getstr == 'a')
    {
        left();
    }
    else if (getstr == 'd')
    {
        right();
    }
    else if (getstr == ' ')
    {
        brake();
    }
}

void run()
{
    digitalWrite(Right_motor_go, HIGH); // 右电机前进
    digitalWrite(Right_motor_back, LOW);
    analogWrite(Right_motor_go, speed); //PWM比例0~255调速，左右轮差异略增减
    analogWrite(Right_motor_back, 0);
    digitalWrite(Left_motor_go, HIGH); // 左电机前进
    digitalWrite(Left_motor_back, LOW);
    analogWrite(Left_motor_go, speed); //PWM比例0~255调速，左右轮差异略增减
    analogWrite(Left_motor_back, 0);
    //delay(time * 100);   //执行时间，可以调整
}

void brake() //刹车，停车
{
    digitalWrite(Right_motor_go, LOW);
    digitalWrite(Right_motor_back, LOW);
    digitalWrite(Left_motor_go, LOW);
    digitalWrite(Left_motor_back, LOW);
}

//void left(int time)         //左转(左轮不动，右轮前进)
void left()
{
    digitalWrite(Right_motor_go, HIGH); // 右电机前进
    digitalWrite(Right_motor_back, LOW);
    analogWrite(Right_motor_go, speed);
    analogWrite(Right_motor_back, 0); //PWM比例0~255调速
    digitalWrite(Left_motor_go, LOW); //左轮后退
    digitalWrite(Left_motor_back, LOW);
    analogWrite(Left_motor_go, 0);
    analogWrite(Left_motor_back, 0); //PWM比例0~255调速
                                     //delay(time * 100);  //执行时间，可以调整
}

//void spin_left(int time)         //左转(左轮后退，右轮前进)
void spin_left()
{
    digitalWrite(Right_motor_go, HIGH); // 右电机前进
    digitalWrite(Right_motor_back, LOW);
    analogWrite(Right_motor_go, speed);
    analogWrite(Right_motor_back, 0); //PWM比例0~255调速
    digitalWrite(Left_motor_go, LOW); //左轮后退
    digitalWrite(Left_motor_back, HIGH);
    analogWrite(Left_motor_go, 0);
    analogWrite(Left_motor_back, speed); //PWM比例0~255调速
    //  delay(time * 100);  //执行时间，可以调整
}

//void right(int time)        //右转(右轮不动，左轮前进)
void right()
{
    digitalWrite(Right_motor_go, LOW); //右电机后退
    digitalWrite(Right_motor_back, LOW);
    analogWrite(Right_motor_go, 0);
    analogWrite(Right_motor_back, 0);  //PWM比例0~255调速
    digitalWrite(Left_motor_go, HIGH); //左电机前进
    digitalWrite(Left_motor_back, LOW);
    analogWrite(Left_motor_go, speed);
    analogWrite(Left_motor_back, 0); //PWM比例0~255调速
                                     //delay(time * 100);  //执行时间，可以调整
}

//void spin_right(int time)        //右转(右轮后退，左轮前进)
void spin_right()
{
    digitalWrite(Right_motor_go, LOW); //右电机后退
    digitalWrite(Right_motor_back, HIGH);
    analogWrite(Right_motor_go, 0);
    analogWrite(Right_motor_back, speed); //PWM比例0~255调速
    digitalWrite(Left_motor_go, HIGH);    //左电机前进
    digitalWrite(Left_motor_back, LOW);
    analogWrite(Left_motor_go, speed);
    analogWrite(Left_motor_back, 0); //PWM比例0~255调速
    //  delay(time * 100);  //执行时间，可以调整
}

//void back(int time)          //后退
void back()
{
    digitalWrite(Right_motor_go, LOW); //右轮后退
    digitalWrite(Right_motor_back, HIGH);
    analogWrite(Right_motor_go, 0);
    analogWrite(Right_motor_back, speed); //PWM比例0~255调速
    digitalWrite(Left_motor_go, LOW);  //左轮后退
    digitalWrite(Left_motor_back, HIGH);
    analogWrite(Left_motor_go, 0);
    analogWrite(Left_motor_back, speed); //PWM比例0~255调速
                                       //delay(time * 100);     //执行时间，可以调整
}