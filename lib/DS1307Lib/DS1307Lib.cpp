#include "Arduino.h"
#include <Wire.h>
#include "DS1307Lib.h"

//TimeDataのメンバ関数
void TimeData::setTimeData(int Year, int Month, int Day, int Week, int Hour, int Minute, int Second) {
  /*
  TimeDataのインスタンスのメンバに値をセットします
  */
  year = Year;
  month = Month;
  day = Day;
  week = Week;
  hour = Hour;
  minute = Minute;
  second = Second;
}

int* TimeData::getTimeData(){
  /*
  TimeDataのインスタンスのメンバの値を格納した配列のポインタとして渡します
  動的に確保した配列を渡すので、関数の呼び出し側でdelete[]を行うこと。
  */
  //例
  //int* timeData=rtc.getTimeData();
  //for(int i=0;i<7;i++){
  //  Serial.print(timeData[i],HEX);
  //  if(i!=6) Serial.print(",");
  //}
  //delete[] timeData;
  
  int* timeData=new int[7];
  int values[7]={year,month,day,week,hour,minute,second};
  for(int i=0;i<7;i++){
    timeData[i]=values[i];
  }
  return timeData;
}

void TimeData::showTimeDataSerial(){
  /*
  TimeDataクラスのインスタンスのメンバを
  シリアルモニタに2024/2/20(火) 16:41:27の形で表示します
  */
  Serial.print("20");
  Serial.print(hex2string(year));//year
  Serial.print("/");
  Serial.print(hex2string(month));//month
  Serial.print("/");
  Serial.print(hex2string(day));//day
  Serial.print("(");
  Serial.print(weeklist[week]);//week
  Serial.print(") ");
  Serial.print(hex2string(hour));//hour
  Serial.print(":");
  Serial.print(hex2string(minute));//minute
  Serial.print(":");
  Serial.print(hex2string(second));//second
  Serial.println();
}

String TimeData::hex2string(int num){
  /*
  16進数の整数型を10進数に変換し、0埋めされた2桁の文字列に変換します
  */
  char tmp[16];
  char param[5] = "%02x";
  sprintf(tmp,param,num);
  return tmp;
}

//DS1307のメンバ関数
void DS1307::write(){
  /*
  RTCにデータを書き込みます
  */
  Wire.beginTransmission(RTC_address);
  Wire.write(address);//Register 先頭アドレス
  Wire.write(second);//second
  Wire.write(minute);//minute
  Wire.write(hour);//hour
  Wire.write(week);//week
  Wire.write(day);//day
  Wire.write(month);//month
  Wire.write(year);//year
  Wire.endTransmission();
}

void DS1307::read(){
  /*
  RTCからデータを読み込みます
  */
  Wire.beginTransmission(RTC_address);
  Wire.write(address);//Register 先頭アドレス
  Wire.endTransmission();
  
  Wire.requestFrom(RTC_address,7);
  for(int i=0;i<7;i++){
  REG_table[i]=Wire.read();
  }
  setTimeData(REG_table[6],REG_table[5],REG_table[4],REG_table[3],REG_table[2],REG_table[1],REG_table[0]);
}