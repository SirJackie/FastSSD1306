#include <Wire.h>

void WriteCommand(char command){
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);
  Wire.write(command);
  Wire.endTransmission();
}

void WriteData(char data){
  Wire.beginTransmission(0x3C);
  Wire.write(0x40);
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  WriteCommand(0xAE);//--turn off oled panel
  WriteCommand(0x00);//---set low column address
  WriteCommand(0x10);//---set high column address
  WriteCommand(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  WriteCommand(0x81);//--set contrast control register
  WriteCommand(0xCF); // Set SEG Output Current Brightness
  WriteCommand(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  WriteCommand(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  WriteCommand(0xA6);//--set normal display
  WriteCommand(0xA8);//--set multiplex ratio(1 to 64)
  WriteCommand(0x3f);//--1/64 duty
  WriteCommand(0xD3);//-set display offset        Shift Mapping RAM Counter (0x00~0x3F)
  WriteCommand(0x00);//-not offset
  WriteCommand(0xd5);//--set display clock divide ratio/oscillator frequency
  WriteCommand(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  WriteCommand(0xD9);//--set pre-charge period
  WriteCommand(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  WriteCommand(0xDA);//--set com pins hardware configuration
  WriteCommand(0x12);
  WriteCommand(0xDB);//--set vcomh
  WriteCommand(0x40);//Set VCOM Deselect Level
  WriteCommand(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  WriteCommand(0x02);//
  WriteCommand(0x8D);//--set Charge Pump enable/disable
  WriteCommand(0x14);//--set(0x10) disable
  WriteCommand(0xA4);
  WriteCommand(0xA6);
  WriteCommand(0xAF);
  
  WriteCommand(0xAF);
  // put your main code here, to run repeatedly:
  int i, n;
  for (i = 0; i < 8; i++)
  {
    WriteCommand(0xb0 + i);  //设置页地址(0~7)
    WriteCommand(0x00);      //设置显示位置—列低地址
    WriteCommand(0x10);      //设置显示位置—列高地址
    for (n = 0; n < 128; n++){
      WriteData(255);
    }
  }
}

int count = 1;

void loop() {
//  WriteCommand(0xAF);
//  // put your main code here, to run repeatedly:
//  int i, n;
//  for (i = 0; i < 8; i++)
//  {
//    WriteCommand(0xb0 + i);  //设置页地址(0~7)
//    WriteCommand(0x00);      //设置显示位置—列低地址
//    WriteCommand(0x10);      //设置显示位置—列高地址
//    for (n = 0; n < 128; n++){
//      WriteData(count);
////      delayMicroseconds(0);
//    }
//  }
//
////  delay(1000);
//  count += 1;
  WriteCommand(0xAF);
  // put your main code here, to run repeatedly:
  int i, n;
  for (i = 0; i < 8; i++)
  {
    WriteCommand(0xb0 + i);  //设置页地址(0~7)
    WriteCommand(0x00);      //设置显示位置—列低地址
    WriteCommand(0x10);      //设置显示位置—列高地址
    for (n = 0; n < 128; n++){
      WriteData(254);
    }
  }
  Serial.println("alpha");
//  delay(50);
}
