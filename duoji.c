#include <Servo.h>
#include <MsTimer2.h>

Servo myservo;
int pos=0;
int INTERVAL=500;
int button=6;
int led=13;
int a=0;


void ggyy(){  //led闪烁
  static int gy=0;
  gy=1-gy;
  digitalWrite(led,gy);
}

void setup(){
  pinMode(led,OUTPUT);
  pinMode(button,INPUT);
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(pos); //初始化舵机的角度
}

void loop(){
  int num=digitalRead(button);
  
  if(num==HIGH){
    delay(200); //通过delay延迟函数来减颤
    if(a==0){  //判断a的值进行正反转
      if(pos<=180){
        pos=pos+10;
        Serial.println(pos);
        INTERVAL=INTERVAL-10;
        MsTimer2::set(INTERVAL,ggyy);
        MsTimer2::start();
        myservo.write(pos);
        if(pos==180){
          a=1;
        }
      }
    }
    if(a==1){
      if(pos >=0){
        pos=pos-10;
        INTERVAL=INTERVAL+10;
        MsTimer2::set(INTERVAL,ggyy); //通过INTERVAL控制led灯闪烁的频率
        MsTimer2::start();
        myservo.write(pos);
        if(pos==0){
          a=0;
        }
      }
    }
  
  }
  
} 

