#include <ADT7410Lib.h>
#include <Wire.h>

void setup() {
    Wire.begin();
    Serial.begin(9600);
}
 
void loop() {
  //コンストラクタを作成
  static ADT7410 adt7410;
  //温度データを取得
  float temp=adt7410.getTempData();
  //温度データをシリアルモニタに表示
  adt7410.showTempDataSerial();
  delay(1000);
}