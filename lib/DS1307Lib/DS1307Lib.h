#ifndef DS1307Lib
#define DS1307Lib
#include "Arduino.h"

class TimeData{
  /*
  RTCモジュールの時間データを管理するクラスです
  */
  protected:
    int year;
    int month;
    int day;
    int week;
    int hour;
    int minute;
    int second;
  public:
    const char *weeklist[7]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
    //デフォルトコンストラクタ
    TimeData(){}
    //変換コンストラクタ
    TimeData(int Year, int Month, int Day, int Week, int Hour, int Minute, int Second)
      : year(Year), month(Month), day(Day), week(Week), hour(Hour), minute(Minute), second(Second) {}
    void setTimeData(int Year, int Month, int Day, int Week, int Hour, int Minute, int Second);
    int* getTimeData();
    void showTimeDataSerial();
    String hex2string(int num);
};

class DS1307: public TimeData{
  /*
  RTCモジュールDS1307用の自作クラスです
  TimeDataクラスから派生します
  */
  private:
    const int address=0x00; //先頭アドレス
    const int RTC_address=0x68; //I2Cアドレス
    uint8_t REG_table[7]; //レジスタテーブル
  public:
    DS1307():TimeData(){}
    DS1307(int Year,int Month,int Day,int Week,int Hour,int Minute,int Second)
      : TimeData(Year, Month, Day, Week, Hour, Minute, Second){
      setTimeData(Year,Month,Day,Week,Hour,Minute,Second);
      write();
    }
    void write();
    void read();
};

#endif