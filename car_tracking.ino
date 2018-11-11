int Left_motor_back = 9;   //左电机后退(IN1)
int Left_motor_go = 5;     //左电机前进(IN2)
int Right_motor_go = 6;    // 右电机前进(IN3)
int Right_motor_back = 10; // 右电机后退(IN4)

const int SensorRight1 = A4; //右一循迹红外传感器
const int SensorRight2 = A2; //右二循迹红外传感器(P3.2 OUT1)
const int SensorLeft2 = A3;  //左二循迹红外传感器(P3.3 OUT2)
const int SensorLeft1 = A5;  //左一循迹红外传感器

int SL2; //左循迹红外传感器状态
int SR2; //右循迹红外传感器状态
int SL1;
int SR1;

int speed = 75;

void setup()
{
    //初始化电机驱动IO为输出方式
    pinMode(Left_motor_go, OUTPUT);    // PIN 5 (PWM)
    pinMode(Left_motor_back, OUTPUT);  // PIN 9 (PWM)
    pinMode(Right_motor_go, OUTPUT);   // PIN 6 (PWM)
    pinMode(Right_motor_back, OUTPUT); // PIN 10 (PWM)
    pinMode(SensorRight2, INPUT);      //定义右循迹红外传感器为输入
    pinMode(SensorLeft2, INPUT);       //定义左循迹红外传感器为输入
    pinMode(SensorRight1, INPUT);
    pinMode(SensorLeft2, INPUT);
}

//=======================智能小车的基本动作=========================

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

void brake(int time) //刹车，停车
{
    digitalWrite(Right_motor_go, LOW);
    digitalWrite(Right_motor_back, LOW);
    digitalWrite(Left_motor_go, LOW);
    digitalWrite(Left_motor_back, LOW);
    delay(time); //执行时间，可以调整
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
    analogWrite(Right_motor_back, 50); //PWM比例0~255调速
    digitalWrite(Left_motor_go, LOW);  //左轮后退
    digitalWrite(Left_motor_back, HIGH);
    analogWrite(Left_motor_go, 0);
    analogWrite(Left_motor_back, 150); //PWM比例0~255调速
                                       //delay(time * 100);     //执行时间，可以调整
}

void shibie()
{
    SR2 = digitalRead(SensorRight2); //有信号表明在白色区域，车子底板上L3亮；没信号表明压在黑线上，车子底板上L3灭
    SL2 = digitalRead(SensorLeft2);  //有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭
    SR1 = digitalRead(SensorRight1);
    SL1 = digitalRead(SensorLeft1);
}

void tri()
{
    while (SL1 == HIGH && SL2 == LOW && SR2 == HIGH && SR1 == HIGH)
    {
        right();
        shibie();
    }
    while (SL1 == HIGH && SL2 == HIGH && SR2 == LOW && SR1 == HIGH)
    {
        left();
        shibie();
    }
}

void loop()
{
    //keysacn();//调用按键扫描函数
    while (1)
    {
        //有信号为LOW  没有信号为HIGH
        shibie();

        if (SL1 == LOW && SL2 == HIGH && SR2 == HIGH && SR1 == LOW)
        {
            run();
        }

        if (SL1 == HIGH && SL2 == HIGH && SR2 == HIGH && SR1 == HIGH)
        {
            brake(1);
        }
        if (SL1 == LOW && SL2 == LOW && SR2 == LOW && SR1 == LOW)
        {
            back();
        }
        if ((SL1 == LOW && SL2 == LOW && SR2 == LOW && SR1 == HIGH) || (SL1 == LOW && SL2 == LOW && SR2 == HIGH && SR1 == HIGH))
        {
            while ((SL1 == LOW && SL2 == LOW && SR2 == LOW && SR1 == HIGH) || (SL1 == LOW && SL2 == LOW && SR2 == HIGH && SR1 == HIGH))
            {
                spin_right();
                shibie();
            }
        }
        if (SL1 == LOW && SL2 == HIGH && SR2 == HIGH && SR1 == HIGH)
        {
            while ((SL1 == LOW && SL2 == HIGH && SR2 == HIGH && SR1 == HIGH))
            {
                spin_right();
                shibie();
                if ((SL1 == HIGH && SL2 == HIGH && SR2 == HIGH && SR1 == HIGH) || (SL1 == LOW && SL2 == HIGH && SR2 == LOW && SR1 == LOW))
                {
                    while (SL1 == HIGH && SL2 == HIGH && SR2 == HIGH && SR1 == HIGH)
                    {
                        right();
                        shibie();
                        tri();
                    }
                }
            }
        }

        if ((SL1 == HIGH && SL2 == LOW && SR2 == LOW && SR1 == LOW) || (SL1 == HIGH && SL2 == HIGH && SR2 == LOW && SR1 == LOW))
        {
            while ((SL1 == HIGH && SL2 == LOW && SR2 == LOW && SR1 == LOW) || (SL1 == HIGH && SL2 == HIGH && SR2 == LOW && SR1 == LOW))
            {
                spin_left();
                shibie();
            }
        }
        if ((SL1 == HIGH && SL2 == HIGH && SR2 == HIGH && SR1 == LOW))
        {
            while ((SL1 == HIGH && SL2 == HIGH && SR2 == HIGH && SR1 == LOW))
            {
                spin_left();
                shibie();
                if (SL1 == HIGH && SL2 == HIGH && SR2 == HIGH && SR1 == HIGH)
                {
                    while (SL1 == HIGH && SL2 == HIGH && SR2 == HIGH && SR1 == HIGH)
                    {
                        spin_left();
                        shibie();
                        tri();
                    }
                }
            }
        }
        if (SL1 == LOW && SL2 == LOW && SR2 == HIGH && SR1 == LOW)
        {
            right();
        }
        if (SL1 == LOW && SL2 == HIGH && SR2 == LOW && SR1 == LOW)
        {
            left();
        }
        else
        {
        }
    }
}