#include "FastWire.h"

void WriteCommand(char command){
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);
  Wire.write(command);
  Wire.endTransmission();
}

void WriteDatum(char data){
  Wire.beginTransmission(0x3C);
  Wire.write(0x40);
  Wire.write(data);
  Wire.endTransmission();
}

void StartWritingMultiCommands(){
  Wire.beginTransmission(0x3C);
  Wire.write(0x80);
}

void StartWritingMultiData(){
  Wire.beginTransmission(0x3C);
  Wire.write(0xC0);
}

#define WriteMultiThings(command) Wire.write(command)

void EndWritingMultiThings(){
  Wire.endTransmission();
}

void OledInit(){

  StartWritingMultiCommands();
  WriteMultiThings(0xAE);//--turn off oled panel
  WriteMultiThings(0x00);//---set low column address
  WriteMultiThings(0x10);//---set high column address
  WriteMultiThings(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  WriteMultiThings(0x81);//--set contrast control register
  WriteMultiThings(0xCF); // Set SEG Output Current Brightness
  WriteMultiThings(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  WriteMultiThings(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  WriteMultiThings(0xA6);//--set normal display
  WriteMultiThings(0xA8);//--set multiplex ratio(1 to 64)
  WriteMultiThings(0x3f);//--1/64 duty
  WriteMultiThings(0xD3);//-set display offset        Shift Mapping RAM Counter (0x00~0x3F)
  WriteMultiThings(0x00);//-not offset
  WriteMultiThings(0xd5);//--set display clock divide ratio/oscillator frequency
  WriteMultiThings(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  WriteMultiThings(0xD9);//--set pre-charge period
  WriteMultiThings(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  WriteMultiThings(0xDA);//--set com pins hardware configuration
  WriteMultiThings(0x12);
  WriteMultiThings(0xDB);//--set vcomh
  WriteMultiThings(0x40);//Set VCOM Deselect Level
  WriteMultiThings(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  WriteMultiThings(0x02);//
  WriteMultiThings(0x8D);//--set Charge Pump enable/disable
  WriteMultiThings(0x14);//--set(0x10) disable
  WriteMultiThings(0xA4);
  WriteMultiThings(0xA6);
  WriteMultiThings(0xAF);
  EndWritingMultiThings();
}

unsigned char FrameBuffer[8][128] = {0};

void RefreshBuffer(){
  WriteCommand(0xAF);
  int i, n;
  for (i = 0; i < 8; i++)
  {
    WriteCommand(0xb0 + i);  //设置页地址(0~7)
    WriteCommand(0x00);      //设置显示位置—列低地址
    WriteCommand(0x10);      //设置显示位置—列高地址
    for (n = 0; n < 128; n++){
      WriteDatum(FrameBuffer[i][n]);
    }
  }
}

void RefreshNewBuffer(){
  WriteCommand(0xAF);
  int i, n;
  for (i = 0; i < 8; i++)
  {
    // Set Refreshing Area
    StartWritingMultiCommands();
    WriteMultiThings(0xb0 + i);  // Set Page Address(0-7)
    WriteMultiThings(0x00);      // Set Low  Row Address
    WriteMultiThings(0x10);      // Set High Row Address
    EndWritingMultiThings();

    // Refresh it
    StartWritingMultiData();
    for (n = 0; n < 128; n++){
      WriteMultiThings(FrameBuffer[i][n]);
    }
    EndWritingMultiThings();
  }
}

void setup() {
//  Serial.begin(9600);
  Wire.begin();
  OledInit();
  
  for(int page = 0; page < 8; page++){
    for(int x = 0; x < 128; x++){
      FrameBuffer[page][x] = 255;
      RefreshBuffer();
    }
  }
}

void loop() {
  ;
}
