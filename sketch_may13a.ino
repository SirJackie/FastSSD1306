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

void StartWritingMultiThings(){
  Wire.beginTransmission(0x3C);
}

void WriteMultiCommands(char command){
  Wire.write(0x80);
  Wire.write(command);
}

void WriteMultiData(char data){
  Wire.write(0xC0);
  Wire.write(data);
}

void EndWritingMultiThings(){
  Wire.endTransmission();
}

void OledInit(){

  StartWritingMultiThings();
  WriteMultiCommands(0xAE);//--turn off oled panel
  WriteMultiCommands(0x00);//---set low column address
  WriteMultiCommands(0x10);//---set high column address
  WriteMultiCommands(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  WriteMultiCommands(0x81);//--set contrast control register
  WriteMultiCommands(0xCF); // Set SEG Output Current Brightness
  WriteMultiCommands(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  WriteMultiCommands(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  WriteMultiCommands(0xA6);//--set normal display
  WriteMultiCommands(0xA8);//--set multiplex ratio(1 to 64)
  WriteMultiCommands(0x3f);//--1/64 duty
  WriteMultiCommands(0xD3);//-set display offset        Shift Mapping RAM Counter (0x00~0x3F)
  WriteMultiCommands(0x00);//-not offset
  WriteMultiCommands(0xd5);//--set display clock divide ratio/oscillator frequency
  WriteMultiCommands(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  WriteMultiCommands(0xD9);//--set pre-charge period
  WriteMultiCommands(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  WriteMultiCommands(0xDA);//--set com pins hardware configuration
  WriteMultiCommands(0x12);
  WriteMultiCommands(0xDB);//--set vcomh
  WriteMultiCommands(0x40);//Set VCOM Deselect Level
  WriteMultiCommands(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  WriteMultiCommands(0x02);//
  WriteMultiCommands(0x8D);//--set Charge Pump enable/disable
  WriteMultiCommands(0x14);//--set(0x10) disable
  WriteMultiCommands(0xA4);
  WriteMultiCommands(0xA6);
  WriteMultiCommands(0xAF);
  EndWritingMultiThings();
}

unsigned char FrameBuffer[8][128] = {0};

void RefreshBuffer(){
  WriteCommand(0xAF);
  int i, n;
  for (i = 0; i < 8; i++)
  {
    StartWritingMultiThings();
    WriteMultiCommands(0xb0 + i);  // Set Page Address(0-7)
    WriteMultiCommands(0x00);      // Set Low  Row Address
    WriteMultiCommands(0x10);      // Set High Row Address
    EndWritingMultiThings();

//    WriteCommand(0xb0 + i);  // Set Page Address(0-7)
//    WriteCommand(0x00);      // Set Low  Row Address
//    WriteCommand(0x10);      // Set High Row Address
    
    StartWritingMultiThings();
    for (n = 0; n < 128; n++){
      
      WriteMultiData(FrameBuffer[i][n]);
//      delay(1);
      
//      WriteDatum(FrameBuffer[i][n]);
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
      FrameBuffer[page][x] = 0;
    }
  }
  RefreshBuffer();
  
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
