#include "hx711.h"

// 初始化HX711
HX711::HX711(int SCK_PIN,int DT_PIN)
{
    HX711_SCK = SCK_PIN;
    HX711_DT = DT_PIN;  
}

//启动HX711
void HX711::begin()
{
  pinMode(HX711_SCK, OUTPUT);	
  pinMode(HX711_DT, INPUT);
  digitalWrite(HX711_SCK, LOW);   // 系统进入正常工作状态
}

//读取HX711产生24位A/D数据
//输入通道：A通道，增益：128
long HX711::HX711_Read() 
{
  long count;                        // 储存24位A/D采样值
	unsigned char i;

  count = 0;        
  while(digitalRead(HX711_DT));     // 当DT值为1时，等待AD转换 
  
  noInterrupts();                   // 禁止中断
  for(i = 0; i < 24; i++)           // 24个脉冲，对应读取24位数值
  { 
     count = count << 1;            // 左移一位，最低位准备用于存储新读入的DT值   
    digitalWrite(HX711_SCK, HIGH);  // SCK=1 
    delayMicroseconds(1);           // 延时1us

    if(digitalRead(HX711_DT))      // 当DT值为1时，count值加1
         count++; 
      
    digitalWrite(HX711_SCK, LOW);  // SCK=0
    delayMicroseconds(1);          // 延时1us
  }
 	digitalWrite(HX711_SCK, HIGH);  // 再来一次上升沿，选择工作方式：128增益
	delayMicroseconds(1);           // 延时1us
	digitalWrite(HX711_SCK, LOW);   // SCK=0
	delayMicroseconds(1);           // 延时1us 
  interrupts(); 
  if(count & 0x800000) count |= 0xFF000000;  
	return(count);                 // 返回传感器读取值
}
