

#include "Timer.h"

#define LOCK 0
#define UNLOCK 1
#define WATER 2
#define CHOUNTER_THRESHOLD 150

uint8_t state = LOCK;

// Variables will change:
int timerCounter = 0;         // counter for the number of button presses
int buttonLockState = HIGH;          // current state of the lock button
int lastButtonLockState = HIGH;      // previous state of the lock button
int buttonWaterState = HIGH;          // current state of the water button
int lastButtonWaterState = HIGH;      // previous state of the water button
int redLedState = 0; 
int greenLedState = 0; 
unsigned char buttonLockDect = 0;     //按键状态值，1：按下；2：松开
unsigned char buttonWaterDect = 0;     //按键状态值，1：按下；2：松开
int buttonWaterActivated = 0;

void setup() {
  Serial.begin(19200);

  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(PUSH1,INPUT_PULLUP);
  pinMode(PUSH2,INPUT_PULLUP);

  digitalWrite(RED_LED,HIGH);
  
  // 设置定时器ISR为isrTimer，定时周期为20ms
  SetTimer(isrTimer, 20);
}

void isrTimer(void){
  Button_SM();  //启动长短键状态机
} 

void Button_SM(){
  
  buttonLockState = digitalRead(PUSH1);   //读取童锁键引脚值
  buttonWaterState = digitalRead(PUSH2);  //读取热水键引脚值

  //按键连接pin电平前高后低，表明按下
  if((lastButtonLockState == HIGH) && (buttonLockState == LOW)){
    buttonLockDect = 1;
    timerCounter = 0;
  }
    
  if((lastButtonWaterState == HIGH) && (buttonWaterState == LOW))
    buttonWaterDect = 1;

  //按键连接pin电平前低后高，表明弹起
  if((lastButtonLockState == LOW) && (buttonLockState == HIGH)){
    buttonLockDect = 2;
    timerCounter = 0;    
  }
  if((lastButtonWaterState == LOW) && (buttonWaterState == HIGH))
    buttonWaterDect = 2;

  switch(state){
    case LOCK:
      if(buttonLockDect == 1)
        if(timer3s()){  //童锁按下满3s事件发生        
          digitalWrite(RED_LED,LOW);  //童锁指示灯灭
          state = UNLOCK; //状态机将转入UNLOCK状态
          Serial.println("解锁了");
        }
      break;
      
    case UNLOCK:
      if(timer3s()){  //3s无操作事件发生        
        digitalWrite(RED_LED,HIGH);  //童锁指示灯亮
        state = LOCK;                 //状态机将转入LOCK状态
        Serial.println("超时");
      }
      
      if(buttonWaterDect == 1){
        buttonWaterActivated = 1;
        timerCounter = 0;
        Serial.println("放水按下");
      }        
      else if(buttonWaterDect == 2){
        if (buttonWaterActivated == 1){  //放水弹起     
          buttonWaterActivated = 0; //本次按键已处理   
          digitalWrite(GREEN_LED,HIGH);  //放水指示灯亮
          state = WATER;
          Serial.println("放水中");
        }
      }      
      break;
     
    case WATER:
      if(buttonWaterDect == 1){
        buttonWaterActivated = 1;
        Serial.println("放水按下");
      }        
      else if (buttonWaterActivated == 1){//放水弹起
        if(buttonWaterDect == 2){  //又按了一次出水  
          buttonWaterActivated = 0;
          digitalWrite(GREEN_LED,LOW);  //放水指示灯灭
          digitalWrite(RED_LED,HIGH);   //童锁指示灯亮
          state = LOCK; //状态机将转入LOCK状态
          Serial.println("结束放水");
        }           
      }
        
      break;
       
    default:
      state = LOCK;
      break;
  }
  lastButtonLockState = buttonLockState;
  lastButtonWaterState = buttonWaterState;
}

//对Timer中断计时，计满清零并返回“满3s”信息
//“满3s”事件发生时，返回true，否则返回false
bool timer3s(){
  timerCounter++;
  if(timerCounter == CHOUNTER_THRESHOLD){
    timerCounter = 0;
    return true;
  }
  else
    return false;
}

void loop() {
  
  delay(1);  
}
