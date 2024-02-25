#include "Arduino.h"
#include <Wire.h>
#include "ADT7410Lib.h"

ADT7410::ADT7410(int Mode){
  /*ADT7410のコンストラクタです*/
  Wire.beginTransmission(ADT7410_address); //ADT7410とI2C通信を開始
  mode=Mode;
  if(mode==16){
    Wire.write(Configuration_register); //設定レジスタに書き込みを指示
    Wire.write(0x80); //設定レジスタに0x80を書き込み=>16bitモードへ
    delay(240); //設定が有効になるまで待機
  }
  else if(mode==13);
  else{
    Serial.println("エラー:");
    Serial.println("無効なモードが指定されました");
    Serial.println("ADT7410のコンストラクタの引数には13か16を指定してください");
  }
  Wire.endTransmission();
}

float ADT7410::getTempData(){
  /*ADT7410から16bitまたは13bitのデータを受信し、温度(℃)を返します*/ 
  Wire.requestFrom((uint8_t)ADT7410_address, (uint8_t)2); //ADT7410から2byteデータを受信
  int tempSign = (Wire.read()<<8) | Wire.read() ; //2byteを結合し16bitの温度データとして取得
  if(mode==16){
    return convTempData(tempSign);
  }
  else if(mode==13){
    tempSign=tempSign>>3; //13bit化
    return convTempData(tempSign);
  }
  else return (float) -1;
}

float ADT7410::convTempData(int tempSign){
  /*ADT7410から取得したデータを浮動小数表示に変換します*/ 
  if(mode==16){
    int temp = tempSign & 0x7fff; //符号ビットを除去
    if (tempSign & 0x8000 ) temp = -( (~temp & 0x7fff) +1); //温度が負の場合、2の補数をとる
    return temperature = temp * 0.0078 ; //128で割って0.0078℃/LSBの変換を行う
  }
  else if(mode==13){ 
    int temp = (tempSign & 0x1000) ? (tempSign - 0x2000) : tempSign; //符号判定した値を返す
    return temperature = temp * 0.0625; //16で割って0.0625℃/LSBの変換を行う
  }
  else return (float) -1;
}
