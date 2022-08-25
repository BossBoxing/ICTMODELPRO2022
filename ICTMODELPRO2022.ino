#include "ModelPro.h"
#include "EEPROM.h"

#define S_LLL map(analog(0),0,1023,0,100)
#define S_LL map(analog(1),0,1023,0,100)
#define S_L map(analog(2),0,1023,0,100)
#define S_C map(analog(3),0,1023,0,100)
#define S_R map(analog(4),0,1023,0,100)
#define S_RR map(analog(5),0,1023,0,100)
#define S_RRR map(analog(6),0,1023,0,100)

#define startReffAddress 10

#define Ref_LLL EEPROM.read(startReffAddress + 1)
#define Ref_LL EEPROM.read(startReffAddress + 2)
#define Ref_L EEPROM.read(startReffAddress + 3)
#define Ref_C EEPROM.read(startReffAddress + 4)
#define Ref_R EEPROM.read(startReffAddress + 5)
#define Ref_RR EEPROM.read(startReffAddress + 6)
#define Ref_RRR EEPROM.read(startReffAddress + 7)

int x;
int function;

#define A0 1 //ขาต่อ servo ตัวยก
#define A1 2 //ขาต่อ servo ตัวหนีบ

int Lift_Max = 109; //ค่า servo ตอนยกมือลงสุด
int Lift_Min = 177; //ค่า servo ตอนยกมือขึ้นสุด
int Lift = Lift_Min;

int Pin_Max = 60;  //ค่า servo ตอนไม่ได้หนีบ
int Pin_Min = 140; //ค่า servo ตอนหนีบ
int Pin = Pin_Max;

int power_manual_fast_L = 80;
int power_manual_fast_R = 77;

int power_manual_slow_L = 40;
int power_manual_slow_R = 40;

void setup()
{
  ok();
}
void loop()
{
  if (function == 0)
  {
    oledClear();
    setTextSize(2);
    oled(1,10,"Running.. ");
    while (Serial1.available() > 0)
    {
      x = Serial1.read();
      // oled(0, 0, "DEC= %d ", x);
      switch (x)
      {
      case 136:
        Fast_forward();
        break;
      case 129:
        Fast_backward();
        break;
      case 132:
        Fast_left();
        break;
      case 130:
        Fast_righ();
        break;

      case 24:
        Slow_forward();
        break;
      case 17:
        Slow_backward();
        break;
      case 20:
        Slow_left();
        break;
      case 18:
        Slow_righ();
        break;

      case 72:
        Lift_up();
        break;
      case 65:
        Lift_down();
        break;
      case 68:
        Pin_in();
        break;
      case 66:
        Pin_out();
        break;

      case 200:
        Brown();
        break;
      case 196:
        Pink();
        break;
      case 194:
        Orange();
        break;
      case 193:
        Yellow();
        break;

      case 56:
        Green();
        break;
      case 52:
        Blue();
        break;
      case 50:
        Purple();
        break;

      default:
        Stop();
      }
    }
  }
  else if(function == 1){
    setSensor();
  }
  else if(function == 2){
    readServo();
  }
  else if(function == 3){
    oledClear();
    setTextSize(1);
    while(1){
      oled(5,0,"L3:%d ", S_LLL);
      oled(5,10,"L2:%d ", S_LL);
      oled(5,20,"L1:%d ", S_L);
      oled(5,30,"C:%d ", S_C);
      oled(5,40,"R1:%d ", S_R);
      oled(5,50,"R2:%d ", S_RR);
      oled(5,60,"R3:%d ", S_RRR);
      delay(50);
      oledClear();
    }
  }
}
