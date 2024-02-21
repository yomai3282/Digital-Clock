#ifndef ADT7410Lib
#define ADT7410Lib
#include "Arduino.h"

class ADT7410{
  private:
    const uint8_t ADT7410_address=0x48; //ADT7410のI2Cアドレス
    const uint8_t Configuration_register = 0x03 ; //設定レジスタのアドレス
    int mode; //16bitモードか13bitモードかを指定する整数
    float temperature; //変換後の温度データ
  public:
    //コンストラクタ
    ADT7410(int Mode=16); //Mode=13 or 16を指定 デフォルトは16
    float getTempData();
    float convTempData(int tempSign);
    void showTempDataSerial(){
      Serial.print("温度: ");
      Serial.print(temperature,2);
      Serial.println(" ℃");
      }
};

#endif