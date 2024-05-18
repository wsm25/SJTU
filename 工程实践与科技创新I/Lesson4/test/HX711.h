#ifndef __HX711__H__
#define __HX711__H__

#include <Energia.h>    //使用Energia的头文件

class HX711
{
public:
  HX711(int SCK_PIN,int DT_PIN);  
  void begin();       // 初始化HX711  
  long HX711_Read();  // 传感器数据读取函数
private:	
  int HX711_SCK;      // HX711_SCK为输出口 —— 输出脉冲
  int HX711_DT;       // HX711_DT为输入口  —— 读取数据
};

#endif
